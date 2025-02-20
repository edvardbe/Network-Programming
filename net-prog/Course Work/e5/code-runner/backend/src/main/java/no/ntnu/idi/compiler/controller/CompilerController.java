package no.ntnu.idi.compiler.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.*;

import no.ntnu.idi.compiler.model.CompilerRequest;
import no.ntnu.idi.compiler.service.CompilerService;

import java.util.Map;

@RestController
@RequestMapping("/api/compiler")
@CrossOrigin(origins = "http://localhost:5173") // Viktig for Vue frontend
public class CompilerController {

    private static final Logger logger = LoggerFactory.getLogger(CompilerController.class);
    private final CompilerService compilerService;

    public CompilerController(CompilerService compilerService) {
        this.compilerService = compilerService;
    }
    //@GetMapping("/user")

    @PostMapping
    public Map<String, Object> compile(@RequestBody CompilerRequest request) {
        Map<String, Object> resultMap = Map.of("", "");
        try {
            logger.info("Received request: {}", request.getSourceCode());

            double result = compilerService.compile(request.getSourceCode());

            logger.info("Returning result: {}", result);
            resultMap = Map.of("result", result);
        } 
        catch (Exception e){
            logger.info("Backend caught exception: {}", e.getMessage());
            resultMap = Map.of("result", "Error");
        }
        return resultMap;
    }
}
