template <class T>
CVector<T>::CVector() : container_(nullptr), size_(0), capacity_(0), allocator_(CVector<T>::Allocator())
{
    this->base_alloc(this->start_val);
}

template <class T>
CVector<T>::CVector(size_type n) : container_(nullptr), size_(0), capacity_(0), allocator_(CVector<T>::Allocator())
{
    this->base_alloc(n);
}

template <class T>
CVector<T>::CVector(size_type n, const T &value) : container_(nullptr), size_(0), capacity_(0), allocator_(CVector<T>::Allocator())
{
    this->base_alloc(n);
    for (size_type i = 0; i < n; i++)
    {
        this->push_back(value);
    }
}

template <class T>
template <class... U, typename F>
CVector<T>::CVector(const T &first, const U &... vars) : container_(nullptr), size_(0), capacity_(0), allocator_(CVector<T>::Allocator())
{
    this->base_alloc(sizeof...(vars) + 1);
    this->emplace_back(first, vars...);
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
    this->clear_and_deallocate();
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
    this->clear_and_deallocate();
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
    this->clear_and_deallocate();
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
    if (i >= this->size_)
        throw OOBException(i, this->size_);
    return container_[i];
}

template <class T>
typename CVector<T>::reference CVector<T>::operator[](size_type i)
{
    if (i >= this->size_)
        throw OOBException(i, this->size_);
    return container_[i];
}

template <class T>
constexpr void CVector<T>::push_back(const T &value)
{
    if (this->size_ == this->capacity_)
    {
        this->reserve(this->reserve_policy());
    }

    this->container_[this->size_++] = value;
}

template <class T>
constexpr void CVector<T>::push_back(T &&value)
{
    if (this->size_ == this->capacity_)
    {
        this->reserve(this->reserve_policy());
    }

    this->container_[this->size_++] = std::move(value);
}

template <class T>
typename CVector<T>::value_type CVector<T>::pop_back()
{
    if (this->size_ == 0)
        throw EmptyVectorException("pop_back");
    T res(this->container_[this->size_ - 1]);
    container_[size_ - 1].~T();
    --size_;
    return res;
}

template <class T>
typename CVector<T>::size_type CVector<T>::reserve_policy()
{
    return this->capacity_ * 2;
}

template <class T>
void CVector<T>::clear_and_deallocate()
{
    this->clear();
    this->allocator_.deallocate(this->container_, this->capacity_);
}

template <class T>
void CVector<T>::base_alloc(size_type n)
{
    this->container_ = this->allocator_.allocate(n);
    this->capacity_ = n;
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
    return reverse_iterator(this->end());
}

template <class T>
typename CVector<T>::reverse_iterator CVector<T>::rend()
{
    return reverse_iterator(this->begin());
}

template <class T>
typename CVector<T>::const_reverse_iterator CVector<T>::rbegin() const
{
    return reverse_iterator(this->end());
}

template <class T>
typename CVector<T>::const_reverse_iterator CVector<T>::rend() const
{
    return reverse_iterator(this->begin());
}

template <class T>
template <class... U, typename F>
void CVector<T>::emplace_back(const T &first, const U &... vars)
{
    this->push_back(first);
    this->emplace_back(vars...);
}

template <class T>
void CVector<T>::emplace_back(const T &last)
{
    this->push_back(last);
}

template <class T>
constexpr void CVector<T>::resize(size_type n)
{
    if (n == this->size_)
        return;
    else if (n < this->size_)
    {
        this->clear_last_n(this->size_ - n);
    }
    else
    {
        if (n > this->capacity_)
            this->reserve(n);
        while (this->size_ != n)
        {
            this->push_back(value_type());
        }
    }
}

template <class T>
constexpr void CVector<T>::resize(size_type n, const value_type &val)
{
    if (n == this->size_)
        return;
    else if (n < this->size_)
    {
        this->clear_last_n(this->size_ - n);
    }
    else
    {
        if (n > this->capacity_)
            this->reserve(n);
        while (this->size_ != n)
        {
            this->push_back(value_type(val));
        }
    }
}

template <class T>
void CVector<T>::clear_last_n(size_type n)
{
    while (this->size_ > n)
    {
        container_[size_ - 1].~T();
        --size_;
    }
}
