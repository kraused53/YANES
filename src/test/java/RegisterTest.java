import io.github.kraused53.CPU.Register.Register;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class RegisterTest {

    @Test
    @DisplayName("Test Register Initialization")
    void registerTestInitialization() {
        Register a = new Register((byte)0x00);
        Register b = new Register((byte)0x0F);
        Register c = new Register((byte)0xF0);
        Register d = new Register((byte)0xFF);

        assertNotEquals(a.get(),b.get());
        assertNotEquals(a.get(),c.get());
        assertNotEquals(a.get(),d.get());
        assertNotEquals(b.get(),c.get());
        assertNotEquals(b.get(),d.get());
        assertNotEquals(c.get(),d.get());

        assertEquals((byte)0x00, a.get());
        assertEquals((byte)0x0F, b.get());
        assertEquals((byte)0xF0, c.get());
        assertEquals((byte)0xFF, d.get());
    }

    @Test
    @DisplayName("Test Register Value Access")
    void registerTestValueAccess() {
        Register a = new Register((byte)0x00);
        Register b = new Register((byte)0x00);

        assertEquals(a.get(),b.get());

        b.set((byte)0xFF);
        assertNotEquals(a.get(),b.get());
        assertEquals((byte)0xFF, b.get());

        a.set((byte)0xFF);
        assertEquals(a.get(),b.get());
        assertEquals((byte)0xFF, a.get());

        a.set((byte)0x0F);
        b.set((byte)0xF0);
        assertEquals((byte)0xFF, a.get()+b.get());
        assertEquals((byte)0x00, a.get()+b.get()+1);
    }

    @Test
    @DisplayName("Test Register toString")
    void registerTestToString() {
        Register a = new Register((byte)0x00);
        assertEquals("00", a.toString());

        a.set((byte)0x0F);
        assertEquals("0F", a.toString());

        a.set((byte)0xF0);
        assertEquals("F0", a.toString());

        a.set((byte)0xFF);
        assertEquals("FF", a.toString());
        
    }

}
