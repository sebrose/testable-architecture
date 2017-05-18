import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.util.List;

class ShoutyReportProcessor {
    List<MileageClaim> mileageClaims;
    ShoutyStatsService statsService = new ShoutyStatsService();

    public ShoutyReportProcessor(List<MileageClaim> mileageClaims) {
        this.mileageClaims = mileageClaims;
    }

    public void process() {
        Document doc = XmlHelper.newDocument();
        Element ecoReport = doc.createElement("ecoReport");
        doc.appendChild(ecoReport);

        for (MileageClaim claim : mileageClaims) {
            String requestXml = "<Customer id=\"" + claim.customerID + "\"/>";
            String responseXml = statsService.getRevenueForCustomer(requestXml);
            Document responseDocument = XmlHelper.parse(responseXml);

            double revenue = Double.parseDouble(responseDocument.getDocumentElement().getAttribute("revenue"));
            float revenuePerMile = (float) revenue / (float) claim.miles;

            Element node = doc.createElement("ecoStat");
            node.setAttribute("SalespersonName", claim.name);
            node.setAttribute("RevenuePerMile", String.valueOf(revenuePerMile));
            ecoReport.appendChild(node);
        }


        XmlHelper.write(doc, "report.xml");
    }
}
