#include <gtest/gtest.h>
#include "core/cpu/CPU.h"
#include "core/bus/IBus.h"

#include <Logger.h>
#include <format>

#include <array>

namespace TestBus {
    class Bus : public IBus {
        public:
            // Fake memory
            std::array<uint8_t, 64 * 1024> ram;
            
            Bus() { 
                // Connect CPU to communication bus
                cpu.ConnectBus(this);

                reset();
            }

            // IBus systems
            CPU cpu;

        uint8_t read(uint16_t addr) override {
            return ram[addr];
        }

        void write(uint16_t addr, uint8_t data) override {
            ram[addr] = data;
        }

        void reset() override {
            // Clear RAM contents, just in case :P
            for (auto &i : ram) i = 0x00;

            cpu.reset();
        }

        void clock() override {
            cpu.step();
        }
    };
}

/* JSON TESTING */
#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
bool json_test( std::string pth, TestBus::Bus *b );
bool test_passed( json data, TestBus::Bus *b, int test_number );
void load_initial_state( json data, TestBus::Bus *b );


TEST( OpCodes, TestBusMemoryAccess ) {
    TestBus::Bus bus;

    bus.cpu.write( 0x0000, 0x12 );
    bus.cpu.write( 0x1234, 0x34 );
    bus.cpu.write( 0x5678, 0x56 );
    bus.cpu.write( 0xF0F0, 0x78 );
    bus.cpu.write( 0xFFFF, 0x90 );

    EXPECT_EQ( bus.cpu.read( 0x0000 ), 0x12 );
    EXPECT_EQ( bus.cpu.read( 0x1234 ), 0x34 );
    EXPECT_EQ( bus.cpu.read( 0x5678 ), 0x56 );
    EXPECT_EQ( bus.cpu.read( 0xF0F0 ), 0x78 );
    EXPECT_EQ( bus.cpu.read( 0xFFFF ), 0x90 );
    
}

