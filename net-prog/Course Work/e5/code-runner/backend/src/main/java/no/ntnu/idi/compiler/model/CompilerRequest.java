package no.ntnu.idi.compiler.model;


public class CompilerRequest {
    private String sourceCode;

    // Konstruktør (kan også bruke Lombok @Data)
    public CompilerRequest() {}

    public CompilerRequest(String sourceCode) {
        this.sourceCode = sourceCode;
    }

    public String getSourceCode() {
        return sourceCode;
    }

    public void setSourceCode(String sourceCode) {
        this.sourceCode = sourceCode;
    }
}
