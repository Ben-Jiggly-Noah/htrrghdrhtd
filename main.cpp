#include<stdio.h>
#include"../Headers/ram.hpp"
#include"../Headers/cpu.hpp"

int main() {
    CPU_UNIT cpuUnit;

    RAM_UNIT ramUnit;
    initRam(ramUnit, 65535);

    // Set some code examples here
    ramUnit.writeAddress(0x0000, 69);

    cpuUnit.startCycle(1, ramUnit);

    ramUnit.freeRam();
}
