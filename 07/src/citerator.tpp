template <class T>
typename Vector<T>::CIterator::reference Vector<T>::CIterator::operator*()
{
    return *(this->vec_pointer + this->index);
}

template <class T>
typename Vector<T>::CIterator::const_reference Vector<T>::CIterator::operator*() const
{
    return *(this->vec_pointer + this->index);
}

template <class T>
typename Vector<T>::CIterator::pointer Vector<T>::CIterator::operator->()
{
    return this->vec_pointer + this->index;
}

template <class T>
typename Vector<T>::CIterator::const_pointer Vector<T>::CIterator::operator->() const
{
    return this->vec_pointer + this->index;
}

template <class T>
typename Vector<T>::CIterator::reference Vector<T>::CIterator::operator[](int m)
{
    return *(this->vec_pointer + this->index + m);
}

template <class T>
typename Vector<T>::CIterator::const_reference Vector<T>::CIterator::operator[](int m) const
{
    return *(this->vec_pointer + this->index + m);
}

template <class T>
typename Vector<T>::CIterator &Vector<T>::CIterator::operator++()
{
    ++this->index;
    return *this;
}

template <class T>
typename Vector<T>::CIterator &Vector<T>::CIterator::operator--()
{
    --this->index;
    return *this;
}

template <class T>
typename Vector<T>::CIterator Vector<T>::CIterator::operator++(int)
{
    CIterator res(*this);
    ++this->index;
    return res;
}

template <class T>
typename Vector<T>::CIterator Vector<T>::CIterator::operator--(int)
{
    CIterator res(*this);
    --this->index;
    return res;
}

template <class T>
typename Vector<T>::CIterator &Vector<T>::CIterator::operator+=(size_t n)
{
    this->index += n;
    return *this;
}

template <class T>
typename Vector<T>::CIterator &Vector<T>::CIterator::operator-=(size_t n)
{
    this->index -= n;
    return *this;
}

template <class T>
typename Vector<T>::CIterator Vector<T>::CIterator::operator+(size_t n) const
{
    CIterator res(*this);
    res += n;
    return res;
}

template <class T>
typename Vector<T>::CIterator Vector<T>::CIterator::operator-(size_t n) const
{
    CIterator res(*this);
    res -= n;
    return res;
}

template <class T>
typename Vector<T>::CIterator::difference_type Vector<T>::CIterator::operator-(CIterator const &second) const
{
    return this->index - second.index;
}

template <class T>
bool Vector<T>::CIterator::operator<(const CIterator &second) const
{
    return this->index < second.index;
}

template <class T>
bool Vector<T>::CIterator::operator<=(const CIterator &second) const
{
    return this->index <= second.index;
}

template <class T>
bool Vector<T>::CIterator::operator>(const CIterator &second) const
{
    return this->index > second.index;
}

template <class T>
bool Vector<T>::CIterator::operator>=(const CIterator &second) const
{
    return this->index >= second.index;
}

template <class T>
bool Vector<T>::CIterator::operator==(const CIterator &second) const
{
    return this->index == second.index;
}

template <class T>
bool Vector<T>::CIterator::operator!=(const CIterator &second) const
{
    return this->index != second.index;
}