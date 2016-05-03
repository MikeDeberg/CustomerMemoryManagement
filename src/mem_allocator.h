#ifndef CUSTOMMEMORYMANAGEMENT_MEM_ALLOCATOR_H
#define CUSTOMMEMORYMANAGEMENT_MEM_ALLOCATOR_H

#include <vector>
#include <stdint.h>


class Block {
public:
    Block(uint64_t addr, unsigned int max, unsigned int size);
    ~Block();

    bool is_full();
    uint64_t get_next_addr();
    void *get_reference_of(unsigned int offset);
private:
    void *memory;
    unsigned int struct_size;
    unsigned int max_count;
    unsigned int curr_offset;
    uint64_t root_addr;
};

class MemoryAllocator {
public:
    MemoryAllocator(int struct_size);
    ~MemoryAllocator();

    uint64_t allocate();
    void *reference(uint64_t virt_ptr);
private:
    unsigned int struct_size;
    unsigned int structs_per_block;
    uint64_t next_block_addr;
    std::vector<Block *> blocks;

    Block *addBlock();
    unsigned int get_block_size(unsigned int struct_size);
};

#endif //CUSTOMMEMORYMANAGEMENT_MEM_ALLOCATOR_H
