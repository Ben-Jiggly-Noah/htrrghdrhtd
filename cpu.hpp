#include<string.h>
#include<stdio.h>

#include<../Headers/instructions.hpp>

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
    // Emulator Properties
    BYTE incorrectCodeByte=0;
    WORD incorrectCodeWord=0;

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

        return &incorrectCodeByte;
    }
    // Get Word Register
    WORD* getWordReg(char* registerName) {
        if (strcmp("AF", registerName)) return &currReg.AF;
        else if (strcmp("BC", registerName)) return &currReg.BC;
        else if (strcmp("DE", registerName)) return &currReg.DE;
        else if (strcmp("HL", registerName)) return &currReg.HL;

        return &incorrectCodeWord;
    }

    BYTE fetchByte(WORD &cycles, RAM_UNIT ram) {
        BYTE data = ram.readAddress(PC);
        PC++;
        cycles-=3;
        return data;
    }

    void startCycle(WORD cycles, RAM_UNIT ram) {
        while (cycles>0) {
            BYTE opcode = fetchByte(cycles, ram);
            cycles--;

            printf("Byte %d: %d\n", PC-1, opcode);

            // Decode the opcode
        }
        
    }

};
