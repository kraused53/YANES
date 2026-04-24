#include "core/cpu/CPU.h"
#include "core/bus/Bus.h"
#include <Logger.h>
#include <format>
#include <iostream>

// Housekeeping
CPU::CPU() {
    using a = CPU;
	opcode_table =  {
		{ "BRK", &a::BRK, &a::IMP, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::UNI, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::UNI, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::UNI, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::UNI, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::UNI, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::UNI, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::UNI, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::UNI, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::UNI, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::UNI, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::UNI, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::UNI, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::UNI, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::UNI, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::UNI, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::UNI, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::UNI, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::UNI, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::UNI, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::UNI, &a::IMP, 5 },{ "???", &a::UNI, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::UNI, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::UNI, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::UNI, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::UNI, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::UNI, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::UNI, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::UNI, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::UNI, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::UNI, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::UNI, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::UNI, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::UNI, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::UNI, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::UNI, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::UNI, &a::IMP, 7 },
	};

    reset();
}

CPU::~CPU() {}

// Bus
uint8_t CPU::read( uint16_t addr ) { return bus->read( addr ); }
void CPU::write( uint16_t addr, uint8_t data ) { bus->write( addr, data ); }

uint8_t CPU::fetch_byte( void ) {
    uint8_t ret = read( PC );
    PC++;
    return ret;
}

uint16_t CPU::fetch_word( void ) {
    uint8_t lo = fetch_byte();
    uint8_t hi = fetch_byte();
    return ( hi << 8 ) | lo;
}

void CPU::push_byte_to_stack( uint8_t data ) {
    write( ( 0x0100 + SP ), data );
    SP--;
}


uint8_t CPU::pop_byte_from_stack( void ) {
    SP++;
    return read( 0x0100 + SP );
}


uint16_t CPU::get_nmi_vector( void ) {
    return ( read( 0xFFFB ) << 8 ) | read( 0xFFFA );
}

uint16_t CPU::get_rst_vector( void ) {
    return ( read( 0xFFFD ) << 8 ) | read( 0xFFFC );
}

uint16_t CPU::get_irq_vector( void ) {
    return ( read( 0xFFFF ) << 8 ) | read( 0xFFFE );
}

// Emulation
void CPU::reset() {
    // Registers
    A = 0x00;
    F = 0x24;
    X = 0x00;
    Y = 0x00;
    PC = 0xFFFC;
    SP = 0xFD;

    // Emulation
    opcode = 0x00;
    halted = false;
    error = false;
    cycles = 0;
    abs_addr = 0x0000;
    rel_addr = 0x0000;
}

void CPU::step()  { 
    // Fetch the next opcode from memory
    opcode = fetch_byte();


    // Fetch the number of cycles needed for given opcode
    cycles = opcode_table[opcode].cycles;

    // Apply the addressing mode for this opcode
    uint8_t aditional_cycle_one = (this->*opcode_table[opcode].addr_mode)();

    // Execute the opcode
    uint8_t aditional_cycle_two = (this->*opcode_table[opcode].operate)();

    cycles += ( aditional_cycle_one & aditional_cycle_two );

}

void CPU::irq()   { Logger::Err( "ERROR - irq" );   }

void CPU::nmi()   { Logger::Err( "ERROR - nmi" );   }

// Flags
bool CPU::get_flag( FLAGS f ) { return F & f; }

void CPU::set_flag( FLAGS f, bool value ) {
    if( value ) {
        F |= f;
    }else {
        F &= ~f;
    }
}

// Addressing Modes
/* Implied addressing - No memory needed */
uint8_t CPU::IMP() { return 0; }

/* Immediate mode - Store current PC and advance for next opcode */
uint8_t CPU::IMM() { 
    abs_addr = PC;
    PC++;
    return 0;
}

/* Zero Page - The data in the address after the opcode is a zeropage offset */
uint8_t CPU::ZP0() { 
    abs_addr = fetch_byte();
    abs_addr &= 0x00FF;

    return 0;
}