// Break
TEST( OpCodes, OP_00 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/00.json", &b ) ); }

// ADC
TEST( OpCodes, OP_61 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/61.json", &b ) ); }
TEST( OpCodes, OP_65 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/65.json", &b ) ); }
TEST( OpCodes, OP_69 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/69.json", &b ) ); }
TEST( OpCodes, OP_6d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/6d.json", &b ) ); }
TEST( OpCodes, OP_71 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/71.json", &b ) ); }
TEST( OpCodes, OP_75 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/75.json", &b ) ); }
TEST( OpCodes, OP_79 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/79.json", &b ) ); }
TEST( OpCodes, OP_7d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/7d.json", &b ) ); }

// AND
TEST( OpCodes, OP_21 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/21.json", &b ) ); }
TEST( OpCodes, OP_25 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/25.json", &b ) ); }
TEST( OpCodes, OP_29 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/29.json", &b ) ); }
TEST( OpCodes, OP_2d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/2d.json", &b ) ); }
TEST( OpCodes, OP_31 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/31.json", &b ) ); }
TEST( OpCodes, OP_35 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/35.json", &b ) ); }
TEST( OpCodes, OP_39 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/39.json", &b ) ); }
TEST( OpCodes, OP_3d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/3d.json", &b ) ); }

// ASL
TEST( OpCodes, OP_06 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/06.json", &b ) ); }
TEST( OpCodes, OP_0a ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/0a.json", &b ) ); }
TEST( OpCodes, OP_0e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/0e.json", &b ) ); }
TEST( OpCodes, OP_16 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/16.json", &b ) ); }
TEST( OpCodes, OP_1e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/1e.json", &b ) ); }

// BCC
TEST( OpCodes, OP_90 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/90.json", &b ) ); }

// BCS
TEST( OpCodes, OP_b0 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/b0.json", &b ) ); }

// BEQ
TEST( OpCodes, OP_f0 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/f0.json", &b ) ); }

// BIT
TEST( OpCodes, OP_24 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/24.json", &b ) ); }
TEST( OpCodes, OP_2c ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/2c.json", &b ) ); }

// BMI
TEST( OpCodes, OP_30 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/30.json", &b ) ); }

// BNE
TEST( OpCodes, OP_d0 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/d0.json", &b ) ); }

// BPL
TEST( OpCodes, OP_10 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/10.json", &b ) ); }

// BVC
TEST( OpCodes, OP_50 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/50.json", &b ) ); }

// BVS
TEST( OpCodes, OP_70 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/70.json", &b ) ); }

// CLC
TEST( OpCodes, OP_18 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/18.json", &b ) ); }

// CLD
TEST( OpCodes, OP_d8 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/d8.json", &b ) ); }

// CLI
TEST( OpCodes, OP_58 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/58.json", &b ) ); }

// CLV
TEST( OpCodes, OP_b8 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/b8.json", &b ) ); }

// CMP
TEST( OpCodes, OP_c9 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/c9.json", &b ) ); }
TEST( OpCodes, OP_c5 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/c5.json", &b ) ); }
TEST( OpCodes, OP_d5 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/d5.json", &b ) ); }
TEST( OpCodes, OP_cd ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/cd.json", &b ) ); }
TEST( OpCodes, OP_dd ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/dd.json", &b ) ); }
TEST( OpCodes, OP_d9 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/d9.json", &b ) ); }
TEST( OpCodes, OP_c1 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/c1.json", &b ) ); }
TEST( OpCodes, OP_d1 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/d1.json", &b ) ); }

// CPX
TEST( OpCodes, OP_e0 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/e0.json", &b ) ); }
TEST( OpCodes, OP_e4 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/e4.json", &b ) ); }
TEST( OpCodes, OP_ec ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ec.json", &b ) ); }

// CPY
TEST( OpCodes, OP_c0 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/c0.json", &b ) ); }
TEST( OpCodes, OP_c4 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/c4.json", &b ) ); }
TEST( OpCodes, OP_cc ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/cc.json", &b ) ); }

// DEC
TEST( OpCodes, OP_c6 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/c6.json", &b ) ); }
TEST( OpCodes, OP_d6 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/d6.json", &b ) ); }
TEST( OpCodes, OP_ce ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ce.json", &b ) ); }
TEST( OpCodes, OP_de ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/de.json", &b ) ); }

// DEX
TEST( OpCodes, OP_ca ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ca.json", &b ) ); }

// DEY
TEST( OpCodes, OP_88 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/88.json", &b ) ); }

// EOR
TEST( OpCodes, OP_49 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/49.json", &b ) ); }
TEST( OpCodes, OP_45 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/45.json", &b ) ); }
TEST( OpCodes, OP_55 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/55.json", &b ) ); }
TEST( OpCodes, OP_4d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/4d.json", &b ) ); }
TEST( OpCodes, OP_5d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/5d.json", &b ) ); }
TEST( OpCodes, OP_59 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/59.json", &b ) ); }
TEST( OpCodes, OP_41 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/41.json", &b ) ); }
TEST( OpCodes, OP_51 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/51.json", &b ) ); }

// INC
TEST( OpCodes, OP_e6 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/e6.json", &b ) ); }
TEST( OpCodes, OP_f6 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/f6.json", &b ) ); }
TEST( OpCodes, OP_ee ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ee.json", &b ) ); }
TEST( OpCodes, OP_fe ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/fe.json", &b ) ); }

// INX
TEST( OpCodes, OP_e8 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/e8.json", &b ) ); }

// INY
TEST( OpCodes, OP_c8 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/c8.json", &b ) ); }

// JMP
TEST( OpCodes, OP_4c ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/4c.json", &b ) ); }
TEST( OpCodes, OP_6c ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/6c.json", &b ) ); }

// JSR
TEST( OpCodes, OP_20 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/20.json", &b ) ); }

// LDA
TEST( OpCodes, OP_a9 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/a9.json", &b ) ); }
TEST( OpCodes, OP_a5 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/a5.json", &b ) ); }
TEST( OpCodes, OP_b5 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/b5.json", &b ) ); }
TEST( OpCodes, OP_ad ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ad.json", &b ) ); }
TEST( OpCodes, OP_bd ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/bd.json", &b ) ); }
TEST( OpCodes, OP_b9 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/b9.json", &b ) ); }
TEST( OpCodes, OP_a1 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/a1.json", &b ) ); }
TEST( OpCodes, OP_b1 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/b1.json", &b ) ); }

// LDX
TEST( OpCodes, OP_a2 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/a2.json", &b ) ); }
TEST( OpCodes, OP_a6 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/a6.json", &b ) ); }
TEST( OpCodes, OP_b6 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/b6.json", &b ) ); }
TEST( OpCodes, OP_ae ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ae.json", &b ) ); }
TEST( OpCodes, OP_be ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/be.json", &b ) ); }

// LDY
TEST( OpCodes, OP_a0 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/a0.json", &b ) ); }
TEST( OpCodes, OP_a4 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/a4.json", &b ) ); }
TEST( OpCodes, OP_b4 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/b4.json", &b ) ); }
TEST( OpCodes, OP_ac ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ac.json", &b ) ); }
TEST( OpCodes, OP_bc ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/bc.json", &b ) ); }

// LSR
TEST( OpCodes, OP_4a ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/4a.json", &b ) ); }
TEST( OpCodes, OP_46 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/46.json", &b ) ); }
TEST( OpCodes, OP_56 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/56.json", &b ) ); }
TEST( OpCodes, OP_4e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/4e.json", &b ) ); }
TEST( OpCodes, OP_5e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/5e.json", &b ) ); }

// NOP
TEST( OpCodes, OP_ea ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ea.json", &b ) ); }

// ORA
TEST( OpCodes, OP_01 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/01.json", &b ) ); }
TEST( OpCodes, OP_05 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/05.json", &b ) ); }
TEST( OpCodes, OP_09 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/09.json", &b ) ); }
TEST( OpCodes, OP_0d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/0d.json", &b ) ); }
TEST( OpCodes, OP_11 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/11.json", &b ) ); }
TEST( OpCodes, OP_15 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/15.json", &b ) ); }
TEST( OpCodes, OP_19 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/19.json", &b ) ); }
TEST( OpCodes, OP_1d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/1d.json", &b ) ); }

// PHA
TEST( OpCodes, OP_48 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/48.json", &b ) ); }

// PHP
TEST( OpCodes, OP_08 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/08.json", &b ) ); }

// PLA
TEST( OpCodes, OP_68 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/68.json", &b ) ); }

// PLP
TEST( OpCodes, OP_28 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/28.json", &b ) ); }

// ROL
TEST( OpCodes, OP_2a ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/2a.json", &b ) ); }
TEST( OpCodes, OP_26 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/26.json", &b ) ); }
TEST( OpCodes, OP_36 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/36.json", &b ) ); }
TEST( OpCodes, OP_2e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/2e.json", &b ) ); }
TEST( OpCodes, OP_3e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/3e.json", &b ) ); }

// ROR
TEST( OpCodes, OP_6a ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/6a.json", &b ) ); }
TEST( OpCodes, OP_66 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/66.json", &b ) ); }
TEST( OpCodes, OP_76 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/76.json", &b ) ); }
TEST( OpCodes, OP_6e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/6e.json", &b ) ); }
TEST( OpCodes, OP_7e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/7e.json", &b ) ); }

// RTI
TEST( OpCodes, OP_40 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/40.json", &b ) ); }

// RTS
TEST( OpCodes, OP_60 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/60.json", &b ) ); }

// SBC
TEST( OpCodes, OP_e1 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/e1.json", &b ) ); }
TEST( OpCodes, OP_e5 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/e5.json", &b ) ); }
TEST( OpCodes, OP_e9 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/e9.json", &b ) ); }
TEST( OpCodes, OP_ed ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ed.json", &b ) ); }
TEST( OpCodes, OP_f1 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/f1.json", &b ) ); }
TEST( OpCodes, OP_f5 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/f5.json", &b ) ); }
TEST( OpCodes, OP_f9 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/f9.json", &b ) ); }
TEST( OpCodes, OP_fd ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/fd.json", &b ) ); }

// SEC
TEST( OpCodes, OP_38 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/38.json", &b ) ); }

// SED
TEST( OpCodes, OP_f8 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/f8.json", &b ) ); }

// SEI
TEST( OpCodes, OP_78 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/78.json", &b ) ); }

// STA
TEST( OpCodes, OP_85 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/85.json", &b ) ); }
TEST( OpCodes, OP_95 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/95.json", &b ) ); }
TEST( OpCodes, OP_8d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/8d.json", &b ) ); }
TEST( OpCodes, OP_9d ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/9d.json", &b ) ); }
TEST( OpCodes, OP_99 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/99.json", &b ) ); }
TEST( OpCodes, OP_81 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/81.json", &b ) ); }
TEST( OpCodes, OP_91 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/91.json", &b ) ); }

// STX
TEST( OpCodes, OP_86 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/86.json", &b ) ); }
TEST( OpCodes, OP_96 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/96.json", &b ) ); }
TEST( OpCodes, OP_8e ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/8e.json", &b ) ); }

// STY
TEST( OpCodes, OP_84 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/84.json", &b ) ); }
TEST( OpCodes, OP_94 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/94.json", &b ) ); }
TEST( OpCodes, OP_8c ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/8c.json", &b ) ); }

// TAX
TEST( OpCodes, OP_aa ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/aa.json", &b ) ); }

// TAY
TEST( OpCodes, OP_a8 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/a8.json", &b ) ); }

// TSX
TEST( OpCodes, OP_ba ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/ba.json", &b ) ); }

// TXA
TEST( OpCodes, OP_8a ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/8a.json", &b ) ); }

// TXS
TEST( OpCodes, OP_9a ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/9a.json", &b ) ); }

// TYA
TEST( OpCodes, OP_98 ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/98.json", &b ) ); }

/*
	TEST( OpCodes, OP_## ) { TestBus::Bus b; EXPECT_TRUE( json_test( "../json_tests/##.json", &b ) ); }
*/
// JSON Framework
void load_initial_state( json data, TestBus::Bus *b ) {
	// Load registers
	b->cpu.A  =  uint8_t( data["initial"]["a"] );
	b->cpu.F  =  uint8_t( data["initial"]["p"] );
	b->cpu.X  =  uint8_t( data["initial"]["x"] );
	b->cpu.Y  =  uint8_t( data["initial"]["y"] );
	b->cpu.PC = uint16_t( data["initial"]["pc"] );
	b->cpu.SP = uint16_t( data["initial"]["s"] );

	// Load memory
	for ( auto& i : data["initial"]["ram"] ) {
		b->ram[uint16_t( i[0] )] = uint8_t( i[1] );
	}
}

bool test_passed( json data, TestBus::Bus *b, int test_number ) {
    
	// Check Register A
	if ( b->cpu.A != uint8_t( data["final"]["a"] ) ) { Logger::Err( std::format( "A: {:02X} -> should be {:02X}", b->cpu.A, ( uint8_t ) data["final"]["a"] ) ); return false; }
	// Check Register F
	if ( b->cpu.F != uint8_t( data["final"]["p"] ) ) { Logger::Err( std::format( "F: {:08b} -> should be {:08b}", b->cpu.F, ( uint8_t ) data["final"]["p"] ) ); return false; }
	// Check Register X
	if ( b->cpu.X != uint8_t( data["final"]["x"] ) ) { Logger::Err( std::format( "X: {:02X} -> should be {:02X}", b->cpu.X, ( uint8_t ) data["final"]["x"] ) ); return false; }
	// Check Register Y
	if ( b->cpu.Y != uint8_t( data["final"]["y"] ) ) { Logger::Err( std::format( "Y: {:02X} -> should be {:02X}", b->cpu.Y, ( uint8_t ) data["final"]["y"] ) ); return false; }
	
	// Check PC
	if ( b->cpu.PC != uint16_t( data["final"]["pc"] ) ) { Logger::Err( std::format( "PC: {:04X} -> should be {:04X}", b->cpu.PC, ( uint16_t ) data["final"]["pc"] ) ); return false; }
	// Check SP
	if ( b->cpu.SP != uint8_t( data["final"]["s"] ) ) { Logger::Err( std::format( "SP: {:02X} -> should be {:02X}", b->cpu.SP, ( uint8_t ) data["final"]["s"] ) ); return false; }


	// Check ram
	for ( auto& i : data["final"]["ram"] ) {
		if ( b->ram[uint16_t( i[0]) ] != uint8_t( i[1] ) ) {
            Logger::Err( std::format( "ram[0x{:04X}]: {:02X} -> should be {:02X}", uint16_t(i[0]), b->ram[uint16_t( i[0]) ], uint8_t(i[1]) ) );
			return false;
		}
	}

    // If cpu has error, test failed
    if( b->cpu.error ) {
        return false;
    }

	return true;
}

bool json_test( std::string pth, TestBus::Bus *b ) {

	std::ifstream f( pth );
	json data = json::parse( f );
	f.close();

	// Tests statistics
	int i = 0;
	int num_passed = 0;

	// Cycle trough all tests in file
	for ( auto &test : data ) {

		// Load initial cpu/ram state
		load_initial_state( test, b );

		// Step cpu
		b->clock();

		if ( !test_passed( test, b, i ) ) {
            Logger::Err( std::format( "Failed test #{:d}", i ) );
            return false;
		}

		num_passed++;
		i++;
	}

    std::cout << "# Tests: " << num_passed << std::endl;

    return true;
}