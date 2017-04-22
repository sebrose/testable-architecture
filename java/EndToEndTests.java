import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Collectors;

public class EndToEndTests {
    @Test
    public void single_sales_person() throws Exception {
        // run report
        run("ShoutyReportJob", "test_case_1_input.csv");

        // check XML report has been generated
        Assert.assertTrue(new File("report.xml").isFile());
        Assert.assertEquals(
                readAllLines("test_case_1_expected.xml"),
                readAllLines("report.xml")
        );
    }

    @Test
    public void multiple_sales_people() throws Exception {
        // run report
        run("ShoutyReportJob", "test_case_2_input.csv");

        // check XML report has been generated
        Assert.assertTrue(new File("report.xml").isFile());
        Assert.assertEquals(
                readAllLines("test_case_2_expected.xml"),
                readAllLines("report.xml")
        );
    }

    private void run(String mainClass, String args) throws Exception {
        String[] command = {"java", "-cp", ".", mainClass, args};
        ProcessBuilder processBuilder = new ProcessBuilder(command);
        processBuilder.environment().put("EXAMPLE_ENVIRONMENT_VARIABLE", "ARBITRARY_DATA");
        processBuilder.inheritIO();
        Process process = processBuilder.start();
        process.waitFor();
    }

    private String readAllLines(String path) throws IOException {
        return Files.readAllLines(Paths.get(path)).stream().map(l -> l).collect(Collectors.joining("\n"));
    }
}
