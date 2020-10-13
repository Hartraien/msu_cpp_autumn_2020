#include <stdexcept>
#include "Allocator.hpp"
#include "InitException.hpp"

Allocator::Allocator()
{
	this->offset_ = 0;
	this->capacity_ = 0;
	this->mem_pointer_ = nullptr;
	this->isInitiated_ = false;
}

Allocator::Allocator(size_t maxSize) : Allocator()
{
	makeAllocator(maxSize);
}

void Allocator::makeAllocator(size_t maxSize)
{
	if (this->isInitiated_ == true)
	{
		return;
	}
	if (maxSize > 0)
	{
		this->mem_pointer_ = new char[maxSize];
		this->capacity_ = maxSize;
		this->isInitiated_ = true;
		return;
	}
	else
	{
		throw std::invalid_argument("Received non-positive maxSize argument");
	}
}

char *Allocator::alloc(size_t size)
{
	if (this->isInitiated_ == false)
	{
		throw InitException("Allocator is not initiated, call makeAllocator before calling alloc");
	}
	if (size == 0)
	{
		throw std::invalid_argument("Received non-positive size argument");
	}
	if (size < this->getRemainder())
	{
		size_t previousOffset = this->offset_;
		this->offset_+=size;
		return this->mem_pointer_ + previousOffset;
	}
	else
	{
		return nullptr;
	}
}

void Allocator::reset()
{
	if (this->isInitiated_ == false)
	{
		throw InitException("Allocator is not initiated, call makeAllocator before calling reset");
	}
	this->offset_ = 0;
}

Allocator::~Allocator()
{
	delete[] this->mem_pointer_;
}

size_t Allocator::getCapacity()
{
	return this->capacity_;
}

size_t Allocator::getRemainder()
{
	return this->capacity_ - this->offset_;
}
