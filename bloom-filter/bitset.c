#include "bitset.h"
#include <stdlib.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
    struct bitset *result = malloc(sizeof(struct bitset)); // we use a pointer because if we didn't, we'd return a copy of the bitset and not the actual bitset. The pointer has the address of the actual bitset
    result -> universe_size = size;
    result -> size_in_words = (result -> universe_size / (sizeof(uint64_t) * 8)) + ((result -> universe_size % (sizeof(uint64_t) * 8) == 0) ? 0 : 1);
    result -> bits = malloc(sizeof(uint64_t) * result -> size_in_words);
    for (int i = 0; i < result -> size_in_words; i++)
    {
        result -> bits[i] = 0;
    }
    return result;
}

// bits + sizeof(uint64_t) * index
// free a bitset's memory
void bitset_free(struct bitset * set)
{
    free(set -> bits);
    free(set);
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
    return this -> universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    int num_of_items = 0;
    for (int i = 0; i < this -> universe_size; i++)
    {
        if (bitset_lookup(this, i))
            num_of_items++;
    }
    return num_of_items;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    int word_index = item / (sizeof(uint64_t) * 8);
    int bit_index = item % (sizeof(uint64_t) * 8);
    uint64_t mask = 1ULL << bit_index;
    return (this -> bits[word_index] & mask) >> bit_index;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
// Note to self: The mask sets the bit to 1, so we can use | (OR) to set the bit. If the bit is already set, it won't clear it as its an OR operation.
void bitset_add(struct bitset * this, int item) {
    int word_index = item / (sizeof(uint64_t) * 8);
    int bit_index = item % (sizeof(uint64_t) * 8);
    uint64_t mask = 1ULL << bit_index;
    this -> bits[word_index] = this->bits[word_index] | mask;
}

// remove an item with number 'item' from the set,
// Note to self: The mask sets the bit to 1, so if we use ^ (XOR), we can clear the bit [since XOR has TT = F]
void bitset_remove(struct bitset * this, int item) {
    int word_index = item / (sizeof(uint64_t) * 8);
    int bit_index = item % (sizeof(uint64_t) * 8);
    uint64_t mask = 1ULL << bit_index;
    this -> bits[word_index] = this->bits[word_index] ^ mask;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
// Note to self: We will use OR for union
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        for (int i = 0; i < dest -> universe_size; i++)
            if (bitset_lookup(src1, i) || bitset_lookup(src2, i))
                bitset_add(dest, i);
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
// Note to self: We will use AND for union
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        for (int i = 0; i < dest -> universe_size; i++)
            if (bitset_lookup(src1, i) && bitset_lookup(src2, i))
                bitset_add(dest, i);
}
