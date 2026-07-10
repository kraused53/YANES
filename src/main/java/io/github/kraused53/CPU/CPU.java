package io.github.kraused53.CPU;

public class CPU {
    // System Registers
    private byte regA;      // Accumulator
    private byte regF;      // Status Register
    private byte regX;      // GP Register: X
    private byte regY;      // GP Register: Y
    private byte regSP;     // Stack Pointer
    private short regPC;    // Program Counter

    // Emulation Variables
    private boolean halted;
    private boolean error;
    private short addressAbsolute;
    private short addressRelative;
    private byte opcode;
    private int cycles;


    public CPU() {
        regA = 0;
        regF = (byte)0x04;
        regX = 0;
        regY = 0;
        regSP = 0;
        regPC = 0;

        halted = false;
        error = false;
        addressAbsolute = 0;
        addressRelative = 0;
        opcode = 0;
        cycles = 0;
    }

    // Getters - For debugging
    public byte getA() { return regA; }
    public byte getF() { return regF; }
    public byte getX() { return regX; }
    public byte getY() { return regY; }
    public byte getSP() { return regSP; }
    public short getPC() { return regPC; }
    public boolean isHalted() { return halted; }
    public boolean isError() { return error; }
    public short getAddressAbsolute() { return addressAbsolute; }
    public short getAddressRelative() { return addressRelative; }
    public short getOpcode() { return opcode; }
    public int getCycles() { return cycles; }

    // Setters - For debugging
    public void setA(byte value) { regA = value; }
    public void setF(byte value) { regF = value; regF |= 0x04; }
    public void setX(byte value) { regX = value; }
    public void setY(byte value) { regY = value; }
    public void setSP(byte value) { regSP = value; }
    public void setPC(short value) { regPC = value; }
}
