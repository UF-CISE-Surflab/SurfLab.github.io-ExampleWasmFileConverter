# C++ and WebAssembly Demonstration Website

Please click [here](https://gatorsethbarber.github.io/GatorSethBarber.github.io-ExampleWasmFileConverter/docs/converter) to go to the actual application.

## Use of Web Application

The user browses and selects a file with type type `.obj`. After pressing the convert button, a shift of all the characters by one position is written to the file `output.obj` in Downloads. A number in parentheses may be added by the user's OS to distinguish between various versions.

### Errors
The following errors raise alerts:
* If the user selects any file that is not a `.obj` file, an error gets raised.
* If the user does not select any file and presses the Convert button (after the wasm file has been loaded), an error gets raised.

## Build Process

*Note: To see more detailed process, see section Detailed Build Explanation*

The applications is built in Windows.

The program is built using the included Makefile. The Makefile was tested using mingw32-make on Windows 10 in Powershell. The technical version of mingw32-make used was GNU Make 4.2.1. The files needed for the web application have already been built and are included. The commands in the makefile follow. They are accompanied by the commands used to run them while testing.

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
* cube.obj
    * This is file by garycak used for testing purposes.

## Detailed Build Explanation

The process is built in Windows, with the Makefile being built using mingw32-make. The details for the various parts are below. If you do not have mingw32-make, then you can run the commands in the command line.

### Setup and Details for Plain .exe Build

This setup simply builds the file src/converter.cpp, which holds the main logic, and src/main.cpp, to test.exe, using the widespread g++ compiler. The commands in the Makefile are:
```
g++ ./src/converter.cpp ./src/main.cpp -o temp.exe      // build using g++
./temp.exe                                              // Run temp.exe
```

If you are using the plain command line, run `temp.exe` rather than `./temp.exe`. This executable will perform the transformation on `cube.obj` and print the result of the transformation to the standard output stream. Note that the commands should be run from the main directory.

### Setup and Details for Web Build

The setup for building for the web is more complicated. Follow the various steps below.

#### Getting emscripten

The commands for getting emscripten on your computer are available at https://emscripten.org/docs/getting_started/downloads.html and are repeated here, with modifications.

1. It is recommended that you create a new directory C:\emcc. While this is not necessary, it will provide an insulated place to perform the following steps and a convenient location for following use, though you may also prefer to not create a file and just use C:\.
2. Go to this directory in the command prompt that has both git and python avaialable.
3. In git bash, run `git clone https://github.com/emscripten-core/emsdk.git`. This will clone the repository for emscripten onto your computer.
4. Run `cd emsdk/` to enter the correct repository.
5. You may want to run `git pull` here to update emscripten. However, this is not necessary.
6. Run `./emsdk install latest` or `emsdk install latest`

This completes what needs to be downloaded to run emscripten. Note that the final step above will take some time to complete.

#### Running emscripten
In PowerShell, you should be able to run the following commands, either by typing them out or running `mingw32-make web`:
```
$(emsdk_filepath)/emsdk activate latest
emcc -lembind src/converter.cpp src/bindings.cpp -o scripts/converter.js -I$(emsdk_filepath) -s EXPORT_NAME=createModule -s MODULARIZE=1
```
If you are typing them out, replace `$(emsdk_filepath)` with the full file path to the emsdk folder that was created when running the `git clone` operation. If you ran the `git clone` inside of C:\emcc, then the path will be C:/emcc/emsdk/. If you are using the Makefile, change `emsdk_filepath` variable to be the appropriate filepath.

The first command makes the emcc command available, while the second command uses emcc to build the necessary C++ files to the output. You may notice that the output is marked as a JavaScript file rather than a WebAssembly file. This is correct, and makes the process output both a WebAssembly file (scripts/converter.wasm) containing bytecode and a JavaScript file (scripts/converter.js) that allows access to the WebAssembly file. The other flags are needed to make the output work correctly with the current web application.

*Note: In the Makefile, you may notice that these commands are on one line and joined by an ampersand (&). This is because running the commands runs them in different new processes (shells). However, it is required that they run in the same process, hence the & in the Makefile*

### Setup and Details for Clean
The following commands is used to remove the .exe file created by the plain option:
```
del temp.exe
```

## Modifying the Web Application

JavaScript and WebAssembly have severe limitations on what can and cannot be performed due to the high risk of exploits from the internet. WebAssembly, in fact, can only access files that it is specified as having access to at compile time. Thus, special code and methodology is needed to access the file system of the computer. This is handled already by having JavaScript read the file in from the computer, take the contents of the file as a string and set it to the WebAssembly application, get back the new date from the WebAssembly application as a string, and (using freely available 3rd-party code) write it to the computer as a file placed into downloads. While this may seem as a hamper, the main change to the C++ code is requiring it to use strings and stringstreams (as in the example) rather than file streams. This replacement can be easily acheieved. The only odd consequence of doing things this is way is when running the Web side, an empty string is (at least once) treated as having 1 character in it when using `getline`. This however, is easily gotten through, as demonstrated in the sample code.

The example code provided in src/bindings.cpp and src/converter.cpp provide a template that can be modified for implementation. The main setup for any function that you add to the class that you wish to expose is:
`.function("exposedName", &refToFunc)`

Note that some special work has to be done for more advanced structures, such as vectors. For those, see https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html, which also has information on concepts such as pointers and overloading and how th bindings must be changed for these.

There is documentation in the files for all functions used. The ones that are currently exposed are all currently used by the WebApplication, and have the following uses:
* `Converter::Converter()`: The constructor. It is needed to construct the Converter object.
* `string Converter::stringConvert(string textInput)`: Used to perform the conversion.
* `string Converter::flagReport()`: Gets a report on any error flags that were set by the class (must be modified if you add more flags).

Note: To change the file type being exported, just go to scripts/handleConverter.js and change the value assigne to `outputFileType` to the appropriate file extension (making sure to include the period).

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
* For the cube.obj file: By garykac at https://github.com/garykac/3d-cubes/blob/master/cube.obj
* cplusplus.com was used as a general reference
* For `stod`: https://www.programiz.com/cpp-programming/string-float-conversion