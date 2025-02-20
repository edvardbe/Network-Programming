import { defineStore } from 'pinia';

export const useCompilerStore = defineStore('compiler', {
    state: () => ({
        result: null,
        error: null
    }),
    actions: {
        async compileCode(sourceCode) {
            try {
                const response = await fetch("http://localhost:8080/compile", {
                    method: "POST",
                    headers: { "Content-Type": "application/json" },
                    body: JSON.stringify({ sourceCode }),
                });

                const data = await response.json();

                if (!response.ok) {
                    throw new Error(data.error || "Ukjent feil");
                }

                this.result = data.result;
                this.error = null;
            } catch (error) {
                this.result = null;
                this.error = error.message;
            }
        }
    }
});
