import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

class ShoutyReportJob {
    public static void main(String[] args) throws IOException {
        String path = args[0];
        List<MileageClaim> mileageClaims = readMileageClaims(path);

        ShoutyReportProcessor job = new ShoutyReportProcessor(mileageClaims);
        job.process();
    }

    private static List<MileageClaim> readMileageClaims(String claimsPath) throws IOException {
        List<MileageClaim> mileageClaims = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new FileReader(claimsPath));
        String line;
        while ((line = reader.readLine()) != null) {
            String[] values = line.split(",");
            mileageClaims.add(new MileageClaim(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2])));
        }
        return mileageClaims;
    }
}
