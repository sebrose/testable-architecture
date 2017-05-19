import org.junit.Assert;
import org.junit.Test;
import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Collectors;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class EndToEndTests {
    @Test
    public void single_sales_person() throws Exception {
        // run report
        run("ShoutyReportJob", "test_case_1_input.csv");

        // check XML report has been generated
        Assert.assertTrue(new File("report.xml").isFile());
        assertXmlFilesEqual(
            "test_case_1_expected.xml",
            "report.xml"
        );
    }

    @Test
    public void multiple_sales_people() throws Exception {
        // run report
        run("ShoutyReportJob", "test_case_2_input.csv");

        // check XML report has been generated
        Assert.assertTrue(new File("report.xml").isFile());
        assertXmlFilesEqual(
            "test_case_2_expected.xml",
            "report.xml"
        );
    }

    private void run(String mainClass, String args) throws Exception {
        String[] command = {"java", "-cp", ".", mainClass, args};
        ProcessBuilder processBuilder = new ProcessBuilder(command);
        // processBuilder.environment().put(
        //     "FAKE_INITIALISATION_DATA",
        //     "19,123456.78;22,123456.78;57,123456.78"
        // );
        processBuilder.inheritIO();
        Process process = processBuilder.start();
        process.waitFor();
    }

    private void assertXmlFilesEqual(String expectedPath, String actualPath) throws IOException {
        List<Map<String, Object>> expected = documentToListOfMaps(XmlHelper.parse(readAllLines(expectedPath)));
        List<Map<String, Object>> actual = documentToListOfMaps(XmlHelper.parse(readAllLines(actualPath)));

        String message = String.format("Expected XML to contain %s, but got %s", expected, actual);
        Assert.assertEquals(message, expected.size(), actual.size());
        for (int i = 0; i < expected.size(); i++) {
            Map<String, Object> entry = expected.get(i);
            Assert.assertTrue(message, actual.contains(entry));
        }
    }

    private static List<Map<String, Object>> documentToListOfMaps(Document document) {
        List<Map<String, Object>> result = new ArrayList<Map<String, Object>>();
        NodeList nodes = document.getDocumentElement().getChildNodes();

        for (int nodeIndex = 0; nodeIndex < nodes.getLength(); nodeIndex++) {
            Node node = nodes.item(nodeIndex);

            if (node.getNodeType() == Node.ELEMENT_NODE) {
                NamedNodeMap nodeMap = node.getAttributes();
                HashMap<String, Object> nodeResult = new HashMap<String,Object>();

                for (int i = 0; i < nodeMap.getLength(); i++) {
                    Node attr = nodeMap.item(i);
                    nodeResult.put(attr.getNodeName(), attr.getNodeValue());
                }

                result.add(nodeResult);
            }
        }
        return result;
    }

    private String readAllLines(String path) throws IOException {
        return Files.readAllLines(Paths.get(path)).stream().map(l -> l).collect(Collectors.joining("\n"));
    }
}
