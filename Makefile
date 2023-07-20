# Source for variables and clean: https://www.youtube.com/watch?v=z4uPHjxYyPs
# Source for including with emscripten: https://stackoverflow.com/questions/28522171/specify-header-locations-for-c-compiler-compiling-r-code-with-emscripten
# Main compilation statement for emcc: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
# https://stackoverflow.com/questions/33674973/makefile-error-make-e-2-the-system-cannot-find-the-file-specified for problem that I encountered
emsdk_filepath = C:/emcc/emsdk/

plain:
	g++ ./src/converter.cpp ./src/main.cpp -o temp.exe
	./temp.exe

web:
	$(emsdk_filepath)/emsdk activate latest & emcc -lembind src/converter.cpp src/bindings.cpp -o scripts/converter.js -I$(emsdk_filepath) -s EXPORT_NAME=createModule -s MODULARIZE=1

# Reminded of del in https://unix.stackexchange.com/questions/726282/what-actually-is-causing-the-system-can-not-find-the-file-specified-problem-in
# If use rm, spawns a child process that fails
clean:
	del temp.exe