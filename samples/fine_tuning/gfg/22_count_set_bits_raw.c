/* Source: https://www.geeksforgeeks.org/dsa/count-set-bits-in-an-integer/ */
#include <stdio.h>

int num_to_bits[16] = { 0, 1, 1, 2, 1, 2, 2, 3,
                        1, 2, 2, 3, 2, 3, 3, 4 };

/* Recursively get nibble of a given number 
  and map them in the array  */
unsigned int countSetBitsRec(unsigned int num)
{
    int nibble = 0;
    if (0 == num)
        return num_to_bits[0];

    // Find last nibble
    nibble = num & 0xf;

    // Use pre-stored values to find count
    // in last nibble plus recursively add
    // remaining nibbles.
    return num_to_bits[nibble] + countSetBitsRec(num >> 4);
}

int main()
{
    int num = 9;
    printf("%d\n", countSetBitsRec(num));
}
