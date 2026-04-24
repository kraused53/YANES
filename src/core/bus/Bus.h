#pragma once

#include <cstdint>
#include <array>

#include "core/cpu/CPU.h"
#include "IBus.h"

class Bus : public IBus {
    private:
        // Fake memory
        std::array<uint8_t, 64 * 1024> ram;
    
    public:
        Bus();
        ~Bus();

        // Emulation
        void reset() override;
        void clock() override;

        // Bus devices
        CPU cpu;

        // Memory access
        void write( uint16_t addr, uint8_t data ) override;
        uint8_t read( uint16_t addr ) override;

};