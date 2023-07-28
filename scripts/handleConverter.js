// https://web.dev/read-files/  for general process
// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input/file for file input
// https://developer.mozilla.org/en-US/docs/Web/API/FileReader for more on file reader
// https://developer.mozilla.org/en-US/docs/Web/API/FileReader/readAsText for readAsText
// For saving file: https://www.tutorialspoint.com/how-to-create-and-save-text-file-in-javascript

// New File System Access API: https://developer.chrome.com/articles/file-system-access/ (not used)

let converter;
let outputFileType = ".obj";

const getLitType = (fileName) => {
    const rightDot = fileName.lastIndexOf(".");

    if (rightDot === -1)
        return ""

    else {
        return fileName.substring(rightDot)
    }
}

function doConversion() {
    fileInInput = document.getElementById("in-file");
    filesIn = fileInInput.files;

    const file = filesIn[0];  // Currently, can only get one file
    console.log("file: ", file);
    if (file == undefined) {
        alert("Please select a file.");
        return;
    }

    // Enforce the literal type to be .obj
    const litType = getLitType(file.name);
    if (litType !== ".obj") {
        alert(`Unsupported file type: ${litType}`);
    }
    
    const fileReader = new FileReader();

    // from readAsText source
    // This handles reading in the text from the file, processing it, and writing new file.
    fileReader.addEventListener(
        "load",
        () => {
            // this will then display a text file
            const result = fileReader.result;

            // processing
            let newString = converter.stringConvert(result);

            // Copied from https://github.com/GatorSethBarber/HotelogyFinal/blob/main/4500/scripts/dataHandler.js
            // Create blob object with file content
            let  blob = new Blob([newString], {type: "text/plain;charset=utf-8",});

            // Create and save the file using the FileWriter library
            saveAs(blob, "output" + outputFileType);

            // State task is done and report errors
            alert("Task done.\nError report:\n" + converter.flagReport());
        },
        false,
    );
    
    if (file) {
        fileReader.readAsText(file);
    }

}

// copied from https://github.com/GatorSethBarber/COP3530Project3/blob/a9aa02985a29c6f5fde027e427496f2067e0bcf1/webpages/questionnaire.html
createModule().then(({Converter}) => {
    // hoist converter
    converter = new Converter();
    const cvtBtn = document.getElementById('convert-button');
    cvtBtn.addEventListener('click', () => {
        doConversion();
    })
}).catch(console.log)