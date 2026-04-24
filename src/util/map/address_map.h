#pragma once

#include <cstdint>

const uint16_t RAM_START  = 0x0000;
const uint16_t RAM_END    = 0x1FFF;
const uint16_t PPU_START  = 0x2000;
const uint16_t PPU_END    = 0x3FFF;
const uint16_t CART_START = 0x4020;
const uint16_t CART_END   = 0xFFFF;

inline bool between( uint16_t location, uint16_t start, uint16_t end ) { 
  return ( location >= start ) && ( location <= end );
}