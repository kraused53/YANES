#include <cstdint>
#include <vector>
#include <string>

class cpu_6502{
private:
    // System Registers
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t SP;

    // System Pointers
    uint16_t PC;

    // Emulation
    bool error;
    bool halted;
    uint8_t opcode;
    unsigned int cycles;

    // Memory
    std::vector<uint8_t> memory;
    uint8_t read_byte( uint16_t addr );
    uint16_t read_word( uint16_t addr );
    uint8_t fetch_byte( void );
    uint16_t fetch_word( void );

    // Flags
    uint8_t F;
    enum FLAG {
        F_N = ( 1 << 7 ),  // Negative
        F_V = ( 1 << 6 ),  // Overflow
        F_B = ( 1 << 4 ),  // Break
        F_D = ( 1 << 3 ),  // Decimal
        F_I = ( 1 << 2 ),  // Interrupt
        F_Z = ( 1 << 1 ),  // Zero
        F_C = ( 1 << 0 )   // Carry
    };

    // Addressing modes
    void IMP( void );
    void IMM( void );	
	void ZP0( void );
    void ZPX( void );	
	void ZPY( void );
    void REL( void );
	void ABS( void );
    void ABX( void );	
	void ABY( void );
    void IND( void );	
	void IZX( void );
    void IZY( void );

    // Opcodes
    void UNI( void );

    // Opcode Lookup Table
    struct OPCODE_TABLE
	{
		std::string dbg;		
		void     (cpu_6502::*operate )(void) = nullptr;
		void     (cpu_6502::*mode)(void) = nullptr;
		int     cycles = 0;
	};
	std::vector<OPCODE_TABLE> lookup;

public:
    cpu_6502( void );
    ~cpu_6502( void );

    /* Emulator */
    void step( void );
    void reset( void );

    // Register getters ( for debugging )
    inline uint8_t   get_A( void ) {  return A; }
    inline uint8_t   get_X( void ) {  return X; }
    inline uint8_t   get_Y( void ) {  return Y; }
    inline uint8_t  get_SP( void ) { return SP; }
    inline uint16_t get_PC( void ) { return PC; }

    // Flags
    bool get_flag( FLAG f );
    void set_flag( FLAG f, bool val );
};