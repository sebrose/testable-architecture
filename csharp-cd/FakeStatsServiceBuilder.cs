using System.Collections.Generic;

public class FakeStatsServiceBuilder
{
    private string defaultCustomerData = "19,123456.78;22,123456.78;57,123456.78";
    private Dictionary<int, double> builderData = null;

    public IStatsService Build() 
    {
        string initialisationData = "";

        if (builderData == null)
        {
            initialisationData = defaultCustomerData;
        } else {
            string separator = "";

            foreach(KeyValuePair<int, double> entry in builderData)
            {
                initialisationData += separator + entry.Key + "," + entry.Value;
                separator = ";";
            }
        }
        return new FakeStatsService(initialisationData);
    }

    public FakeStatsServiceBuilder WithCustomerRevenue(int id, double revenue)
    {
        if (builderData == null)
        {
            builderData = new Dictionary<int, double>();
        }

        builderData.Add(id, revenue);

        return this;
    }
}
