import org.junit.Assert;
import org.junit.Test;

public class UnitTests {
    @Test
    public void milage_claim_can_be_created_from_strings() {
        MileageClaim claim = new MileageClaim("David Allen", 37000, 99);
        Assert.assertEquals("David Allen", claim.name);
        Assert.assertEquals(37000, claim.miles);
        Assert.assertEquals(99, claim.customerID);
    }
}
