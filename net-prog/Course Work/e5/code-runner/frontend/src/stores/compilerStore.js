import { defineStore } from 'pinia';
import axios from 'axios';

export const useCompilerStore = defineStore('compiler', {
    state: () => ({
        result: null,
        error: null
    }),
    actions: {
        async compileCode(sourceCode) {
            try {
                const response = await axios.post("http://localhost:8080/api/compile", {
                    sourceCode: sourceCode
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
