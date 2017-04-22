public class ProductionStatsService implements StatsService {
    private ShoutyStatsService service = new ShoutyStatsService();

    public double getRevenue(int customerID) {
      throw new java.lang.UnsupportedOperationException();

      // Hint: you can copy code from shouty_report_processor.cpp to
      // implement this method, including the behaviour to extract the
      // revenue value as a double from the XML
    }
}
