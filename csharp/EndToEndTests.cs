using NUnit.Framework;
using System.IO;

[TestFixture]
public class EndToEndTests
{
    [Test]
    public void single_sales_person()
    {
        // run report
        Run("ShoutyReportJob.exe","test_case_1_input.csv");

        // check XML report has been generated
        Assert.IsTrue(File.Exists("report.xml"));
        Assert.AreEqual(
            File.ReadAllLines("test_case_1_expected.xml"),
            File.ReadAllLines("report.xml")
        );
    }

    [Test]
    public void multiple_sales_people()
    {
        // run report
        Run("ShoutyReportJob.exe","test_case_2_input.csv");

        // check XML report has been generated
        Assert.IsTrue(File.Exists("report.xml"));
        Assert.AreEqual(
            File.ReadAllLines("test_case_2_expected.xml"),
            File.ReadAllLines("report.xml")
        );
    }

    private void Run(string exe, string args)
    {
        System.Diagnostics.Process proc = new System.Diagnostics.Process();
        proc.EnableRaisingEvents = false;
        proc.StartInfo.FileName = exe;
        proc.StartInfo.Arguments = args;
        proc.StartInfo.EnvironmentVariables.Add("EXAMPLE_ENVIRONMENT_VARIABLE", "ARBITRARY_DATA");
        proc.StartInfo.UseShellExecute = false;
        proc.Start();
        proc.WaitForExit();
    }
}
