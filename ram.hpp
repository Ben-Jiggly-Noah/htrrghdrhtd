// Sizes
using BYTE = char;
using WORD = short;

// Ram Unit
struct RAM {
    BYTE* initRam(WORD size) {
        return (BYTE*)malloc(((size_t)size)+1);
    }

    void clearRam(BYTE* RAM) {
        free(RAM);
        RAM=NULL;
    }
};