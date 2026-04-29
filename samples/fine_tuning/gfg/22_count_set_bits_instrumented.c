/* Source: https://www.geeksforgeeks.org/dsa/count-set-bits-in-an-integer/ */
#include <stdio.h>

#include "tracer.h"

int num_to_bits[16] = { 0, 1, 1, 2, 1, 2, 2, 3,
                        1, 2, 2, 3, 2, 3, 3, 4 };

/* Recursively get nibble of a given number
  and map them in the array  */
unsigned int countSetBitsRec(unsigned int num)
{
    trace_var_init("num", num);
    trace_line(11);
    int nibble = 0;
    trace_var_init("nibble", nibble);
    trace_line(12);
    if (0 == num)
        return num_to_bits[0];

    // Find last nibble
    trace_line(16);
    nibble = num & 0xf;
    trace_var("nibble", nibble);
    trace_array_highlight("num_to_bits", nibble);

    // Use pre-stored values to find count
    // in last nibble plus recursively add
    // remaining nibbles.
    trace_line(21);
    return num_to_bits[nibble] + countSetBitsRec(num >> 4);
}

int main()
{
    trace_line(26);
    int num = 9;
    trace_var_init("num", num);
    trace_line(27);
    printf("%d\n", countSetBitsRec(num));
}
