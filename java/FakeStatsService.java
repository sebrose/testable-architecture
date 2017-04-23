import java.util.HashMap;
import java.util.Map;

public class FakeStatsService implements StatsService {
    Map<Integer, Double> revenueData = new HashMap<>();

    public FakeStatsService(String data) {
        for (String tuple : data.split(";")) {
            String[] pair = tuple.split(",");
            revenueData.put(Integer.parseInt(pair[0]), Double.parseDouble(pair[1]));
        }
    }

    public double getRevenue(int customerID) {
        if (revenueData.containsKey(customerID)) {
            return revenueData.get(customerID);
        }
        throw new ShoutyStatsServiceException("No such Customer ID: " + customerID);
    }
}
