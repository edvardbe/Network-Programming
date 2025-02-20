package no.ntnu.idi.compiler.service;


import org.springframework.stereotype.Service;
import java.io.*;
import java.nio.file.*;
import java.util.concurrent.TimeUnit;

@Service
public class CompilerService {

    //private static final String WORK_DIR = "/tmp/docker_compiler"; // Midlertidig mappe
    private static final String WORK_DIR = System.getProperty("java.io.tmpdir") + "/docker_compiler";
    // Windows-sti

    public String compile(String sourceCode) throws IOException, InterruptedException {
    Files.createDirectories(Paths.get(WORK_DIR));

    String filename = "program.py";
    Path filePath = Paths.get(WORK_DIR, filename);
    System.out.println("Fil lagres her: " + filePath.toAbsolutePath()); // Console-log
    Files.writeString(filePath, sourceCode);

    boolean isWindows = System.getProperty("os.name").toLowerCase().contains("win");

    // Kjør Docker direkte, uten sh
    String dockerCommand = String.format(
        "docker run --rm -v %s:/app -w /app my-python-app python %s",
        WORK_DIR, filename
    );

    ProcessBuilder builder = isWindows
        ? new ProcessBuilder("cmd.exe", "/c", dockerCommand)  // Windows
        : new ProcessBuilder("bash", "-c", dockerCommand);   // Linux/macOS

    builder.redirectErrorStream(true);
    Process process = builder.start();

    String output = new String(process.getInputStream().readAllBytes());

    if (!process.waitFor(5, TimeUnit.SECONDS)) {
        process.destroy();
        throw new RuntimeException("Timeout: Programmet brukte for lang tid");
    }

    return output;
    }

    
}
