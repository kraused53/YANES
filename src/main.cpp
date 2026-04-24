#include <iostream>
#include <map>
#include <cstdint>
#include <string>

#include "core/bus/Bus.h"

int main( int argc, char** argv ) {
    Bus nes;
    
    nes.write( 0xC000, 0x4C );
    nes.write( 0xC001, 0xF5 );
    nes.write( 0xC002, 0xC5 );

    nes.cpu.PC = 0xC000;

    nes.clock();
    nes.clock();

    return EXIT_SUCCESS;
}