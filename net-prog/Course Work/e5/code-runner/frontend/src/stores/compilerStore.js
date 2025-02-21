import { defineStore } from 'pinia';
import axios from 'axios';

export const useCompilerStore = defineStore('compiler', {
    state: () => ({
        sourceCode: null,
        language: null,
        result: null,
        error: null
    }),
    persist: true,
    actions: {
        async compileCode() {
            try {
                const response = await axios.post("http://localhost:8080/api/compile", {
                    sourceCode: this.sourceCode,
                    language: this.language
                });

                this.result = response.data.result;
                this.error = null;
            } catch (error) {
                this.result = null;

                // Sjekk om feilen kommer fra serveren
                if (error.response) {
                    this.error = error.response.data.error || "Ukjent serverfeil";
                } else {
                    this.error = "Kunne ikke koble til serveren";
                }
            }
        }
    }
});
