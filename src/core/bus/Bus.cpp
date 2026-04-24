#include "core/bus/Bus.h"
#include "util/map/address_map.h"

#include <Logger.h>

Bus::Bus() {
	// Connect CPU to communication bus
	cpu.ConnectBus(this);

	reset();
}

Bus::~Bus() {

}

void Bus::write( uint16_t addr, uint8_t data ) {
	if( between( addr, RAM_START, RAM_END ) ) {
  	ram[ addr & 0x07FF ] = data;
	}
}

uint8_t Bus::read( uint16_t addr ) {
	if( between( addr, RAM_START, RAM_END ) ) {
  	return ram[ addr ];
	}

	return 0xFF;
}

void Bus::reset() {
	
	// Clear RAM contents, just in case :P
	for (auto &i : ram) i = 0x00;

	cpu.reset();
}

void Bus::clock() {
	cpu.step();
}