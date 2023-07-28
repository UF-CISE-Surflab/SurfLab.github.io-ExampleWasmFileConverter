#pragma once
#include <string>

using namespace std;

struct Vertex {
    // A structure for .obj vertices; ignores the possibility of w existing

    double x, y, z;      // For coordinates
    string remainder;    // For comments, etc.

    // Functions
    Vertex(double x, double y, double z);
    Vertex(string objString);
    void scaleZ(double amount);
    string getOutput();
};

class Converter {
    // Performs the actual conversion

    // Private variables associated with errors
    bool malformed_line;      // Should be used if a line is malformed so as to cause an error
    bool error_before_eof;    // If some error occurs that causes stop before end of file, set this on
    string lineWithError;     // Line that malformed_error occurred on
public:
    Converter();
    string stringConvert(string text);
    string flagReport();
};
