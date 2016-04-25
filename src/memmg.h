/* Allocation will look like:
 * MemmgPointer my_ptr;
 * my_ptr = MemmgPointer(new(memmg_alloc()) OurClassType(1, 2, 3));
 *
 * Care should be taken to ensure that a pointer to MemmgPointer is not used,
 * instead place it directly in any structs.
 */

#include "definitions.h"


void * memmg_alloc();

class MemmgPointer {
public:
    MemmgPointer(MEMMG_TYPE *ptr);
    MEMMG_TYPE & operator* ();
    MEMMG_TYPE * operator-> ();
private:
    char *_pointer;
};
