import io.github.kraused53.CPU.CPU;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class CPUTest {

    @Test
    @DisplayName("Test CPU Initialization")
    void registerTestInitialization() {
        CPU cpu = new CPU();

        assertEquals(0,  cpu.getA());
        assertEquals((byte)0x04,  cpu.getF());
        assertEquals(0,  cpu.getX());
        assertEquals(0,  cpu.getY());
        assertEquals(0,  cpu.getSP());
        assertEquals(0,  cpu.getPC());
    }

    @Test
    @DisplayName("Test CPU Register Access")
    void registerTestRegisterAccess() {
        CPU cpu = new CPU();

        assertEquals(0,  cpu.getA());
        assertEquals((byte)0x04,  cpu.getF());
        assertEquals(0,  cpu.getX());
        assertEquals(0,  cpu.getY());
        assertEquals(0,  cpu.getSP());
        assertEquals(0,  cpu.getPC());

        cpu.setA((byte)0x12);
        cpu.setF((byte)0x34);
        cpu.setX((byte)0x56);
        cpu.setY((byte)0x78);
        cpu.setSP((byte)0x9A);
        cpu.setPC((short)0xBCDE);

        assertEquals((byte)0x12,  cpu.getA());
        assertEquals((byte)0x34,  cpu.getF());
        assertEquals((byte)0x56,  cpu.getX());
        assertEquals((byte)0x78,  cpu.getY());
        assertEquals((byte)0x9A,  cpu.getSP());
        assertEquals((short)0xBCDE,  cpu.getPC());
    }

    @Test
    @DisplayName("Test CPU Flag Register Unused Bit")
    void registerTestUnusedFlagAlwaysSet() {
        CPU cpu = new CPU();
        assertNotEquals(0,  cpu.getF());

        cpu.setF((byte)0xFF);
        assertEquals((byte)0xFF,  cpu.getF());

        cpu.setF((byte)0xF0);
        assertNotEquals((byte)0xF0,  cpu.getF());
        assertEquals((byte)0xF4,  cpu.getF());

        cpu.setF((byte)0x00);
        assertNotEquals((byte)0x00,  cpu.getF());
        assertEquals((byte)0x04,  cpu.getF());
    }

}
