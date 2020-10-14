#ifndef __ALLOCATOR_HPP___
#define __ALLOCATOR_HPP___

class Allocator
{
public:
	//Sets offset_ = 0,
	Allocator();
	// calls Allocator() and then calls makeAllocator(maxSize)
	Allocator(size_t maxSize);
	//Allocates memory of maxSize chars and stores pointer in mem_pointer_
	// throws std::invalid_argument if maxSize == 0
	void makeAllocator(size_t maxSize);
	// Allocates size memory from mem_pointer
	// If remaining capacity is no less than size
	// return pointer to allocated memory or nullptr
	// throws std::invalid_argument("Allocator is not initiated...") if called before makeAllocator
	// throws std::invalid_argument("") if called with size == 0
	char *alloc(size_t size);
	//Resets allocated memory for reuse
	//throws std::invalid_argument("Allocator is not initiated...") if called before makeAllocator
	void reset();
	//Deletes mem_pointer_
	~Allocator();
	// Returns capacity of preallocated memory
	// If called before makeAllocator returns 0
	size_t getCapacity();
	// Returns remaining capacity of preallocated memory
	// If called before makeAllocator returns 0
	size_t getRemainder();

private:
	// Pointer to allocated memory
	// Initial value = nullptr
	char *mem_pointer_;
	// Length of memeory, that is already allocated by alloc() method
	// Initial value = 0
	size_t offset_;
	// Capacity of mem_pointer memory
	// Initial value = 0
	size_t capacity_;
	// Shows whether makeAllocator() was called already
	// Initial value = false
	bool isInitiated_;
};

#endif