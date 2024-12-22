// Sizes
using BYTE = char;
using WORD = short;
using RAM = char*;

struct CPU_UNIT {
    // Registers
    union statusReg {
        struct {
            BYTE S: 1;
            BYTE Z: 1;
            BYTE unused1: 1;
            BYTE H: 1;
            BYTE unused0: 1;
            BYTE PV: 1;
            BYTE N: 1;
            BYTE C: 1;
        };
        BYTE flags;
    };

    struct regs {
        union { struct { BYTE B; BYTE C; }; WORD BC;};
        union { struct { BYTE D; BYTE E; }; WORD DE;};
        union { struct { BYTE H; BYTE L; }; WORD HL;};
        union { struct { BYTE A; statusReg F; }; WORD AF;}; // Accumulator + Flags
    };

    struct s_regs {
        BYTE I, R;
        WORD IX, IY, SP, PC;
    };

    // Components
    regs bRegs;
    regs aRegs;
    s_regs sRegs;
    regs currReg = bRegs;
    RAM ram;

    WORD addrBus;
    BYTE dataBus;

    void initCPU(RAM outerRAM) {
        for (int i=0; i<sizeof(outerRAM); i++) ram[i]==outerRAM[i];

        sRegs.I=sRegs.R=0;
        sRegs.IX=sRegs.IY=sRegs.SP=sRegs.PC=0;
        bRegs.F.flags=aRegs.F.flags=0;
        bRegs.BC=bRegs.DE=bRegs.HL=0;
        aRegs.BC=aRegs.DE=aRegs.HL=0;
    }

    BYTE fetchByte(WORD cycles) {
        int *ptr = &cycles;

        BYTE data = dataBus;
        sRegs.PC++;
        *ptr-=4;
        return data;
    }

    // Opcodes
    static constexpr BYTE INS_INC_B = 0x04;
    static constexpr BYTE INS_INC_C = 0x14;
    static constexpr BYTE INS_INC_D = 0x24;
    static constexpr BYTE INS_INC_E = 0x34;
    static constexpr BYTE INS_INC_H = 0x44;
    static constexpr BYTE INS_INC_L = 0x54;
    static constexpr BYTE INS_INC_HL_P = 0x64;
    static constexpr BYTE INS_INC_A = 0x74;

    static constexpr BYTE INS_INC_BC = 0x03;
    static constexpr BYTE INS_INC_DE = 0x13;
    static constexpr BYTE INS_INC_HL = 0x23;
    static constexpr BYTE INS_INC_SP = 0x33;

    void startCycle(WORD cycles) {
        while (cycles>0) {
            printf("%d\n", cycles);
            BYTE instr = fetchByte(cycles);
            switch (instr)
            {
            case INS_INC_B: currReg.B++; break;
            case INS_INC_C: currReg.C++; break;
            case INS_INC_D: currReg.D++; break;
            case INS_INC_E: currReg.E++; break;
            case INS_INC_H: currReg.H++; break;
            case INS_INC_L: currReg.L++; break;
            case INS_INC_HL_P: ram[currReg.HL]++; break;
            case INS_INC_A: currReg.A++; break;

            case INS_INC_BC: currReg.BC++; break;
            case INS_INC_DE: currReg.DE++; break;
            case INS_INC_HL: currReg.HL++; break;
            case INS_INC_SP: sRegs.SP++; break;
            
            default:
                break;
            }
        }
    }
};
