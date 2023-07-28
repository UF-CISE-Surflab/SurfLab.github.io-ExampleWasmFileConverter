#include "converter.h"
#include <sstream>
#include <iostream>

using namespace std;

// Reviewed: https://cplusplus.com/reference/sstream/istringstream/istringstream/


//-----------------  Vertex Struct --------------------//
Vertex::Vertex(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    remainder = "";
}

Vertex::Vertex(string objString) {
    istringstream forRead(objString);
    // We will assume that no problems occurr ...
    string temp;
    // Looked up stod on web; got answer from programiz https://www.programiz.com/cpp-programming/string-float-conversion
    getline(forRead, temp, ' ');
    getline(forRead, temp, ' ');
    x = stod(temp);
    getline(forRead, temp, ' ');
    y = stod(temp);
    getline(forRead, temp, ' ');
    z = stod(temp);
    getline(forRead, remainder);

}

void Vertex::scaleZ(double amount) {
    z *= amount;
}

string Vertex::getOutput() {
    return "v " + to_string(x) + " " + to_string(y) + " " + to_string(z) + remainder;
}

//-------------------  Converter Class -------------------//
Converter::Converter() : malformed_line(false), unknown_error(false) {
    lineWithError = "";
}

string Converter::stringConvert(string textInput) {
    // Reset flags
    malformed_line = false;
    unknown_error = false;
    lineWithError = "";

    istringstream input(textInput);
    ostringstream output;

    // Dummy Parsing Code
    string line, code;         // Used to hold line and identifying code
    
    while (input.good()) {
        getline(input, line);
        
        // If a blank line, write with no adjustments
        // NOTE: Size 1 used to make it work with JavaScript
        if (line.size() < 2) {
            output << line << endl;
            continue;
        }

        // Main Parsing

        // If malformed, set flag and break.
        int spacePos = line.find(' ');
        if (spacePos == -1) {
            cout << "Malformed line" << endl;
            malformed_line = true;
            continue;
        }

        // Otherwise, get code specifiying the type of specification
        string code = line.substr(0, spacePos);

        // If a vector, parse, process, and output
        if (code == "v") {
            Vertex tempVec(line);
            tempVec.scaleZ(10.0);
            output << tempVec.getOutput();
        }

        // If not a vector, just output
        else
            output << line;

        // Add newline back in (was effectively discarded by getline)
        output << endl;
    }

    // If we did not get to the end of the file (end of the string) but stopped, error occurred.
    if (!input.eof()) {
        unknown_error = true;
    }

    return output.str();
}

/*
Get the flags that are output from processing. Can be displayed as an alert
*/
string Converter::flagReport() {
    string errorString = "malformed_line: " + to_string(malformed_line) + "; unknown_error: " + to_string(unknown_error);
    if (lineWithError != "")
        errorString += "; lineWithError = "  + lineWithError;
    return errorString;
}