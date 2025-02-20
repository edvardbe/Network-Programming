/* package no.ntnu.idi.compiler.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class CorsConfig {

    @Bean
    public WebMvcConfigurer corsConfigurer() {
        return new WebMvcConfigurer() {
            @Override
            public void addCorsMappings(CorsRegistry registry) {
                registry.addMapping("/api/**") // Gjelder alle API-endepunkter
                        .allowedOrigins("http://localhost:5173") // Tillat Vue.js frontend
                        .allowedMethods("GET", "POST", "PUT", "DELETE", "OPTIONS") // Viktig for preflight
                        .allowedHeaders("*")
                        .allowCredentials(true);
            }
        };
    }
}
 */