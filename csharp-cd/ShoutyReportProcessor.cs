using System.Collections.Generic;
using System.Xml;

class ShoutyReportProcessor
{
    IList<MileageClaim> mileageClaims;
    ShoutyStatsService statsService = new ShoutyStatsService();

    public ShoutyReportProcessor(IList<MileageClaim> mileageClaims)
    {
        this.mileageClaims = mileageClaims;
    }

    public void Process()
    {
        XmlDocument reportXml = new XmlDocument();
        reportXml.LoadXml("<?xml version=\"1.0\" encoding=\"UTF-8\"?><ecoReport/>");
        foreach (var claim in mileageClaims)
        {
            string requestXml = "<Customer id=\"" + claim.CustomerID + "\"/>";
            string responseXml = statsService.GetRevenueForCustomer(requestXml);

            var responseDocument = new XmlDocument();
            responseDocument.LoadXml(responseXml);
            var revenue = decimal.Parse(responseDocument.DocumentElement.Attributes["revenue"].Value);

            var revenuePerMile = (float)revenue / (float)claim.Miles;
            XmlElement node = reportXml.CreateElement(string.Empty, "ecoStat", string.Empty);
            node.SetAttribute("SalespersonName", claim.Name);
            node.SetAttribute("RevenuePerMile", System.Convert.ToString(revenuePerMile));
            reportXml.DocumentElement.AppendChild(node);
        }

        reportXml.Save("report.xml");
    }
}
