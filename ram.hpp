#include<stdlib.h>

// Sizes
using BYTE = char;
using WORD = short;
using RAM = char*;

// Ram Unit
struct RAM_UNIT {
    RAM initRam(WORD size) {
        return (RAM)malloc(((size_t)size)+1);
    }

    void clearRam(RAM ram) {
        free(ram);
        ram=NULL;
    }
};
