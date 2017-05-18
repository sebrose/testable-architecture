using System.IO;
using System.Xml;

public class ProductionStatsService : IStatsService
{
    // private ShoutyStatsService service = new ShoutyStatsService();

    public decimal GetRevenue(int customerId)
    {
        /*
            string requestXml = "<Customer id=\"" + customerId + "\"/>";
            string responseXml = service.GetRevenueForCustomer(requestXml);

            var responseDocument = new XmlDocument();
            responseDocument.LoadXml(responseXml);
            return decimal.Parse(responseDocument.DocumentElement.Attributes["revenue"].Value);
        */

        throw new System.NotImplementedException("Uncomment code above and delete this exception");
    }
}