/* Zero Page With X-Offset - Same as ZP0, but add X */
uint8_t CPU::ZPX() { 
    abs_addr = fetch_byte() + X;
    abs_addr &= 0x00FF;

    return 0;
}

/* Zero Page With X-Offset - Same as ZP0, but add X */
uint8_t CPU::ZPY() { 
    abs_addr = fetch_byte() + Y;
    abs_addr &= 0x00FF;

    return 0;
}

/* Realative - The byte after opcode is a relative offset */
uint8_t CPU::REL() { 
    rel_addr = fetch_byte();

    if( rel_addr & 0x80 ) {
        rel_addr|= 0xFF00;
    }

    return 0;
 }

/* Absolute - Fetch a full word from memory */
uint8_t CPU::ABS() { 
    abs_addr = fetch_word();
    return 0;
 }

/* Absolute + X - Absolute offset by X */
uint8_t CPU::ABX() { 
    abs_addr = fetch_word();
    uint16_t check_page_crossing = abs_addr;

    abs_addr += X;

    // Add a clock cycle if adding X caused a page crossing
    if( ( abs_addr & 0xFF00 ) != ( check_page_crossing & 0xFF00 ) ) {
        return 1;
    }

    return 0;
}

/* Absolute + Y - Absolute offset by Y */
uint8_t CPU::ABY() { 
    abs_addr = fetch_word();
    uint16_t check_page_crossing = abs_addr;

    abs_addr += Y;

    // Add a clock cycle if adding Y caused a page crossing
    if( ( abs_addr & 0xFF00 ) != ( check_page_crossing & 0xFF00 ) ) {
        return 1;
    }

    return 0;
}

/* Indirect - A kind of pointer */
uint8_t CPU::IND() {

    // Next word in memory is used as an address to read a byte from
    uint16_t ptr = fetch_word();

    // Simulate page boundry bug
    if( ( ptr & 0x00FF ) == 0x00FF ) {
        abs_addr = ( read( ptr & 0xFF00 ) << 8 ) | read( ptr );
    } else {
        abs_addr = ( read( ptr + 1 ) << 8 ) | read( ptr );
    }

    return 0;
}

/* Indirect X - Pointer with X offset */
uint8_t CPU::IZX() { 
    uint16_t offset = fetch_byte();

    uint8_t lo = read( ( uint16_t ) ( offset + X )     & 0x00FF );
    uint8_t hi = read( ( uint16_t ) ( offset + X + 1 ) & 0x00FF );

    abs_addr = ( hi << 8 ) | lo;

    return 0;
}

/* Indirect Y - Pointer with Y offset */
uint8_t CPU::IZY() { 
    uint16_t offset = fetch_byte();

    uint8_t lo = read( offset & 0x00FF );
    uint8_t hi = read( ( offset + 1 ) & 0x00FF );

    abs_addr = ( hi << 8 ) | lo;
    abs_addr += Y;


    if( ( abs_addr & 0xFF00 ) != ( hi << 8 ) ) {
        return 1;
    }

    return 0;
}

// This function uses the address built in the above addressing modes to collect a byte of memory for a given operation
uint8_t CPU::collect( void ) {
    if( opcode_table[opcode].addr_mode == &CPU::IMP ) {
        return A;
    }

    return read( abs_addr );
}

// Opcodes
uint8_t CPU::UNI() {
    halted = true;
    error = true;
    return 1;
}

// Add with carry
uint8_t CPU::ADC() {
    uint8_t operand = collect();

    // Calculate add. Use word to catch overflow
    uint16_t tmp = A + operand;
    if( get_flag( C ) ) {
        tmp++;
    }

    set_flag( C, tmp > 0xFF );
    set_flag( Z, ( tmp & 0x00FF ) == 0 );
    set_flag( V, (~((uint16_t)A ^ (uint16_t)operand) & ((uint16_t)A ^ (uint16_t)tmp)) & 0x0080 );
    set_flag( N, tmp & 0x80 );

    A = tmp & 0xFF;

    return 1;
}

