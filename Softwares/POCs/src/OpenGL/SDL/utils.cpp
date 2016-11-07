#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std ;


void readShaderSource(const string& file, string& output) {
	try {
		ifstream input ;
        input.open(file.c_str()) ;

		if (input.is_open()) {
			// Get the size of the file content to optimize allocations
			input.seekg(0, input.end) ;
			int length = input.tellg() ;
			input.seekg(0, input.beg) ;

			// Read the file and store its content in the output string
			output = "" ;
			output.reserve(length) ;
			string curLine ;
			// Parse the file
            while(getline(input, curLine))
            	output += curLine + "\n" ;
		}
		else {
            cerr << "The file " << file << " cannot be opened..." << endl ;
        }
	}
	catch(...) {
		cerr << "Unexpected error while reading file " << file << endl ;
	}
}
