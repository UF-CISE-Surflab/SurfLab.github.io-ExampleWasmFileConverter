/**
 * Bindings to allow emscripten to compile the code to WebAssembly.
 * Source for binding classes: https://blog.esciencecenter.nl/using-c-in-a-web-app-with-webassembly-efd78c08469
 * Source for binding data types: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
*/
#include <emscripten/bind.h>
#include "converter.h"

using namespace emscripten;
EMSCRIPTEN_BINDINGS(Converter) {
    class_<Converter>("Converter")
        .constructor<>()
        .function("stringConvert", &Converter::stringConvert)
        .function("flagReport", &Converter::flagReport)
        ;
}
