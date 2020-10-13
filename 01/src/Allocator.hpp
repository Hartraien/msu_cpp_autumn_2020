class Allocator
{
public:
	Allocator();
	Allocator(size_t maxSize);
	void makeAllocator(size_t maxSize);
	char *alloc(size_t size);
	void reset();
	~Allocator();
	size_t getCapacity();
	size_t getRemainder();

private:
	char *mem_pointer;
	size_t offset;
	size_t capacity;
	bool isInitiated;
};