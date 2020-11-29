template <class T>
CVector<T>::CIterator::reference CVector<T>::CIterator::operator*()
{
    return *(this->vec_pointer)[this->index];
}

template <class T>
CVector<T>::CIterator::const_reference CVector<T>::CIterator::operator*() const
{
    return *(this->vec_pointer)[this->index];
}

template <class T>
CVector<T>::CIterator::pointer CVector<T>::CIterator::operator->()
{
    return &((*vec_pointer)[this->index]);
}

template <class T>
CVector<T>::CIterator::const_pointer CVector<T>::CIterator::operator->() const
{
    return &((*vec_pointer)[this->index]);
}

template <class T>
CVector<T>::CIterator::reference CVector<T>::CIterator::operator[](int m)
{
    return (*(this->vec_pointer))[this->index + m];
}

template <class T>
CVector<T>::CIterator::const_reference CVector<T>::CIterator::operator[](int m) const
{
    return (*(this->vec_pointer))[this->index + m];
}

template <class T>
CVector<T>::CIterator &CVector<T>::CIterator::operator++()
{
    ++this->index;
    return *this;
}

template <class T>
CVector<T>::CIterator &CVector<T>::CIterator::operator--()
{
    ++this->index;
    return *this;
}

template <class T>
CVector<T>::CIterator CVector<T>::CIterator::operator++(int)
{
    CIterator res(*this);
    ++this->index;
    return res;
}

template <class T>
CVector<T>::CIterator CVector<T>::CIterator::operator--(int)
{
    CIterator res(*this);
    --this->index;
    return res;
}

template <class T>
CVector<T>::CIterator &CVector<T>::CIterator::operator+=(size_t n)
{
    this->index += n;
    return *this;
}

template <class T>
CVector<T>::CIterator &CVector<T>::CIterator::operator-=(size_t n)
{
    this->index -= n;
    return *this;
}

template <class T>
CVector<T>::CIterator CVector<T>::CIterator::operator+(size_t n) const
{
    CIterator res(*this);
    res += n;
    return res;
}

template <class T>
CVector<T>::CIterator CVector<T>::CIterator::operator-(size_t n) const
{
    CIterator res(*this);
    res -= n;
    return res;
}

template <class T>
CVector<T>::CIterator::difference_type CVector<T>::CIterator::operator-(CIterator const &second) const
{
    return this->index - second.index;
}

template<class T>
bool CVector<T>::CIterator::operator<(CIterator const &second) const
{
    return this->index < second.index;
}

template<class T>
bool CVector<T>::CIterator::operator<=(CIterator const &second) const
{
    return this->index <= second.index;
}

template<class T>
bool CVector<T>::CIterator::operator>(CIterator const &second) const
{
    return this->index > second.index;
}

template<class T>
bool CVector<T>::CIterator::operator>=(CIterator const &second) const
{
    return this->index >= second.index;
}

template<class T>
bool CVector<T>::CIterator::operator==(CIterator const &second) const
{
    return this->index == second.index;
}

template<class T>
bool CVector<T>::CIterator::operator!=(CIterator const &second) const
{
    return this->index !=second.index;
}