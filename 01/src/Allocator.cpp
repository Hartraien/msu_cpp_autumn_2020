#include <stdexcept>
#include "Allocator.hpp"

Allocator::Allocator()
{
	this->offset = this->baseOffset;
	this->mem_pointer = nullptr;
}

Allocator::Allocator(size_t maxSize) : Allocator()
{
	makeAllocator(maxSize);
}

void Allocator::makeAllocator(size_t maxSize)
{
	if (maxSize > 0)
	{
		mem_pointer = new char[maxSize];
		this->capacity = maxSize;
	}
	else
	{
		throw std::invalid_argument("received non-positive maxSize argument: " + maxSize);
	}
}

char *Allocator::alloc(size_t size)
{
	size_t remainder = this->capacity - this->offset;
	if (size < remainder)
	{
		this->offset += size;
		return mem_pointer+size;
	}
	else
	{
		return nullptr;
	}
	
}

void Allocator::reset()
{
	offset = baseOffset;
}

Allocator::~Allocator()
{
	delete[] this->mem_pointer;
}
