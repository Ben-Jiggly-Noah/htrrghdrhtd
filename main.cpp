#include<stdio.h>

#include"../Headers/cpu.hpp"
#include"../Headers/ram.hpp"

int main() {
    CPU_UNIT cpu;
    RAM_UNIT ramUnit;

    RAM ram = ramUnit.initRam(65535);
    cpu.initCPU(ram);

    ram[0]=0x23;

    cpu.startCycle(4);

    printf("%d\n", cpu.bRegs.HL);

    ramUnit.clearRam(ram);
    return 0;
}
