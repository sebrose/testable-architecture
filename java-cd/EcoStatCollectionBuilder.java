import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class EcoStatCollectionBuilder {
    private List<EcoStat> defaultEcoStatCollection =
        new ArrayList<EcoStat>(){{
            add(new EcoStat("David Allen", 1.234f));
            add(new EcoStat("Lisa Crispin", 0.025f));
            add(new EcoStat("Ian Dees", 98.76f));
        }};

    private Map<String, Float> ecoStatData = null;

    public List<EcoStat> build() {
        if (ecoStatData == null) {
            return defaultEcoStatCollection;
        } else {
            List<EcoStat> ecoStatCollection = new ArrayList<EcoStat>();

            for (Map.Entry<String, Float> entry : ecoStatData.entrySet()) {
                ecoStatCollection.add(new EcoStat(entry.getKey(), entry.getValue()));
            }

            return ecoStatCollection;
        }
    }

    public EcoStatCollectionBuilder withSalesPersonRpm(String name, float rpm) {
        if (ecoStatData == null){
            ecoStatData = new HashMap<String, Float>();
        }

        ecoStatData.put(name, rpm);
        return this;
    }
}
