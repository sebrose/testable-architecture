using System.Collections.Generic;

public class EcoStatCollectionBuilder
{
    private List<EcoStat> defaultEcoStatCollection =
        new List<EcoStat>(){
            new EcoStat("David Allen", 1.234f),
            new EcoStat("Lisa Crispin", 0.025f),
            new EcoStat("Ian Dees", 98.76f)
        };

    private Dictionary<string, float> ecoStatData = null;

    public List<EcoStat> Build()
    {
        if (ecoStatData == null)
        {
            return defaultEcoStatCollection;
        }
        else
        {
            List<EcoStat> ecoStatCollection = new List<EcoStat>();

            foreach(KeyValuePair<string, float> entry in ecoStatData)
            {
                ecoStatCollection.Add(new EcoStat(entry.Key, entry.Value));
            }

            return ecoStatCollection;
        }
    }

    public EcoStatCollectionBuilder WithSalesPersonRpm(string name, float rpm)
    {
        if (ecoStatData == null)
        {
            ecoStatData = new Dictionary<string, float>();
        }

        ecoStatData[name] = rpm;
        return this;
    }
}
