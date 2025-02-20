package no.ntnu.idi.compiler.service;

import org.springframework.stereotype.Service;

import java.util.concurrent.TimeUnit;

import javax.annotation.PreDestroy;

@Service
public class DockerService {

    private Process dockerProcess;
    private final boolean isWindows = System.getProperty("os.name").toLowerCase().contains("win");


    public String startDockerProcess(String WORK_DIR, String filename) throws Exception {
        // Start Docker container
        String dockerCommand = String.format(
        "docker run -d -v %s:/app -w /app my-python-app python %s",
        WORK_DIR, filename
        );

        ProcessBuilder builder = isWindows
            ? new ProcessBuilder("cmd.exe", "/c", dockerCommand)  // Windows
            : new ProcessBuilder("bash", "-c", dockerCommand); 
        
        dockerProcess = builder.start();

        String output = new String(dockerProcess.getInputStream().readAllBytes());

        return output;

    }

    public String getDockerOutput() throws Exception {
        String output = new String(dockerProcess.getInputStream().readAllBytes());
        return output;
    }



    @PreDestroy
    public void stopDockerProcess() throws Exception {
        if (dockerProcess != null) {
            // Stopp Docker-containeren manuelt
            String dockerCommand = String.format(
            "docker stop %s",
            dockerProcess.pid()
            );
            ProcessBuilder builder = isWindows
            ? new ProcessBuilder("cmd.exe", "/c", dockerCommand)  // Windows
            : new ProcessBuilder("bash", "-c", dockerCommand); 
        
            Process stop = builder.start();
            dockerProcess.destroy();
            stop.waitFor(5, TimeUnit.SECONDS);
            stop.destroy();
        }
    }
}
