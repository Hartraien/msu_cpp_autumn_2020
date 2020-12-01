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
        CIterator(const T *v, size_t i) : vec_pointer(v), index(i){};

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
        T *vec_pointer;
        size_t index;
    };

public:
    using value_type = T;
    using const_value_type = const T;
    using size_type = size_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using iterator = CIterator;
    using const_iterator = const CIterator;
    using reverse_iterator = std::reverse_iterator<CIterator>;
    using const_reverse_iterator = const std::reverse_iterator<CIterator>;
    using Allocator = CAllocator<T>;

public:
    CVector();
    CVector(size_type n);
    CVector(size_type n, const T &value);
    CVector(const CVector<T> &other);
    CVector(CVector<T> &&other);

    CVector &operator=(const CVector<T> &other);
    CVector &operator=(CVector<T> &&other);

    ~CVector();

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
    void emplace_back(T last);

    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();

    const_iterator begin() const;
    const_iterator end() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

private:
    size_type reserve_policy();
    void full_clear();
    void base_alloc(size_type n);

    template <class... U,
              typename = std::enable_if_t<
                  std::conjunction_v<
                      std::is_convertible<T, U>...>>>
    void construct_from_values(T first, U... vars);

    pointer container_;
    size_type size_;
    size_type capacity_;
    Allocator allocator_;
    const size_type start_val = 6;
};

template <class T>
CVector<T>::CVector() : container_(nullptr), size_(0), capacity_(0), allocator_(CAllocator<T>())
{
    this->base_alloc(this->start_val);
}

template <class T>
CVector<T>::CVector(size_type n) : container_(nullptr), size_(0), capacity_(0), allocator_(CAllocator<T>())
{
    this->base_alloc(n);
}

template <class T>
CVector<T>::CVector(size_type n, const T &value) : container_(nullptr), size_(0), capacity_(0), allocator_(CAllocator<T>())
{
    this->base_alloc(n);
    for (size_type i = 0; i < n; i++)
    {
        this->push_back(value);
    }
}

template <class T>
template <class... U, typename F>
CVector<T>::CVector(T first, U... vars) : container_(nullptr), size_(0), capacity_(0), allocator_(CAllocator<T>())
{
    this->base_alloc(this->start_val);
    this->construct_from_values(first, vars...);
}

template <class T>
CVector<T>::CVector(const CVector<T> &other) : container_(nullptr), size_(0), capacity_(0), allocator_(other.allocator_)
{
    this->base_alloc(other.capacity_);
    for (size_type i = 0; i < other.size_; i++)
    {
        this->push_back(other[i]);
    }
}

template <class T>
CVector<T>::CVector(CVector<T> &&other) : container_(std::move(other.container_)), size_(std::move(other.size_)), capacity_(std::move(other.capacity_)), allocator_(std::move(other.allocator_))
{
    other.container_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <class T>
CVector<T> &CVector<T>::operator=(const CVector<T> &other)
{
    if (this == &other)
        return *this;
    this->full_clear();
    this->base_alloc(other.capacity_);
    for (size_type i = 0; i < other.size_; i++)
    {
        this->push_back(other[i]);
    }
    return *this;
}

template <class T>
CVector<T> &CVector<T>::operator=(CVector<T> &&other)
{
    if (this == &other)
        return *this;
    this->full_clear();
    this->container_ = other.container_;
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->allocator_ = other.allocator_;

    other.container_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
}

template <class T>
CVector<T>::~CVector()
{
    this->full_clear();
}

template <class T>
constexpr typename CVector<T>::size_type CVector<T>::capacity() const
{
    return this->capacity_;
}

template <class T>
constexpr typename CVector<T>::size_type CVector<T>::size() const
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

template <class T>
constexpr void CVector<T>::reserve(size_type n)
{
    if (n <= this->capacity_)
        return;
    pointer temp = this->allocator_.allocate(n);
    for (size_type i = size_; i > 0; i--)
    {
        temp[i - 1] = this->container_[i - 1];
        this->container_[i - 1].~T();
    }
    this->allocator_.deallocate(this->container_, this->capacity_);
    this->capacity_ = n;
    this->container_ = temp;
}

template <class T>
typename CVector<T>::const_reference CVector<T>::operator[](size_type i) const
{
    return container_[i];
}

template <class T>
typename CVector<T>::reference CVector<T>::operator[](size_type i)
{
    return container_[i];
}

template <class T>
constexpr void CVector<T>::push_back(const T &value)
{
    if (this->size_ == this->capacity_)
    {
        this->reserve(this->reserve_policy());
    }

    new (this->container_ + this->size_) T(value);
}

template <class T>
constexpr void CVector<T>::push_back(T &&value)
{
    if (this->size_ == this->capacity_)
    {
        this->reserve(this->reserve_policy());
    }

    new (this->container_ + this->size_) T(value);
}

template <class T>
typename CVector<T>::size_type CVector<T>::reserve_policy()
{
    return this->capacity_ * 2;
}

template <class T>
void CVector<T>::full_clear()
{
    this->clear();
    this->allocator_.deallocate(this->container_, this->capacity_);
}

template <class T>
void CVector<T>::base_alloc(size_type n)
{
    this->container_ = this->allocator_.allocate(n);
}

template <class T>
typename CVector<T>::iterator CVector<T>::begin()
{
    return iterator(this->container_, 0);
}

template <class T>
typename CVector<T>::iterator CVector<T>::end()
{
    return iterator(this->container_, this->size_);
}

template <class T>
typename CVector<T>::const_iterator CVector<T>::begin() const
{
    return iterator(this->container_, 0);
}

template <class T>
typename CVector<T>::const_iterator CVector<T>::end() const
{
    return iterator(this->container_, this->size_);
}

template <class T>
typename CVector<T>::reverse_iterator CVector<T>::rbegin()
{
    return reverse_iterator(this->container_, this->size_ - 1);
}

template <class T>
typename CVector<T>::reverse_iterator CVector<T>::rend()
{
    return reverse_iterator(this->container_, this->size_);
}

template <class T>
typename CVector<T>::const_reverse_iterator CVector<T>::rbegin()
{
    return reverse_iterator(this->container_, this->size_);
}

template <class T>
typename CVector<T>::const_reverse_iterator CVector<T>::rend()
{
    return reverse_iterator(this->container_, this->size_);
}

#include "citerator.tpp"
#include "cvector.tpp"
#endif // __CVECTOR_H__