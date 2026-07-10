import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class DummyTest {

    @Test
    @DisplayName("This test will pass!")
    void dummyPass() {
        assertEquals(true, true);
    }

    @Test
    @DisplayName("This test will fail...")
    void dummyFail() {
        assertEquals(false, true);
    }
}
