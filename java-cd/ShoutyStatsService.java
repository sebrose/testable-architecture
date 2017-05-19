// DO NOT LOOK IN THIS FILE
// DO NOT LOOK IN THIS FILE
// DO NOT LOOK IN THIS FILE
// DO NOT LOOK IN THIS FILE

































































import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class ShoutyStatsService {
    private static Random rnd = new Random();

    private int latestEcoStatsMonth;
    private int latestEcoStatsYear;
    private Map<String, Map<String, Float>> ecoStatsStore = new HashMap<>();

    private Map<Integer, Double> revenueByCustomerId = new HashMap<Integer, Double>() {{
        put(1, 234.50);
        put(19, 123456.78);
        put(22, 123456.78);
        put(57, 123456.78);
    }};

    public ShoutyStatsService() {
        if (System.getenv("VOLATILE_STATS_DATA") != null) {
            revenueByCustomerId = new HashMap<>();
            for (int i = 0; i < 10; i++) {
                revenueByCustomerId.put(rnd.nextInt(1000), rnd.nextInt(99999999) / 100.0);
            }
        }
    }

    public String getRevenueForCustomer(String customerXml) {
        checkServiceConnection();
        int customerID = extractCustomerId(customerXml);
        if (!revenueByCustomerId.containsKey(customerID))
            throw new ShoutyStatsServiceException("No customer found with ID '" + customerID + "'");

        return "<CustomerStats id=\"" +
                customerID +
                "\" revenue=\"" +
                revenueByCustomerId.get(customerID) +
                "\"/>";
    }

    public String getCustomerIDs() {
        StringBuilder result = new StringBuilder();
        result.append("<Customers>");
        for (Integer id : revenueByCustomerId.keySet()) {
            result.append("<Customer id=\"");
            result.append(id);
            result.append("\"/>");
        }
        result.append("</Customers>");

        return result.toString();
    }

    public String isValidCustomer(String customerXml) {
        int id = extractCustomerId(customerXml);

        if (revenueByCustomerId.containsKey(id)) {
            return "<booleanResponse result=\"TRUE\" />";
        } else {
            return "<booleanResponse result=\"FALSE\" />";
        }
    }

    public String getLatestEcoStatsDate() {
        return "<LatestEcoStatsDate year=\"" +
                String.format("%04d", latestEcoStatsYear) +
                "\" month=\"" +
                String.format("%04d", latestEcoStatsMonth) +
                "\" />";
    }

    public void setEcoStats(String ecoStatsXml) {
        Document doc = XmlHelper.parse(ecoStatsXml);
        int month = Integer.parseInt(doc.getDocumentElement().getAttribute("month"));
        int year = Integer.parseInt(doc.getDocumentElement().getAttribute("year"));

        String key = createKey(year, month);

        if (year < latestEcoStatsYear ||
                (year == latestEcoStatsYear && month < latestEcoStatsMonth)) {
            throw new ShoutyStatsServiceException("EcoStats for a later month have already been set");
        }

        storeEcoStats(key, doc.getDocumentElement());
        latestEcoStatsYear = year;
        latestEcoStatsMonth = month;
    }

    public String getEcoStatsWinnerFor(String dateXml) {
        String winnersName = "Nobody";
        float winningRevenuePerMile = 0;

        Document doc = XmlHelper.parse(dateXml);
        int month = Integer.parseInt(doc.getDocumentElement().getAttribute("month"));
        int year = Integer.parseInt(doc.getDocumentElement().getAttribute("year"));
        String key = createKey(year, month);

        for (Map.Entry<String, Float> stat : ecoStatsStore.get(key).entrySet()) {
            if (stat.getValue() > winningRevenuePerMile) {
                winnersName = stat.getKey();
                winningRevenuePerMile = stat.getValue();
            }
        }

        return "<ecoStatsWinner SalespersonName=\"" +
                winnersName +
                "\" />";
    }

    private int extractCustomerId(String xml) {
      Document doc = XmlHelper.parse(xml);

      return Integer.parseInt(doc.getDocumentElement().getAttribute("id"));
    }

    private String createKey(int year, int month) {
        return String.format("%04d-%02d", year, month);
    }

    private void storeEcoStats(String key, Element root) {
        if (root.hasChildNodes()) {
            Map<String, Float> ecoStats = new HashMap<>();

            Element ecoStatNode = (Element) root.getFirstChild();

            while (ecoStatNode != null) {
                ecoStats.put(ecoStatNode.getAttribute("SalespersonName"), Float.parseFloat(ecoStatNode.getAttribute("RevenuePerMile")));
                ecoStatNode = (Element) ecoStatNode.getNextSibling();
            }

            ecoStatsStore.put(key, ecoStats);
        }
    }

    private void checkServiceConnection() {
        if (System.getenv("RELIABLE_CONNECTION") != null)
            return;

        int parityControl = rnd.nextInt(10);
        if (parityControl == 1)
            throw new ShoutyStatsServiceException("shouty.reporting.ShoutyStatsService connection error - please wait a few moments and try your request again");
    }
}
