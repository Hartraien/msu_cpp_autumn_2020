template <class T>
Vector<T>::Vector() : container_(nullptr), size_(0), capacity_(0), allocator_(Vector<T>::Allocator())
{
    this->base_alloc(this->start_val);
}

template <class T>
Vector<T>::Vector(size_type n) : container_(nullptr), size_(0), capacity_(0), allocator_(Vector<T>::Allocator())
{
    this->base_alloc(n);
}

template <class T>
Vector<T>::Vector(size_type n, const T &value) : container_(nullptr), size_(0), capacity_(0), allocator_(Vector<T>::Allocator())
{
    this->base_alloc(n);
    for (size_type i = 0; i < n; i++)
    {
        this->push_back(value);
    }
}

template <class T>
Vector<T>::Vector(const std::initializer_list<T> &il) : container_(nullptr), size_(0), capacity_(0), allocator_(Vector<T>::Allocator())
{
    this->base_alloc(il.size());
    for (auto iter = il.begin(); iter != il.end(); iter++)
    {
        this->push_back(*iter);
    }
}

template <class T>
template <class InputIterator>
Vector<T>::Vector(InputIterator first, InputIterator last)
{
    this->base_alloc(1);
    for (auto iter = first; iter != last; iter++)
    {
        this->push_back(*iter);
    }
}

template <class T>
Vector<T> &Vector<T>::operator=(const std::initializer_list<T> &il)
{
    Vector<T> res(il.begin(), il.end());
    *this = std::move(res);
    return *this;
}

template <class T>
Vector<T>::Vector(const Vector<T> &other) : container_(nullptr), size_(0), capacity_(0), allocator_(other.allocator_)
{
    this->base_alloc(other.capacity_);
    for (size_type i = 0; i < other.size_; i++)
    {
        this->push_back(other[i]);
    }
}

template <class T>
Vector<T>::Vector(Vector<T> &&other) : container_(std::move(other.container_)), size_(std::move(other.size_)), capacity_(std::move(other.capacity_)), allocator_(std::move(other.allocator_))
{
    other.container_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
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
Vector<T> &Vector<T>::operator=(Vector<T> &&other)
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
Vector<T>::~Vector()
{
    this->clear_and_deallocate();
}

template <class T>
constexpr typename Vector<T>::size_type Vector<T>::capacity() const
{
    return this->capacity_;
}

template <class T>
constexpr typename Vector<T>::size_type Vector<T>::size() const
{
    return this->size_;
}

template <class T>
void Vector<T>::clear()
{
    while (this->size_ > 0)
    {
        container_[size_ - 1].~T();
        --size_;
    }
}

template <class T>
constexpr bool Vector<T>::empty() const
{
    return (this->size_ == 0);
}

template <class T>
constexpr void Vector<T>::reserve(size_type n)
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
typename Vector<T>::const_reference Vector<T>::operator[](size_type i) const
{
    if (i >= this->size_)
        throw OOBException(i, this->size_);
    return container_[i];
}

template <class T>
typename Vector<T>::reference Vector<T>::operator[](size_type i)
{
    if (i >= this->size_)
        throw OOBException(i, this->size_);
    return container_[i];
}

template <class T>
constexpr void Vector<T>::push_back(const T &value)
{
    if (this->size_ == this->capacity_)
    {
        this->reserve(this->reserve_policy());
    }

    new (this->container_ + this->size_) T(value);
    this->size_++;
}

template <class T>
constexpr void Vector<T>::push_back(T &&value)
{
    if (this->size_ == this->capacity_)
    {
        this->reserve(this->reserve_policy());
    }
    new (this->container_ + this->size_) T(std::move(value));
    this->size_++;
}

template <class T>
typename Vector<T>::value_type Vector<T>::pop_back()
{
    if (this->size_ == 0)
        throw EmptyVectorException("pop_back");
    T res(this->container_[this->size_ - 1]);
    container_[size_ - 1].~T();
    --size_;
    return res;
}

template <class T>
constexpr typename Vector<T>::size_type Vector<T>::reserve_policy() const
{
    return this->capacity_ * 2 + 1;
}

template <class T>
void Vector<T>::clear_and_deallocate()
{
    this->clear();
    this->allocator_.deallocate(this->container_, this->capacity_);
}

template <class T>
void Vector<T>::base_alloc(size_type n)
{
    this->container_ = this->allocator_.allocate(n);
    this->capacity_ = n;
    this->size_ = 0;
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return iterator(this->container_, 0);
}

template <class T>
typename Vector<T>::iterator Vector<T>::end()
{
    return iterator(this->container_, this->size_);
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
    return iterator(this->container_, 0);
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
    return iterator(this->container_, this->size_);
}

template <class T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin()
{
    return reverse_iterator(this->end());
}

template <class T>
typename Vector<T>::reverse_iterator Vector<T>::rend()
{
    return reverse_iterator(this->begin());
}

template <class T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const
{
    return reverse_iterator(this->end());
}

template <class T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const
{
    return reverse_iterator(this->begin());
}

template <class T>
template <class... U>
void Vector<T>::emplace_back(const U &... vars)
{
    if (this->size_ == this->capacity_)
    {
        this->reserve(this->reserve_policy());
    }

    new (this->container_ + this->size_) T(vars...);
    this->size_++;
}

template <class T>
constexpr void Vector<T>::resize(size_type n)
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
constexpr void Vector<T>::resize(size_type n, const value_type &val)
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
void Vector<T>::clear_last_n(size_type n)
{
    while (this->size_ > n)
    {
        container_[size_ - 1].~T();
        --size_;
    }
}
