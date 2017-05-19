import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MileageClaimCollectionBuilder {
    private List<MileageClaim> defaultMileageClaimCollection =
        new ArrayList<MileageClaim>(){{
            add(new MileageClaim("David Allen", 130000, 57));
            add(new MileageClaim("Lisa Crispin", 27000, 19));
            add(new MileageClaim("Ian Dees", 19238855, 22));
        }};

    private List<MileageClaim> mileageClaimCollection = null;

    public List<MileageClaim> build() {
        if (mileageClaimCollection == null) {
            return defaultMileageClaimCollection;
        } else {
            return mileageClaimCollection;
        }
    }

    public MileageClaimCollectionBuilder withSalesPersonMilesForCustomer(
      String name,
      int miles,
      int id) {

        if (mileageClaimCollection == null){
            mileageClaimCollection = new ArrayList<MileageClaim>();
        }

        mileageClaimCollection.add(new MileageClaim(name, miles, id));
        return this;
    }
}
