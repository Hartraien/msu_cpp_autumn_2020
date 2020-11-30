#ifndef __CVECTOR_H__
#define __CVECTOR_H__
#include "callocator.hpp"

template <class T>
class CVector
{
private:
    class CIterator
    {
    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        CIterator() : vec_pointer(nullptr), index(0){};
        CIterator(const CVector<T> *v, size_t i) : vec_pointer(v), index(i){};

        reference operator*();
        const_reference operator*() const;
        pointer operator->();
        const_pointer operator->() const;
        reference operator[](int m);
        const_reference operator[](int m) const;

        CIterator &operator++();
        CIterator &operator--();
        CIterator operator++(int);
        CIterator operator--(int);
        CIterator &operator+=(size_t n);
        CIterator &operator-=(size_t n);
        CIterator operator+(size_t n) const;
        CIterator operator-(size_t n) const;
        difference_type operator-(CIterator const &second) const;

        bool operator<(CIterator const &second) const;
        bool operator<=(CIterator const &second) const;
        bool operator>(CIterator const &second) const;
        bool operator>=(CIterator const &second) const;
        bool operator!=(const CIterator &second) const;
        bool operator==(const CIterator &second) const;

    private:
        CVector<T> *vec_pointer;
        size_t index;
    };

public:
    using value_type = T;
    using const_value_type = const T;
    using size_type = size_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = cosnt T &;
    using iterator = CIterator<T>;
    using const_iterator = const CIterator<T>;
    using reverse_iterator = std::reverse_iterator<CIterator<T>>;
    using const_reverse_iterator = const std::reverse_iterator<CIterator<T>>;
    using Allocator = CAllocator<T>;

public:
    CVector();
    CVector(size_type n);
    CVector(size_type n, const T &value);
    template <typename... U,
              typename = std::enable_if_t<
                  std::conjunction_v<
                      std::is_convertible<T, U>...>>>
    CVector(T first, U... vars);

    constexpr size_type capacity() const;
    constexpr size_type size() const;
    void clear();
    constexpr bool empty() const;
    constexpr void reserve(size_type n);
    constexpr void resize(size_type n);
    constexpr void resize(size_type n, const value_type &val);

    const_reference operator[](size_type i) const;
    reference operator[](size_type i);

    constexpr void push_back(const T &value);
    constexpr void push_back(T &&value);

    value_type pop_back();
    template <typename... U,
              typename = std::enable_if_t<
                  std::conjunction_v<
                      std::is_convertible<T, U>...>>>
    void emplace_back(T first, U... vars);

    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();

    const_iterator begin() const;
    const_iterator end() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

private:
    void base_alloc(size_type n);

    template <class... U,
              typename = std::enable_if_t<
                  std::conjunction_v<
                      std::is_convertible<T, U>...>>>
    void construct_from_values(T first, U... vars);
    void emplace_back(T last);

    pointer container_;
    size_type size_;
    size_type capacity_;
    Allocator allocator_;
    const size_type start_val = 6;
};

template <class T>
CVector<T>::CVector() : container_(nullptr), size_(0), capacity_(0), allocator_(new CAllocator())
{
    this->base_alloc(this->start_val);
}

template <class T>
CVector<T>::CVector(size_type n) : container_(nullptr), size_(0), capacity_(0), allocator_(new CAllocator())
{
    this->base_alloc(n);
}

template <class T>
CVector<T>::CVector(size_type n, const T &value) : container_(nullptr), size_(0), capacity_(0), allocator_(new CAllocator())
{
    this->base_alloc(n);
    for (size_type i = 0; i < n; i++)
    {
        this->push_back(value);
    }
}

template <class T>
template <class... U, typename F>
CVector<T>::CVector(T first, U... vars) : container_(nullptr), size_(0), capacity_(0), allocator_(new CAllocator())
{
    this->base_alloc(this->start_val);
    this->construct_from_values(first, vars);
}

template <class T>
constexpr CVector<T>::size_type CVector<T>::capacity() const
{
    return this->capacity_;
}

template <class T>
constexpr CVector<T>::size_type CVector<T>::size() const
{
    return this->size_;
}

template <class T>
void CVector<T>::clear()
{
    while (this->size_ > 0)
    {
        container_[size_ - 1].~T();
        --size_;
    }
}

template <class T>
constexpr bool CVector<T>::empty() const
{
    return (this->size_ == 0);
}

#include "citerator.tpp"
#include "cvector.tpp"
#endif // __CVECTOR_H__