// Logical AND
uint8_t CPU::AND() {
    A = A & collect();

    set_flag( Z, A == 0 );
    set_flag( N, A & 0x80 );

    return 1;
}

// Arithmetic shift left
uint8_t CPU::ASL() { 
    operand = collect();

    tmp = operand << 1;

    set_flag( C, tmp > 0x00FF );
    set_flag( Z, ( tmp & 0x00FF ) == 0 );
    set_flag( N, tmp & 0x0080 );

    if ( opcode_table[opcode].addr_mode == &CPU::IMP ) {
        A = tmp & 0xFF;
    }else {
        write( abs_addr, ( tmp & 0xFF ) );
    }

    return 0;
}

// Branch when carry clear
uint8_t CPU::BCC() {
    // Skip if carry is set 
    if( get_flag( C ) ) {
        return 0;
    }

    // Will take min. 1 extra cycle
    cycles++;

    abs_addr = PC + rel_addr;

    // Extra cycle on page crossing
    if( ( abs_addr & 0xFF00 ) != ( PC & 0xFF00 ) ) {
        cycles++;
    }

    // Jump
    PC = abs_addr;

    return 0;
}

// Branch when carry set
uint8_t CPU::BCS() {
    // Skip if carry is not set 
    if( !get_flag( C ) ) {
        return 0;
    }

    // Will take min. 1 extra cycle
    cycles++;

    abs_addr = PC + rel_addr;

    // Extra cycle on page crossing
    if( ( abs_addr & 0xFF00 ) != ( PC & 0xFF00 ) ) {
        cycles++;
    }

    // Jump
    PC = abs_addr;

    return 0;
}

// Branch on equal ( zero set )
uint8_t CPU::BEQ() {
    
    if( !get_flag( Z ) ) {
        return 0;
    }

    // Will take min. 1 extra cycle
    cycles++;

    abs_addr = PC + rel_addr;

    // Extra cycle on page crossing
    if( ( abs_addr & 0xFF00 ) != ( PC & 0xFF00 ) ) {
        cycles++;
    }

    // Jump
    PC = abs_addr;

    return 0;
}

// Test bits
uint8_t CPU::BIT() { 
    operand = collect();

    tmp = A & operand;

    set_flag( Z, ( tmp & 0x00FF ) == 0 );
    set_flag( N, operand & ( 1 << 7 ) );
    set_flag( V, operand & ( 1 << 6 ) );

    return 0;
}

// Branch on neg
uint8_t CPU::BMI() {
    
    if( !get_flag( N ) ) {
        return 0;
    }

    // Will take min. 1 extra cycle
    cycles++;

    abs_addr = PC + rel_addr;

    // Extra cycle on page crossing
    if( ( abs_addr & 0xFF00 ) != ( PC & 0xFF00 ) ) {
        cycles++;
    }

    // Jump
    PC = abs_addr;

    return 0;
}

// Branch on equal ( zero clear )
uint8_t CPU::BNE() {
    
    if( get_flag( Z ) ) {
        return 0;
    }

    // Will take min. 1 extra cycle
    cycles++;

    abs_addr = PC + rel_addr;

    // Extra cycle on page crossing
    if( ( abs_addr & 0xFF00 ) != ( PC & 0xFF00 ) ) {
        cycles++;
    }

    // Jump
    PC = abs_addr;

    return 0;
}

// Branch on pos
uint8_t CPU::BPL() {
    
    if( get_flag( N ) ) {
        return 0;
    }

    // Will take min. 1 extra cycle
    cycles++;

    abs_addr = PC + rel_addr;

    // Extra cycle on page crossing
    if( ( abs_addr & 0xFF00 ) != ( PC & 0xFF00 ) ) {
        cycles++;
    }

    // Jump
    PC = abs_addr;

    return 0;
}

