package io.github.kraused53.CPU;

public class CPU {
    private byte regA;
    private byte regF;
    private byte regX;
    private byte regY;
    private byte regSP;
    private short regPC;

    public CPU() {
        regA = 0;
        regF = (byte)0x04;
        regX = 0;
        regY = 0;
        regSP = 0;
        regPC = 0;
    }

    public byte getA() { return regA; }
    public byte getF() { return regF; }
    public byte getX() { return regX; }
    public byte getY() { return regY; }
    public byte getSP() { return regSP; }
    public short getPC() { return regPC; }

    public void setA(byte value) { regA = value; }
    public void setF(byte value) { regF = value; regF |= 0x04; }
    public void setX(byte value) { regX = value; }
    public void setY(byte value) { regY = value; }
    public void setSP(byte value) { regSP = value; }
    public void setPC(short value) { regPC = value; }
}
