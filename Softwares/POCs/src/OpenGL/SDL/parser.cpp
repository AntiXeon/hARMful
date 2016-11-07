#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <time.h>
#include <stdlib.h>

using namespace std ;


void readOBJ(const string& path,
             vector<GLfloat>& vertice,
             vector<GLuint>& verticeArray) {
	srand(time(NULL)) ;

    try {
        ifstream input ;
        input.open(path.c_str()) ;

        if (input.is_open()) {
            int index = 0 ;
            string curLine, lineHeader ;
            GLfloat vertexCoord ;
            GLuint vertexID0, vertexID1, vertexID2 ;
            int color0, color1, color2 ;

            while(getline(input, curLine)) {
                // Parse the file
                if (!curLine.empty() || curLine[0] != '#') {
                    lineHeader.clear() ;
                    istringstream iss(curLine) ;
                    iss >> lineHeader ;

                    if (!lineHeader.empty()) {
                        if (lineHeader[0] == 'v') {
                            if (lineHeader.length() == 1) {
								vertice.push_back(0.5f) ;
								color0 = vertice.size() - 1 ;
								vertice.push_back(0.5f) ;
								color1 = vertice.size() - 1 ;
								vertice.push_back(0.5f) ;
								color2 = vertice.size() - 1 ;

                                // Information on vertice position
                                iss >> vertexCoord ;
                                vertice.push_back(vertexCoord) ;
                                vertice[color0] = vertexCoord ;
                                iss >> vertexCoord ;
                                vertice.push_back(vertexCoord) ;
                                vertice[color1] = vertexCoord ;
                                iss >> vertexCoord ;
                                vertice.push_back(vertexCoord) ;
                                vertice[color2] = vertexCoord ;
                            }
                        }
                        else if (lineHeader[0] == 'f') {
                            // Read informations about the face as shown below:
                            // f vertex0/texture0/normalFace vertex1/texture1/normalFace vertex2/texture2/normalFace
                            // Here we only keep the vertexes index.
                            sscanf(curLine.c_str(),
                                   "%*s %d//%*d %d//%*d %d//%*d",
                                   &vertexID0, &vertexID1, &vertexID2) ;

                            // Create a triangle with the parsed vertex indices
                            verticeArray.push_back(vertexID0 - 1) ;
                            verticeArray.push_back(vertexID1 - 1) ;
                            verticeArray.push_back(vertexID2 - 1) ;
                        }
                    }
                }
            }
        }
        else {
        	cerr << "File not opened: " << path << endl ;
        }
    }
    catch(...) {
        cout << "Unexpected error while reading file..." << endl ;
    }
}
