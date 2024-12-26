#include<stdlib.h>
#include<stdio.h>

// Sizes
using BYTE = unsigned char;
using WORD = unsigned short;

// Ram Unit
struct RAM_UNIT {
    WORD size = 0;
    BYTE* ram = (BYTE*)malloc(0);
    bool init = false;

    // Frees Ram; Best ran at end of CPU usage
    void freeRam() {
        if (init) {
            size = 0;

            free(ram);
            ram=NULL;
            init=false;
        }
    }

    // Reads a byte from Ram; Must be initialized first
    BYTE readAddress(WORD addr) {
        if (init && addr<=size) {
            return ram[addr];
        } else exit(1);
    }

    // Writes a byte to Ram; Must be initialized first
    void writeAddress(WORD addr, BYTE value) {
        if (init && addr<size) {
            ram[addr]=value;
        } else exit(1);
    }
};

// Allocates space for Ram; Initializes Ram
void initRam(RAM_UNIT &ramModule, WORD bytes) {
    ramModule.size = bytes;
    ramModule.ram = (BYTE*)realloc(ramModule.ram, ramModule.size+1);
    ramModule.init = true;
}
