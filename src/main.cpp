#include "./cpu_6502/cpu_6502.h"

int main( int argc, char** argv ) {

    cpu_6502 cpu;
    cpu.step();

    return 0;
}