#include<stdio.h>
#include<stdlib.h>

#include"Headers/cpu.hpp"
#include"Headers/ram.hpp"

int main() {
    CPU cpu;
    RAM ramUnit;

    BYTE* ram = ramUnit.initRam(65535);

    ramUnit.clearRam(ram);
    return 0;
}