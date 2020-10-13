#include <stdexcept>
#include "Allocator.hpp"

Allocator::Allocator()
{
	this->offset = 0;
	this->capacity = 0;
	this->mem_pointer = nullptr;
	this->isInitiated = false;
}

Allocator::Allocator(size_t maxSize) : Allocator()
{
	makeAllocator(maxSize);
}

void Allocator::makeAllocator(size_t maxSize)
{
	if (this->isInitiated == true)
	{
		return;
	}
	if (maxSize > 0)
	{
		this->mem_pointer = new char[maxSize];
		this->capacity = maxSize;
		this->isInitiated = true;
		return;
	}
	else
	{
		throw std::invalid_argument("received non-positive maxSize argument: " + maxSize);
	}
}

char *Allocator::alloc(size_t size)
{
	if (this->isInitiated == false)
	{
		throw "Allocator is not initiated, call makeAllocator before calling alloc";
	}
	if (size < this->getRemainder())
	{
		this->offset += size;
		return this->mem_pointer + size;
	}
	else
	{
		return nullptr;
	}
}

void Allocator::reset()
{
	if (this->isInitiated == false)
	{
		throw "Allocator is not initiated, call makeAllocator before calling reset";
	}
	this->offset = 0;
}

Allocator::~Allocator()
{
	delete[] this->mem_pointer;
}

size_t Allocator::getCapacity()
{
	return this->capacity;
}

size_t Allocator::getRemainder()
{
	return this->capacity - this->offset;
}
