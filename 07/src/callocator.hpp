#ifndef __CALLOCATOR_H__
#define __CALLOCATOR_H__
#include <new>
#include <limits>

template <class T>
class CAllocator
{
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = size_t;

public:
    pointer allocate(size_type n);
    void deallocate(pointer p, size_type n);
};

template <class T>
typename CAllocator<T>::pointer CAllocator<T>::allocate(size_type n)
{
    if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
        throw std::bad_alloc();
    pointer p = static_cast<pointer>(::operator new(n * sizeof(value_type)));
    return p;
}

template<class T>
void CAllocator<T>::deallocate(pointer p, size_type n) 
{
    ::operator delete(static_cast<void*>(p));
}

template <class T, class U>
bool operator==(const CAllocator<T> &, const CAllocator<U> &) { return true; }
template <class T, class U>
bool operator!=(const CAllocator<T> &, const CAllocator<U> &) { return false; }
#endif // __CALLOCATOR_H__