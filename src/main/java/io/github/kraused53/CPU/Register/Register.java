package io.github.kraused53.CPU.Register;

public class Register {
    private byte value;

    public Register(byte value) {
        this.value = value;
    }

    public byte get() { return value; }
    public void set(byte value) { this.value = value; }

    @Override
    public String toString() {
        return String.format("%02X", value);
    }
}
