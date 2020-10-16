#include <iostream>
#include <string>
#include <fstream>
#include <exception>

using namespace std;

// Global variables
string input;
string fileName;
string line;

// Prototypes
string validateFileName(string input_p);
string convertLine(const string& line_p);

struct MyException : public exception {
    string what() {
        return "File could not be closed.";
    }
};

int main() {
    const string fileExtension = ".cpp";
    // Declare stream objects
    ifstream inStream;
    ofstream outStream;

    // Get file name from user
    while (true) {
        try {
            cout << "Enter the absolute path of the file: ";
            cin >> input;
            fileName = validateFileName(input);
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << ". Please try again." << endl;
        }
        catch (const exception& e) {
            cout << "Unknown exception happened" << endl;
        }
    }

    // Connect stream objects to file(s)
    try {
        inStream.open(fileName);
        outStream.open("output.txt", ios::app);
    }
    catch (const exception&) {
        cout << "File could not be open." << endl;
    }

    // Get the content of the file
    try {
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
            throw "File failed to open.";
        }
    }
    catch (const char* message) {
        cout << message << endl;
    }

    // Close resources
    try {
        inStream.close();
        outStream.close();
    }
    catch (MyException& e) {
        cout << e.what() << endl;
    }

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
        throw invalid_argument("File name does not end with '.cpp'");
    }
}

string convertLine(const string& line_p) {
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