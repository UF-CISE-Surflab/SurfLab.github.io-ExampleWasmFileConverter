#include "converter.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    string input;
    
    Converter converter;
    cout << "Input ('End' to stop): ";
    cin >> input;

    while (input != "End") {
        cout << "Output: " << (converter.stringConvert(input)) << endl;
        cout << "Input: ('End' to stop): ";
        cin >> input;
    }

    return 0;
}