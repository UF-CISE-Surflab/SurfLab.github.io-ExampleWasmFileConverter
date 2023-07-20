# C++ and WebAssembly Demonstration Website

Please click [here](https://gatorsethbarber.github.io/GatorSethBarber.github.io-ExampleWasmFileConverter/docs/converter) to go to the actual application.

## Use of Web Application

The user browses and selects a file with type `.txt` or type `.obj`. After pressing the convert button, a shift of all the characters by one position is written to the file `output.txt` in Downloads. A number in parentheses may be added by the user's OS to distinguish between various versions.

### Errors
The following errors raise alerts:
* If the user selects any file that is not a `.txt` or `.obj` file, an error gets raised.
* If the user does not select any file and presses the Convert button (after the wasm file has been loaded), an error gets raised.

## Building Process 

The program is built using the included Makefile. The Makefile was tested using mingw32-make on Windows 10 in Powershell. The technical version of mingw32-make used was GNU Make 4.2.1. The files needed for the web application have already been built and are included. The commands in the makefile follow. They are accompanied by the commands used to run them while testing.

*Note: Some comments have been added since last build. However, these should have no effect.*

### `plain` (default)

This command builds the (currently present) C++ files excepting `src/bindings.cpp` and outputs the result to `test.exe`. To run on Windows, use one of the following two commands:

```
mingw32-make
mingw32-make plain
```

### `web` (for the web application)

This command builds the `.wasm` and `.js` files that allow access to the C++ class. Before running, you must install emscripten. Directions for installing emscripten are available at https://emscripten.org/docs/getting_started/downloads.html. After installation, specify the installed location in the Makefile as the value of the variable `emsdk_filepath`. For further use, the Makefile already handles activating the latest version of emcc installed on the computer

To run, use the following command:
```
mingw32-make web
```

*Note: The application as tested with emcc version 3.1.27.*

It will generate the files `converter.wasm`, the WebAssembly (WASM) version of the C++ class, and `converter.js`, a javascript file that enables easy access to the WASM, and hence C++, functionality.

### `clean`

This command, deletes the `test.exe` file created by the default. The command is as follows:
```
mingw32-make clean
```

## Directory Structure

The following details the structure of the project.

* pages/
    * This folder contains the HTML files for the web application.
* scripts/
    * This folder contains the JS and WASM files for the web application.
* src/
    * This folder contains the C++ source files. Of particular importance is `bindings.cpp`, which contains the bindings that deterime what can C++ code will be made accessible to the web application.
* styles/
    * The CSS stylesheets for the web application.
* Makefile
    * The Makefile for the application.
* readme.md
    * This file.

## References

The following is a list of URLs/sites used in the project.

* https://web.dev/read-files/  for the general process of reading local files in JavaScript.
* https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input/file for getting file input.
* https://developer.mozilla.org/en-US/docs/Web/API/FileReader for more info on FileReader
* https://developer.mozilla.org/en-US/docs/Web/API/FileReader/readAsText for readAsText
* For saving file: https://www.tutorialspoint.com/how-to-create-and-save-text-file-in-javascript
* New File System Access API: https://developer.chrome.com/articles/file-system-access/ (not used)
* Source for binding classes: https://blog.esciencecenter.nl/using-c-in-a-web-app-with-webassembly-efd78c08469
* Source for binding data types: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
* Mozilla Web Docs
* cplusplus.com (mainly for https://cplusplus.com/reference/sstream/istringstream/istringstream/)
* https://stackoverflow.com/questions/44153866/how-can-i-get-the-height-of-an-element-using-css-only (2nd answer)
* https://www.freecodecamp.org/news/how-to-center-anything-with-css-align-a-div-text-and-more/  for vertical centering
* Source for variables and clean: https://www.youtube.com/watch?v=z4uPHjxYyPs
* Source for including with emscripten: https://stackoverflow.com/questions/28522171/specify-header-locations-for-c-compiler-compiling-r-code-with-emscripten
* Main compilation statement: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
* Reminded of del in https://unix.stackexchange.com/questions/726282/what-actually-is-causing-the-system-can-not-find-the-file-specified-problem-in
* https://github.com/GatorSethBarber/HotelogyFinal/blob/main/4500/scripts/dataHandler.js
* https://github.com/GatorSethBarber/COP3530Project3/blob/a9aa02985a29c6f5fde027e427496f2067e0bcf1/webpages/questionnaire.html
* For saving file: https://www.tutorialspoint.com/how-to-create-and-save-text-file-in-javascript
* https://stackoverflow.com/questions/33674973/makefile-error-make-e-2-the-system-cannot-find-the-file-specified describes a problem I encountered with running the make program
* https://www.codecademy.com/resources/docs/markdown/links for links in Markdown
