package no.ntnu.idi.compiler.service;


import org.springframework.stereotype.Service;
import java.io.*;
import java.nio.file.*;
import java.util.concurrent.TimeUnit;

@Service
public class CompilerService {

    private static final String WORK_DIR = System.getProperty("java.io.tmpdir") + "/docker_compiler";
    
    private final boolean isWindows = System.getProperty("os.name").toLowerCase().contains("win");

    public String compile(String sourceCode, String language) throws IOException, InterruptedException, Exception {
        Files.createDirectories(Paths.get(WORK_DIR));

        String filename, compileCmd, runCmd, dockerImage;

        switch (language.toLowerCase()) {
            case "c":
                filename = "program.c";
                compileCmd = "gcc " + filename + " -o program";
                runCmd = "./program";
                dockerImage = "gcc";
                break;
            case "java":
                filename = "Program.java";
                compileCmd = "javac " + filename;;
                runCmd = "java Program";
                dockerImage = "openjdk:17";
                break;
            case "python":
            default:
                filename = "program.py";
                compileCmd = "";
                runCmd = "python " + filename;
                dockerImage = "python-comp";
                break;
        }
        Path filePath = Paths.get(WORK_DIR, filename);
        System.out.println("Fil lagres her: " + filePath.toAbsolutePath()); // Console-log
        Files.writeString(filePath, sourceCode);
        if (!compileCmd.isEmpty()) {
            String compileDockerCommand = String.format(
                "docker run --rm -v %s:/app -w /app %s sh -c \"%s\"",
                WORK_DIR, dockerImage, compileCmd
            );
            Process compileProcess = new ProcessBuilder("sh", "-c", compileDockerCommand).start();
            compileProcess.waitFor();
        }
        // Start Docker container
        String dockerCommand = String.format(
        "docker run --rm -v %s:/app -w /app %s %s",
        WORK_DIR, dockerImage, runCmd
        );

        ProcessBuilder builder = isWindows
            ? new ProcessBuilder("cmd.exe", "/c", dockerCommand)  // Windows
            : new ProcessBuilder("bash", "-c", dockerCommand); 
        
        Process process = builder.start();
        if (!process.waitFor(5, TimeUnit.SECONDS)) {
            process.destroy();
            throw new RuntimeException("Timeout: Programmet brukte for lang tid");
        }
        

        String output = new String(process.getInputStream().readAllBytes());
        return output;
    }

    
}
