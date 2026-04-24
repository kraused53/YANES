#include <gtest/gtest.h>
#include "core/cpu/CPU.h"
#include "core/bus/Bus.h"

TEST( CPU, Initialization ) {
    Bus bus;

    EXPECT_EQ( bus.cpu.A,    0x00 );
    EXPECT_EQ( bus.cpu.X,    0x00 );
    EXPECT_EQ( bus.cpu.Y,    0x00 );
    EXPECT_EQ( bus.cpu.F,    0x24 );
    EXPECT_EQ( bus.cpu.SP,   0xFD );
    EXPECT_EQ( bus.cpu.PC, 0xFFFC );
}


TEST( CPU, Reset ) {
    Bus bus;

    bus.cpu.A  =   0xFF;
    bus.cpu.X  =   0xFF;
    bus.cpu.Y  =   0xFF;
    bus.cpu.F  =   0xFF;
    bus.cpu.SP =   0x00;
    bus.cpu.PC = 0xFF00;
    bus.cpu.reset();

    EXPECT_EQ( bus.cpu.A,    0x00 );
    EXPECT_EQ( bus.cpu.X,    0x00 );
    EXPECT_EQ( bus.cpu.Y,    0x00 );
    EXPECT_EQ( bus.cpu.F,    0x24 );
    EXPECT_EQ( bus.cpu.SP,   0xFD );
    EXPECT_EQ( bus.cpu.PC, 0xFFFC );
}