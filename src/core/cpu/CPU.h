#pragma once

#include <vector>
#include <cstdint>

class IBus;
class CPU {
    public:
        CPU();
        ~CPU();

        // System registers
        uint8_t   A;    // Accumulator
        uint8_t   F;    // Flags
        uint8_t   X;    // X-Index
        uint8_t   Y;    // Y-Index
        uint8_t  SP;    // Stack pointer
        uint16_t PC;    // Program Counter

        // Bus
        IBus *bus = nullptr;
        uint8_t read( uint16_t addr );
        void write( uint16_t addr, uint8_t data );
        void ConnectBus(IBus *n) { bus = n; }
        uint8_t fetch_byte( void );
        uint16_t fetch_word( void );

        // Stack
        void push_byte_to_stack( uint8_t data );
        uint8_t pop_byte_from_stack( void );

        // Interrupt Vectors
        uint16_t get_nmi_vector( void );
        uint16_t get_rst_vector( void );
        uint16_t get_irq_vector( void );

        // Emulation
        void reset();
        void step();
        void irq();
        void nmi();

        // Emulation Variables
        uint8_t opcode;
        uint16_t abs_addr;
        uint16_t rel_addr;
        uint16_t tmp;
        uint16_t operand;
        uint64_t cycles;
        bool halted;
        bool error;

    private:
        // Flags
        enum FLAGS {
            C = (1 << 0),	// Carry Bit
            Z = (1 << 1),	// Zero
            I = (1 << 2),	// Disable Interrupts
            D = (1 << 3),	// Decimal Mode (unused in this implementation)
            B = (1 << 4),	// Break
            U = (1 << 5),	// Unused
            V = (1 << 6),	// Overflow
            N = (1 << 7)	// Negative
        };
        bool get_flag( FLAGS f );
        void set_flag( FLAGS f, bool value );

        // Addressing Modes
        uint8_t IMP();	uint8_t IMM();	
        uint8_t ZP0();	uint8_t ZPX();	
        uint8_t ZPY();	uint8_t REL();
        uint8_t ABS();	uint8_t ABX();	
        uint8_t ABY();	uint8_t IND();	
        uint8_t IZX();	uint8_t IZY();
        uint8_t collect( void );

        // Opcodes
        uint8_t UNI();
        uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
        uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
        uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
        uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
        uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
        uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
        uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
        uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
        uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
        uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
        uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
        uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
        uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
        uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

        // Instructions
        struct INSTRUCTION {
            std::string name;
            uint8_t (CPU::*operate )(void) = nullptr;
            uint8_t (CPU::*addr_mode)(void) = nullptr;
            uint8_t cycles;
        };
        std::vector<INSTRUCTION> opcode_table;
};
