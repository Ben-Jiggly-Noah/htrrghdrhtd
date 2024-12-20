// Sizes
using BYTE = char;
using WORD = short;

struct CPU {
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
};