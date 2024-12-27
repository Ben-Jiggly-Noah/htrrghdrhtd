#include<string.h>
#include<stdio.h>

#include<C:\Users\jeffr\Desktop\Z80 Emu\Headers\instructions.hpp>

// Sizes
using BYTE = unsigned char;
using WORD = unsigned short;

// Register Types
struct IR_Reg {
    union { struct { BYTE I; BYTE R; }; WORD IR; };
};

struct registers {
    union { struct { BYTE A; BYTE F; }; WORD AF; };
    union { struct { BYTE B; BYTE C; }; WORD BC; };
    union { struct { BYTE D; BYTE E; }; WORD DE; };
    union { struct { BYTE H; BYTE L; }; WORD HL; };
};

// Cpu Unit
struct CPU_UNIT {
    // Registers
    registers regA;
    registers regB;

    registers currReg = regA;

    WORD PC=0;
    WORD SP=0;

    WORD IX=0;
    WORD IY=0;
    
    IR_Reg IR;

    // Register Functions
    // Get Byte Register
    BYTE* getByteReg(char registerName) {
        if (registerName=='A') return &currReg.A;
        else if (registerName=='B') return &currReg.B;
        else if (registerName=='C') return &currReg.C;
        else if (registerName=='D') return &currReg.D;
        else if (registerName=='E') return &currReg.E;
        else if (registerName=='H') return &currReg.H;
        else if (registerName=='L') return &currReg.L;

        printf("Invalid Register: %c\n", registerName);
        exit(1);
    }
    // Get Word Register
    WORD* getWordReg(char* registerName) {
        if (strcmp("AF", registerName)) return &currReg.AF;
        else if (strcmp("BC", registerName)) return &currReg.BC;
        else if (strcmp("DE", registerName)) return &currReg.DE;
        else if (strcmp("HL", registerName)) return &currReg.HL;

        printf("Invalid Register: %s\n", registerName);
        exit(1);
    }

    BYTE fetchByte(WORD &cycles, RAM_UNIT ram) {
        BYTE data = ram.readAddress(PC);
        PC++;
        cycles-=3;
        return data;
    }

    int startCycle(WORD cycles, RAM_UNIT ram) {
        while (cycles>0) {
            BYTE opcode = fetchByte(cycles, ram);
            printf("Byte %d: 0x%x\n", PC-1, opcode);

            // Encoding
            int i=0;
            for (i=0; INSTRUCTIONS[i][0]==opcode; i++) {
                if (i==instructionsLength) {
                    printf("Invalid Instruction at %d: %x\n", PC-1, opcode);
                    return 1;
                }
            }

            CONST_BYTE* instrData = INSTRUCTIONS[i];
            cycles--;

            // Looking for extra bytes
            BYTE* operands = (BYTE*)malloc(0);

            for (int i=0; i<instrData[1]; i++) {
                BYTE operand = fetchByte(cycles, ram);
                printf("Byte %d: 0x%x, Operand %d/%d for byte %d\n", PC-1, operand, i+1, instrData[1], PC-1-(i+1));

                operands=(BYTE*)realloc(operands,i+1);
                operands[i]=operand;
            }

            // Do encoding for operands

            free(operands);
            operands = NULL;
        }

        return 0;
    }
};