// Break - Software Interrupt
uint8_t CPU::BRK() {
    PC++; // Space provided to identify break

    push_byte_to_stack( ( PC >> 8 ) & 0x00FF );
    push_byte_to_stack( ( PC ) & 0x00FF );    

    push_byte_to_stack( F | B );

    set_flag( I, true );
    PC = get_irq_vector();

    return 0;
}

// Branch on no overflow
uint8_t CPU::BVC() {
    
    if( get_flag( V ) ) {
        return 0;
    }

    // Will take min. 1 extra cycle
    cycles++;

    abs_addr = PC + rel_addr;

    // Extra cycle on page crossing
    if( ( abs_addr & 0xFF00 ) != ( PC & 0xFF00 ) ) {
        cycles++;
    }

    // Jump
    PC = abs_addr;

    return 0;
}

// Branch on overflow
uint8_t CPU::BVS() {
    
    if( !get_flag( V ) ) {
        return 0;
    }

    // Will take min. 1 extra cycle
    cycles++;

    abs_addr = PC + rel_addr;

    // Extra cycle on page crossing
    if( ( abs_addr & 0xFF00 ) != ( PC & 0xFF00 ) ) {
        cycles++;
    }

    // Jump
    PC = abs_addr;

    return 0;
}

/* Clear Carry Bit */
uint8_t CPU::CLC() { 
    set_flag( C, false );
    return 0;
}

// Clear decimal
uint8_t CPU::CLD() { 
    set_flag( D, false );
    return 0;
}

// Clear interrupt
uint8_t CPU::CLI() { 
    set_flag( I, false );
    return 0;
}

// Clear overflow
uint8_t CPU::CLV() { 
    set_flag( V, false );
    return 0;
}

// Compare A
uint8_t CPU::CMP() { 
    
    operand = collect();

    tmp = ( uint16_t ) A - operand;

    set_flag(C, A >= operand );
	set_flag(Z, ( tmp & 0x00FF ) == 0x0000 );
	set_flag(N, tmp & 0x0080 );

    return 1;
}

// Compare X
uint8_t CPU::CPX() { 
    
    operand = collect();

    tmp = ( uint16_t ) X - operand;

    set_flag(C, X >= operand );
	set_flag(Z, ( tmp & 0x00FF ) == 0x0000 );
	set_flag(N, tmp & 0x0080 );

    return 0;
}

// Compare Y
uint8_t CPU::CPY() { 
    
    operand = collect();

    tmp = ( uint16_t ) Y - operand;

    set_flag(C, Y >= operand );
	set_flag(Z, ( tmp & 0x00FF ) == 0x0000 );
	set_flag(N, tmp & 0x0080 );

    return 0;
}

// DEC mem
uint8_t CPU::DEC() { 

    tmp = collect() - 1;
    write( abs_addr, tmp & 0xFF );
    
	set_flag(Z, ( tmp & 0x00FF ) == 0 );
	set_flag(N, tmp & 0x0080 );

    return 0;
}

// DEC X
uint8_t CPU::DEX() { 
    X--;
    
	set_flag(Z, X == 0 );
	set_flag(N, X & 0x80 );

    return 0;
}

// DEC Y
uint8_t CPU::DEY() { 
    Y--;
    
	set_flag(Z, Y == 0 );
	set_flag(N, Y & 0x80 );

    return 0;
}

// ExOR
uint8_t CPU::EOR() { 
    A = A ^ collect();

    set_flag( Z, A == 0 );
    set_flag( N, A & 0x80 );

    return 1;
}

// Increment mem
uint8_t CPU::INC() { 
    tmp = collect() + 1;
    write( abs_addr, tmp & 0xFF );
    
	set_flag(Z, ( tmp & 0x00FF ) == 0 );
	set_flag(N, tmp & 0x0080 );

    return 0;
}

// Increment X
uint8_t CPU::INX() { 
    X++;
    
	set_flag(Z, X == 0 );
	set_flag(N, X & 0x80 );

    return 0;
}

// Increment Y
uint8_t CPU::INY() { 
    Y++;
    
	set_flag(Z, Y == 0 );
	set_flag(N, Y & 0x80 );

    return 0;
}

