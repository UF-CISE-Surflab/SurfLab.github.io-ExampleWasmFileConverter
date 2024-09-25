// https://web.dev/read-files/  for general process
// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input/file for file input
// https://developer.mozilla.org/en-US/docs/Web/API/FileReader for more on file reader
// https://developer.mozilla.org/en-US/docs/Web/API/FileReader/readAsText for readAsText
// For saving file: https://www.tutorialspoint.com/how-to-create-and-save-text-file-in-javascript

// New File System Access API: https://developer.chrome.com/articles/file-system-access/ (not used)

let converter;
let outputFileType = ".igs";

const getLitType = (fileName) => {
    const rightDot = fileName.lastIndexOf(".");

    if (rightDot === -1)
        return ""

    else {
        return fileName.substring(rightDot)
    }
}

const reviseIGES = (fileStr) => {
    let s_data = [];
    let g_data = [];
    let d_data = [];
    let p_data = [];
    let t_data = [];
    let start_locs = [];
    let lineCtr = 0;
    let fileLines = fileStr.split('\n');
    const numFileLines = fileLines.length;
    while (lineCtr < numFileLines) {
        line = fileLines[lineCtr].trimEnd()
        if (line === undefined || line === null)
            break;
        if (line.length < 9)
            break;

        line_type = line[72]
        if (line_type === 'S') {
            s_data.push(line);
            lineCtr += 1;
        }
        else if (line_type === 'G') {
            g_data.push(line);
            lineCtr += 1;
        }
        else if (line_type === 'D') {
            d_data.push(line + '\n' + fileLines[lineCtr + 1].trimEnd())
            lineCtr += 2;
        }
        else if (line_type === 'P') {
            let tmp = line;
            start_locs.push(Number(line.substring(73)));
            old_num = line.substring(64, 73)      // NOTE: This assumes that numbers use consistent format
            lineCtr += 1;
            while (true) {
                if (fileLines[lineCtr].substring(64,73) === old_num) {
                    tmp += '\n' + fileLines[lineCtr].trimEnd();
                    lineCtr += 1
                }
                else
                    break;
            }
            p_data.push(tmp);
        }
        else {
            t_data.push(line);
            lineCtr += 1;
            console.log("Got T")
        }

    }
    
    for (let idx = 0; idx < start_locs.length; idx += 1) {
        let asStr = start_locs[idx].toString().padStart(8);
        const curr = d_data[idx];
        d_data[idx] = d_data[idx].substring(0, 8) + asStr + d_data[idx].substring(16,);
    }

    out = ''
    if (s_data.length === 0)
        out += 'copyright(c)Jorg Peters [jorg.peters@gmail.com]                         S      1\n';
    else
        out += ''.join(s_data);
    if (g_data.length === 0)
        out += "                                                                        G      1\n";
    else
        out += ''.join(g_data);
    out += d_data.join('\n') + '\n';
    out += p_data.join('\n') + '\n';
    out += t_data.join('\n') + '\n';
    return out
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

            let  blob = new Blob([reviseIGES(newString)], {type: "text/plain;charset=utf-8",});

            // Create and save the file using the FileWriter library
            saveAs(blob, "output" + outputFileType);

            // State task is done and report errors
            alert("IGS file is generated!.\n If you see holes on surface or totally empty, please modify the mesh configuration (Two singularities should not be direct neighbor.).");
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
