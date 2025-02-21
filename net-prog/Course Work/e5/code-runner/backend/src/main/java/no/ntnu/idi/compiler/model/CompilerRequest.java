package no.ntnu.idi.compiler.model;


public class CompilerRequest {
    private String sourceCode;
    private String language;

    // Konstruktør (kan også bruke Lombok @Data)
    public CompilerRequest() {}

    public CompilerRequest(String language, String sourceCode) {
        this.language = language;
        this.sourceCode = sourceCode;
    }

    public String getSourceCode() {
        return sourceCode;
    }

    public void setSourceCode(String sourceCode) {
        this.sourceCode = sourceCode;
    }

    public String getLanguage() {
        return language;
    }

    public void setLanguage(String language) {
        this.language = language;
    }
}
