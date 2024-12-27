#include<stdio.h>
#include"../Headers/ram.hpp"
#include"../Headers/cpu.hpp"

int main() {
    CPU_UNIT cpuUnit;

    RAM_UNIT ramUnit;
    initRam(ramUnit, 256);

    // Set some code examples here
    ramUnit.writeAddress(0x0000, 0x69);
    ramUnit.writeAddress(0x0001, 0x42);
    ramUnit.writeAddress(0x0002, 0xF0);

    cpuUnit.startCycle(12, ramUnit);

    ramUnit.freeRam();
}
