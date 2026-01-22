#include "cpu_6502.h"
#include "../Logger/Logger.h"

#include <format>

cpu_6502::cpu_6502( void ) {
    Logger::Log( "Initializing CPU..." );
    reset();

    memory.resize( 64 * 1024 );
    for( int i = 0; i < ( 64 * 1024 ); i++ ) {
        memory[i] = 0x00;
    }

    using c = cpu_6502;
    lookup = {
        // 0x00 -> 0x0F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x00
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x01
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x02
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x03
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x04
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x05
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x06
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x07
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x08
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x09
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x0A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x0B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x0C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x0D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x0E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x0F
        // 0x10 -> 0x1F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x10
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x11
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x12
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x13
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x14
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x15
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x16
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x17
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x18
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x19
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x1A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x1B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x1C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x1D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x1E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x1F
        // 0x20 -> 0x2F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x20
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x21
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x22
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x23
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x24
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x25
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x26
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x27
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x28
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x29
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x2A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x2B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x2C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x2D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x2E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x2F
        // 0x30 -> 0x3F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x30
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x31
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x32
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x33
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x34
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x35
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x36
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x37
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x38
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x39
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x3A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x3B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x3C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x3D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x3E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x3F
        // 0x40 -> 0x4F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x40
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x41
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x42
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x43
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x44
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x45
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x46
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x47
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x48
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x49
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x4A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x4B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x4C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x4D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x4E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x4F
        // 0x50 -> 0x5F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x50
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x51
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x52
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x53
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x54
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x55
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x56
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x57
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x58
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x59
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x5A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x5B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x5C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x5D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x5E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x5F
        // 0x60 -> 0x6F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x60
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x61
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x62
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x63
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x64
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x65
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x66
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x67
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x68
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x69
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x6A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x6B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x6C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x6D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x6E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x6F
        // 0x70 -> 0x7F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x70
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x71
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x72
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x73
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x74
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x75
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x76
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x77
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x78
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x79
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x7A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x7B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x7C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x7D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x7E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x7F
        // 0x80 -> 0x8F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x80
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x81
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x82
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x83
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x84
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x85
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x86
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x87
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x88
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x89
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x8A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x8B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x8C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x8D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x8E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x8F
        // 0x90 -> 0x9F
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x90
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x91
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x92
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x93
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x94
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x95
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x96
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x97
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x98
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x99
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x9A
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x9B
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x9C
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x9D
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x9E
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0x9F
        // 0xA0 -> 0xAF
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA0
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA1
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA2
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA3
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA4
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA5
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA6
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA7
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA8
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xA9
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xAA
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xAB
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xAC
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xAD
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xAE
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xAF
        // 0xB0 -> 0xBF
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB0
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB1
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB2
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB3
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB4
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB5
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB6
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB7
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB8
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xB9
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xBA
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xBB
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xBC
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xBD
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xBE
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xBF
        // 0xC0 -> 0xCF
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC0
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC1
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC2
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC3
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC4
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC5
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC6
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC7
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC8
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xC9
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xCA
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xCB
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xCC
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xCD
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xCE
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xCF
        // 0xD0 -> 0xDF
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD0
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD1
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD2
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD3
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD4
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD5
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD6
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD7
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD8
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xD9
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xDA
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xDB
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xDC
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xDD
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xDE
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xDF
        // 0xE0 -> 0xEF
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE0
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE1
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE2
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE3
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE4
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE5
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE6
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE7
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE8
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xE9
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xEA
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xEB
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xEC
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xED
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xEE
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xEF
        // 0xF0 -> 0xFF
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF0
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF1
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF2
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF3
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF4
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF5
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF6
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF7
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF8
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xF9
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xFA
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xFB
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xFC
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xFD
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xFE
        { "Unimplemented Opcode", &c::UNI, &c::IMP, 1 }, // 0xFF
    };
}

cpu_6502::~cpu_6502( void ) {
    // Nothing to do right now
}

/* Memory */
uint8_t cpu_6502::read_byte( uint16_t addr ) { 
    return memory[addr];
}

uint16_t cpu_6502::read_word( uint16_t addr ) { 
    return ( memory[addr] << 8 ) | memory[addr];
}

uint8_t cpu_6502::fetch_byte( void ) { 
    uint8_t ret = memory[PC];
    PC++;
    return ret;
}

uint16_t cpu_6502::fetch_word( void ) {
    uint8_t lo = fetch_byte();
    uint8_t hi = fetch_byte();

    return ( hi << 8 ) | lo;
}

/* Flags */
bool cpu_6502::get_flag( FLAG f ) { 
    return F & f;
}

void cpu_6502::set_flag( FLAG f, bool val ) { 
    if ( val ) {
        F |= f;
    }else {
        F &= ~f;
    }  
}

/* Emulation */
void cpu_6502::step( void ) {
    opcode = fetch_byte();

    // Handle addressing modes
    ( this->*lookup[opcode].mode )();
    // Execute opcode
    ( this->*lookup[opcode].operate )();

    cycles = ( this->lookup[opcode].cycles );
}

void cpu_6502::reset( void ) {
    A = 0x00;
    X = 0x00;
    Y = 0x00;
    SP = 0x00;
    PC = 0xFFFC;
    opcode = 0x00;
    cycles = 0;
    error = false;
    halted = false;
}

/* Addressing Modes */
void cpu_6502::IMP( void ) { UNI(); }
void cpu_6502::IMM( void ) { UNI(); }	
void cpu_6502::ZP0( void ) { UNI(); }
void cpu_6502::ZPX( void ) { UNI(); }	
void cpu_6502::ZPY( void ) { UNI(); }
void cpu_6502::REL( void ) { UNI(); }
void cpu_6502::ABS( void ) { UNI(); }
void cpu_6502::ABX( void ) { UNI(); }	
void cpu_6502::ABY( void ) { UNI(); }
void cpu_6502::IND( void ) { UNI(); }	
void cpu_6502::IZX( void ) { UNI(); }
void cpu_6502::IZY( void ) { UNI(); }

/* Opcodes */
void cpu_6502::UNI( void ) {
    error = true;
    halted = true;
    Logger::Err( std::format( "Unimplemented Opcode 0x{:02X} at ${:04X}", opcode, PC - 1 ) );
}