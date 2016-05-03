//
// Created by Justin on 4/26/16.
//
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "mem_allocator.h"

using namespace std;

Block::Block(uint64_t addr, int max, int size) {
    root_addr = addr;
    max_count = max;
    struct_size = size;
    curr_offset = 0;
    memory = malloc(struct_size * max_count);
}

Block::~Block() {
    free(memory);
}

bool Block::is_full() {
    return curr_offset == max_count;
}

uint64_t Block::get_next_addr() {
    if (is_full()) return 0;
    return root_addr + curr_offset++;
}

void *Block::get_reference_of(int offset) {
    return memory + (offset * struct_size);
}


MemoryAllocator::MemoryAllocator(int size) {
    struct_size = size;
    structs_per_block = get_block_size(struct_size) / size;
    cout << "Struct Size " << struct_size << endl;
    cout << "Structs per Block " << structs_per_block << endl;
    next_block_addr = 1;
    addBlock();
}

MemoryAllocator::~MemoryAllocator() {
    // The current understanding is that calling delete on the vector's
    // contained block pointers will free the underlying memory to which they
    // point but, after this, the pointers themselves still exist (although they
    // have been invalidated). Calling the vectors destructor eliminates the
    // remaining invalidated block pointers themselves.
    for(uint64_t i = blocks.size() - 1; i >= 0; i--) {
        delete(blocks[i]);
    }
    blocks.clear();
}

uint64_t MemoryAllocator::allocate() {
    Block *b = blocks.back();
    if (b->is_full()) {
        b = addBlock();
    }
    return b->get_next_addr();
}

void *MemoryAllocator::reference(uint64_t virt_ptr) {
    if (!virt_ptr)
        return NULL;
    uint64_t block_id = ((uint64_t) (virt_ptr - ((uint64_t) 1))) / structs_per_block;
    uint64_t struct_id = virt_ptr % structs_per_block;
    try{
        return blocks.at(block_id)->get_reference_of(struct_id);

    }
    catch(...){
        cout << virt_ptr << endl;
        cout << block_id << endl;
        cout << struct_id << endl;
        throw "Reference died";
    }
}

Block *MemoryAllocator::addBlock() {
    uint64_t root_addr = next_block_addr;
    next_block_addr += structs_per_block;
    Block *b = new Block(root_addr, structs_per_block, struct_size);
    blocks.push_back(b);
    return b;
}

/**
 * Gets optimal minimal block size based upon multiples
 * of struct and pointer sizes in bytes.
 */
int MemoryAllocator::get_block_size(int struct_size) {
    int pointer_size = sizeof(void *);
    struct_size *= 1024;
    int lcm = (struct_size > pointer_size) ? struct_size : pointer_size;

    do {
        if (lcm % struct_size == 0 && lcm % pointer_size == 0) {
            break;
        }
        else
            ++lcm;
    } while (true);

    return lcm;
}
