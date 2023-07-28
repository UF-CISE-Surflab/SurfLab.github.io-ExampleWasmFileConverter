#pragma once
#include <string>

using namespace std;

struct Vertex {
    double x, y, z;      // For coordinates
    string remainder;    // For comments, etc.

    // Functions
    Vertex(double x, double y, double z);
    Vertex(string objString);
    void scaleZ(double amount);
    string getOutput();
};

class Converter {
    bool malformed_line;
    bool unknown_error;
    string lineWithError;
public:
    Converter();
    string stringConvert(string text);
    string flagReport();
};
