#include "converter.h"
#include <sstream>
#include <iostream>

using namespace std;

// Reviewed: https://cplusplus.com/reference/sstream/istringstream/istringstream/

Converter::Converter() {}

string Converter::stringConvert(string text) {
    istringstream input(text);
    ostringstream output;

    char temp;
    while (input >> temp) {
        output << (char)(temp + 1);
    }

    if (!input.eof()) {
        // Do some error message
    }

    return output.str();
}