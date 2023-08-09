#include "converter.h"
#include <sstream>
#include <iostream>
#include "mesh_to_igs.hpp"


using namespace std;

// Reviewed: https://cplusplus.com/reference/sstream/istringstream/istringstream/


//-----------------  Vertex Struct --------------------//
/**
 * Standard vertex constructor
 * @param x: The x-coordinate
 * @param y: The y-coordinate
 * @param z: The z-coordinate
*/
Vertex::Vertex(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    remainder = "";
}

/**
 * Vertex constructor for string input. Note: Assumes that the line is not malformed
 * @param objString: The line representing the vector from the .obj file
*/
Vertex::Vertex(string objString) {
    istringstream forRead(objString);
    // We will assume that no problems occurr
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

/**
 * Scale the z-coordinate of the vertex by amount
*/
void Vertex::scaleZ(double amount) {
    z *= amount;
}

/**
 * Get the .obj line representation of the vertex
*/
string Vertex::getOutput() {
    return "v " + to_string(x) + " " + to_string(y) + " " + to_string(z) + remainder;
}

//-------------------  Converter Class -------------------//
/**
 * Constructor for the converter.
 * While not really necessary, set the errors to appropriate default values.
*/
Converter::Converter() : malformed_line(false), error_before_eof(false) {
    lineWithError = "";
}


/**
 * Do the conversion.
 * @param textInput: The string to convert
 * @returns: The string resulting from teh conversion
*/
string Converter::stringConvert(string textInput) {
    // Reset flags
    malformed_line = false;
    error_before_eof = false;
    lineWithError = "";


    // Set up input and output streams
    istringstream input(textInput);
    ostringstream output;

    output << mesh_to_igs(input) << endl;

    // Dummy Parsing Code

     // Used to hold line and identifying code
    string line, code;

    // while (input.good()) {
    //     getline(input, line);
    //
    //     // If a blank line, write with no adjustments
    //     // NOTE: Size 1 used to make it work with JavaScript and Wasm
    //     if (line.size() < 2) {
    //         output << line << endl;
    //         continue;
    //     }
    //
    //     // Main Parsing
    //
    //     // If malformed, set flag and break.
    //     int spacePos = line.find(' ');
    //     if (spacePos == -1) {
    //         cout << "Malformed line" << endl;
    //         malformed_line = true;
    //         continue;
    //     }
    //
    //     // Otherwise, get code specifiying the type of specification
    //     string code = line.substr(0, spacePos);
    //
    //     // If a vector, parse, process, and output
    //     if (code == "v") {
    //         Vertex tempVec(line);
    //         tempVec.scaleZ(10.0);
    //         output << tempVec.getOutput();
    //     }
    //
    //     // If not a vector, just output
    //     else
    //         output << line;
    //
    //     // Add newline back in (was effectively discarded by getline)
    //     output << endl;
    // }

    // If we did not get to the end of the file (end of the string) but stopped, error occurred.
    if (!input.eof()) {
        error_before_eof = true;
    }

    return output.str();
}

/**
 * Get the flags that are output from processing. Can be displayed as an alert.
*/
string Converter::flagReport() {
    string errorString;
    if (malformed_line)
        errorString = "malformed_line: " + lineWithError;
    else if (error_before_eof)
        errorString = "unknown_error_before_eof";
    else
        errorString = "No errors.";
    return errorString;
}
