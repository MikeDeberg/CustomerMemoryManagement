#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "definitions.h"
#include "mem_allocator.h"
#include "memmg.h"

using namespace std;

uint64_t memmg_alloc() {
    return memmg->allocate();
}

MEMMG_TYPE *memmg_reference(unsigned char *small_pointer) {
    // convert the virtual pointer into a reference, use MEMMG_WIDTH to
    // determine how far to read in the small_pointer.
    uint64_t virtual_address;
    unsigned int i;

    virtual_address = 0;
    for(i=0; i<MEMMG_WIDTH; i++) {
        virtual_address |=  small_pointer[i] << (i * 8);
    }
    return (MEMMG_TYPE *) memmg->reference(virtual_address);
}

memmg_ptr::memmg_ptr() {
    unsigned int i;
    for(i=0; i<MEMMG_WIDTH; i++) {
        *(_pointer + i) = 0;
    }
}

memmg_ptr::memmg_ptr(uint64_t virtual_address) {
    // do some bitmasking here to apply the virtual_address to the _pointer
    // array
    unsigned int i;
    for(i=0; i<MEMMG_WIDTH; i++) {
        _pointer[i] = (0xFF & (virtual_address >> (i * 8)));
    }
}

MEMMG_TYPE &memmg_ptr::operator* () {
    return *memmg_reference(_pointer);
}

MEMMG_TYPE *memmg_ptr::operator-> () {
    return memmg_reference(_pointer);
}