// Jump
uint8_t CPU::JMP() { 
    PC = abs_addr;
    return 0;
}

// Jump to sub routine
uint8_t CPU::JSR() { 
    PC--;

    push_byte_to_stack( ( PC >> 8 ) & 0x00FF );
    push_byte_to_stack( ( PC ) & 0x00FF );  

    PC = abs_addr;

    return 0;
}

// Load A
uint8_t CPU::LDA() { 
    A = collect();

	set_flag(Z, A == 0 );
	set_flag(N, A & 0x80 );

    return 1;
}

// Load X
uint8_t CPU::LDX() { 
    X = collect();

	set_flag(Z, X == 0 );
	set_flag(N, X & 0x80 );

    return 1;
}

// Load Y
uint8_t CPU::LDY() { 
    Y = collect();

	set_flag(Z, Y == 0 );
	set_flag(N, Y & 0x80 );

    return 1;
}

// Logical shift right
uint8_t CPU::LSR() { 
    operand = collect();

    set_flag( C, operand & 0x0001 );

    tmp = operand >> 1;

    set_flag( Z, ( tmp & 0x00FF ) == 0 );
    set_flag( N, tmp & 0x0080 );

    if( opcode_table[opcode].addr_mode == &CPU::IMP ) {
        A = tmp & 0xFF;
    }else {
        write( abs_addr, tmp & 0xFF );
    }
    
    return 0;
}

/* NOP - Do nothing for 2 cycles */
uint8_t CPU::NOP() { 
    switch (opcode) {
        case 0x1C:
        case 0x3C:
        case 0x5C:
        case 0x7C:
        case 0xDC:
        case 0xFC:
            return 1;
            break;
	}
	return 0;
}

uint8_t CPU::ORA() {
    
    A |= collect();

    set_flag( Z, A == 0x00 );
    set_flag( N, A  & 0x80 );

    return 1;
}

uint8_t CPU::PHA() { 
    push_byte_to_stack( A );
    return 0;
}

uint8_t CPU::PHP() { 

    push_byte_to_stack( F | B | U );

    return 0;
}

uint8_t CPU::PLA() { 
    return UNI();
}

uint8_t CPU::PLP() { 
    return UNI();
}

uint8_t CPU::ROL() { 
    return UNI();
}

uint8_t CPU::ROR() { 
    return UNI();
}

uint8_t CPU::RTI() { 
    return UNI();
}

uint8_t CPU::RTS() { 
    return UNI();
}

uint8_t CPU::SBC() {
    operand = ((uint16_t) collect() ) ^ 0x00FF;

    tmp = (uint16_t) A + operand;
    if( get_flag( C ) ) {
        tmp++;
    }

    set_flag( C, tmp & 0xFF00 );
    set_flag( Z, ( tmp & 0x00FF ) == 0);
    set_flag( V, ( tmp ^ (uint16_t)A ) & ( tmp ^ operand ) & 0x0080 );
    set_flag( N, tmp & 0x80 );

    A = tmp & 0x00FF;

    return 1;
}

uint8_t CPU::SEC() { 
    return UNI();
}

uint8_t CPU::SED() { 
    return UNI();
}

uint8_t CPU::SEI() { 
    return UNI();
}

uint8_t CPU::STA() { 
    return UNI();
}

uint8_t CPU::STX() { 
    return UNI();
}

uint8_t CPU::STY() { 
    return UNI();
}

uint8_t CPU::TAX() { 
    return UNI();
}

uint8_t CPU::TAY() { 
    return UNI();
}

uint8_t CPU::TSX() { 
    return UNI();
}

uint8_t CPU::TXA() { 
    return UNI();
}

uint8_t CPU::TXS() { 
    return UNI();
}

/* Transfer Y -> A */
uint8_t CPU::TYA() {
    A = Y;
    set_flag( N, ( A & 0x80 ) ); 
    set_flag( Z, ( A ==   0 ) ); 
    return 0;
}