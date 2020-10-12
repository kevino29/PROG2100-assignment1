#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Global variables
string input;
string fileName;
string line;

// Prototypes
string validateFileName(string input_p);
string convertLine(string line_p);

int main() {
    const string fileExtension = ".cpp";
    // Declare stream objects
    ifstream inStream;
    ofstream outStream;

    // Get file name from user
    cout << "Enter the absolute path of the file: ";
    cin >> input;
//    cout << input << endl;
    fileName = validateFileName(input);

    // Connect stream objects to file(s)
    inStream.open(fileName);
    outStream.open("output.txt", ios::app);

    // Get the content of the file
    if (inStream.is_open()) {
        outStream << "<PRE>" << endl;
        while(!inStream.eof()) {
            getline(inStream, line);
            line = convertLine(line);
            outStream << line << endl;
        }
        outStream << "</PRE>" << endl;
    }

    else {
        cout << "File failed to open." << endl;
    }

    // Close resources
    inStream.close();
    outStream.close();

    return 0;
}

string validateFileName(string input_p) {
    const string extension = ".cpp";
    string buffer;

    if (input_p.length() > 4) {
        for (int i = input_p.length() - 4; i < input_p.length(); i++) {
            buffer += input_p[i];
        }
    }

    if (buffer == extension) {
        return input_p;
    }
    else {
        return input_p + extension;
    }
}

string convertLine(string line_p) {
    string buffer;

    for (char i : line_p) {
        switch (i) {
            case '<':
                buffer += "&lt;";
                break;
            case '>':
                buffer += "&gt;";
                break;
            default:
                buffer += i;
                break;
        }
    }
    return buffer;
}