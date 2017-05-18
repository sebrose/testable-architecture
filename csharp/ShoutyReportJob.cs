using System.IO;
using System.Collections.Generic;

class ShoutyReportJob
{
    public static void Main(string[] args)
    {
        var path = args[0];
        var mileageClaims = ReadMileageClaims(path);

        var job = new ShoutyReportProcessor(mileageClaims);
        job.Process();
    }

        /*
        private static IStatsService CreateStatsService()
        {
            if (System.Environment.GetEnvironmentVariable("FAKE_INITIALISATION_DATA") != null)
            {
                return new FakeStatsService(
                    System.Environment.GetEnvironmentVariable("FAKE_INITIALISATION_DATA"));
            }

            return new ProductionStatsService(new ShoutyStatsService());
        }
        */

    private static IList<MileageClaim> ReadMileageClaims(string claimsPath)
    {
        var mileageClaims = new List<MileageClaim>();
        using (var reader = new StreamReader(claimsPath))
        {
            while (!reader.EndOfStream)
            {
                var values = reader.ReadLine().Split(',');
                mileageClaims.Add(new MileageClaim(values[0], int.Parse(values[1]), int.Parse(values[2])));
            }
        }
        return mileageClaims;
    }
}
