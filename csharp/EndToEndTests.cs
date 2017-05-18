using System.IO;
using System.Xml;
using System.Linq;
using System.Collections.Generic;
using NUnit.Framework;

[TestFixture]
public class EndToEndTests
{
    [Test]
    public void single_sales_person()
    {

        // run report
        Run("ShoutyReportJob.exe", "test_case_1_input.csv");

        // check XML report has been generated
        Assert.IsTrue(File.Exists("report.xml"));
        assertXmlFilesEqual(
            "test_case_1_expected.xml",
            "report.xml"
        );
    }

    [Test]
    public void multiple_sales_people()
    {
        // run report
        Run("ShoutyReportJob.exe", "test_case_2_input.csv");

        // check XML report has been generated
        Assert.IsTrue(File.Exists("report.xml"));
        assertXmlFilesEqual(
            "test_case_2_expected.xml",
            "report.xml"
        );
    }

    private void Run(string exe, string args)
    {
        if (File.Exists("report.xml"))
        {
            File.Delete("report.xml");
        }

        System.Diagnostics.Process proc = new System.Diagnostics.Process();
        proc.EnableRaisingEvents = false;
        proc.StartInfo.FileName = exe;
        proc.StartInfo.Arguments = args;
        // proc.StartInfo.EnvironmentVariables.Add(
        //     "FAKE_INITIALISATION_DATA",
        //     "19,123456.78;22,123456.78;57,123456.78"
        // );
        proc.StartInfo.UseShellExecute = false;
        proc.Start();
        proc.WaitForExit();
    }

    private void assertXmlFilesEqual(string expectedPath, string actualPath)
    {
        var expectedXml = File.ReadAllText(expectedPath);
        var expectedDoc = new XmlDocument();
        expectedDoc.LoadXml(expectedXml);

        var actualXml = File.ReadAllText(actualPath);
        var actualDoc = new XmlDocument();
        actualDoc.LoadXml(actualXml);

        List<Dictionary<string, object>> expected = documentToListOfMaps(expectedDoc);
        List<Dictionary<string, object>> actual = documentToListOfMaps(actualDoc);

        string message = string.Format("Expected XML to contain {0}, but got {1}", expectedXml, actualXml);
        Assert.AreEqual(expected.Count, actual.Count, message);
        for (int i = 0; i < expected.Count; i++)
        {
            Dictionary<string, object> entry = expected[i];

            bool dictionariesEqual =
                actual[i].Keys.All(k => entry.ContainsKey(k) && object.Equals(entry[k], actual[i][k]));
            Assert.IsTrue(dictionariesEqual, message);
        }
    }

    private static List<Dictionary<string, object>> documentToListOfMaps(XmlDocument document)
    {
        List<Dictionary<string, object>> result = new List<Dictionary<string, object>>();
        XmlNodeList nodes = document.DocumentElement.ChildNodes;
        for (int nodeIndex = 0; nodeIndex < nodes.Count; nodeIndex++)
        {
            XmlNode node = nodes.Item(nodeIndex);
            if (node.NodeType == XmlNodeType.Element)
            {
                XmlAttributeCollection nodeMap = node.Attributes;
                Dictionary<string, object> nodeResult = new Dictionary<string, object>();
                for (int i = 0; i < nodeMap.Count; i++)
                {
                    XmlNode attr = nodeMap.Item(i);
                    nodeResult.Add(attr.Name, attr.Value);
                }

                result.Add(nodeResult);
            }
        }
        return result;
    }
}
