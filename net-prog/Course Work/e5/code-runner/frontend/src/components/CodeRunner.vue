<script setup>
import { ref } from "vue";
import { useCompilerStore } from "@/stores/compilerStore"; // Sjekk at import-stien stemmer!

const store = useCompilerStore();
const sourceCode = ref("");

async function runCompilation() {
    await store.compileCode(sourceCode.value);
}
</script>

<template id="container">
    <div>
        <textarea id="code-area" v-model="sourceCode" placeholder="Skriv inn kode"></textarea>
        <button @click="runCompilation">Kjør</button>

        <p v-if="store.result">Resultat: {{ store.result }}</p>
        <p v-if="store.error" style="color: red;">Feil: {{ store.error }}</p>
    </div>
</template>

<style scoped>

/* Contact form container */

.container {
  display: flex;
  flex-direction: column;
  position: relative;
  width: 100%;
  height: 100%;
  justify-content: center;
  align-items: center;
  padding: 30px;
  background-color: #3c3c3c;


  /* overflow-y: scroll;
  overflow-x: hidden; */
  /* Center content vertically */
}

/* Position the "x" button in the top-left corner */
.header {
  position: absolute;
  top: 1rem;
  left: 1rem;
  margin: 0;
}

.footer {
  bottom: 1rem;
  right: 1rem;
  margin: 0;
  position: absolute;
}

.exit {
  text-decoration: none;
  background-color: transparent;
  border: none;
  font-size: 24px;
  color: white;
  cursor: pointer;
}

.exit:hover {
  color: red;
}


/* Contact form content styles */
.content {
  width: 100%;
  height: 80%;
  display: grid;
  border: 1px solid #4b4b4b;
  position: relative;
  justify-content: center;
  align-items: center;
  text-align: center;
  padding: 10px;
  margin: 10px;
  gap: 2%;
  overflow-y: auto;

}

.radio-group {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 10px;
}

.name-box {
  display: flex;
  flex-direction: row;
  justify-content: center;
  width: 100%;
  gap: 5px;
}

.name {
  display: flex;
  flex-direction: column;
  width: 50%;
}

input[type=text],
select,
textarea {
  width: 100%;
  /* Full width */
  padding: 12px;
  /* Some padding */
  border: 1px solid #ccc;
  /* Gray border */
  border-radius: 4px;
  /* Rounded borders */
  box-sizing: border-box;
  /* Make sure that padding and width stays in place */
  margin-top: 6px;
  /* Add a top margin */
  margin-bottom: 16px;
  /* Bottom margin */
  resize: vertical
    /* Allow the user to vertically resize the textarea (not horizontally) */
}

input[type=email],
select,
textarea {
  width: 100%;
  /* Full width */
  padding: 12px;
  /* Some padding */
  border: 1px solid #ccc;
  /* Gray border */
  border-radius: 4px;
  /* Rounded borders */
  box-sizing: border-box;
  /* Make sure that padding and width stays in place */
  margin-top: 6px;
  /* Add a top margin */
  margin-bottom: 16px;
  /* Bottom margin */
  resize: vertical
    /* Allow the user to vertically resize the textarea (not horizontally) */
}

/* Style the submit button with a specific background color etc */
button {
  font-size: 24px;
  background-color: #3c3c3c;
  border: 1px solid black;
  cursor: default;
  outline: none;
  transition: background-color 0.3s;
  color: white;
  border-radius: 5px;
  cursor: pointer;
}

/* When moving the mouse over the submit button, add a darker green color */
button:hover:not(:disabled) {
  background-color: #555;
}

button:disabled {
  opacity: 0.4;
  cursor: not-allowed;
}
</style>
