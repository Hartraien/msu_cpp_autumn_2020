#ifndef __CVECTOR_H__
#define __CVECTOR_H__
#include "callocator.hpp"
#include "exc/outofbounds.hpp"
#include "exc/emptyvectorexception.hpp"

#include <initializer_list>

template <class T>
class Vector
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
        explicit CIterator(pointer v, size_t i) : vec_pointer(v), index(i){};
        CIterator(const CIterator &other) : vec_pointer(other.vec_pointer), index(other.index){};
        CIterator(CIterator &&other) : vec_pointer(other.vec_pointer), index(other.index)
        {
            other.vec_pointer = nullptr;
            other.index = 0;
        };
        ~CIterator(){};

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

        bool operator<(const CIterator &second) const;
        bool operator<=(const CIterator &second) const;
        bool operator>(const CIterator &second) const;
        bool operator>=(const CIterator &second) const;
        bool operator!=(const CIterator &second) const;
        bool operator==(const CIterator &second) const;

    private:
        pointer vec_pointer;
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
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const iterator>;
    using Allocator = CAllocator<T>;

public:
    Vector();
    explicit Vector(size_type n);
    explicit Vector(size_type n, const T &value);
    Vector(const Vector<T> &other);
    Vector(Vector<T> &&other);
    Vector(const std::initializer_list<T> &il);

    template <class InputIterator>
    Vector(InputIterator first, InputIterator last);

    Vector &operator=(const Vector<T> &other);
    Vector &operator=(Vector<T> &&other);
    Vector &operator=(const std::initializer_list<T> &il);

    ~Vector();

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

    template <typename... U>
    void emplace_back(const U &... vars);

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
    void clear_and_deallocate();
    void clear_last_n(size_type n);
    void base_alloc(size_type n);

    pointer container_;
    size_type size_;
    size_type capacity_;
    Allocator allocator_;
    const size_type start_val = 6;
};

#include "citerator.tpp"
#include "cvector.tpp"
#endif // __CVECTOR_H__