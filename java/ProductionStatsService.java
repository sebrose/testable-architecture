import org.w3c.dom.Document;

public class ProductionStatsService implements StatsService {
    private ShoutyStatsService service = new ShoutyStatsService();

    public double getRevenue(int customerID) {
      /*
        String requestXml = "<Customer id=\"" + customerID + "\"/>";
        String responseXml = service.getRevenueForCustomer(requestXml);
        Document responseDocument = XmlHelper.parse(responseXml);

        return Double.parseDouble(responseDocument.getDocumentElement().getAttribute("revenue"));
      */

      throw new java.lang.UnsupportedOperationException("Uncomment code above and delete this exception");
    }
}
