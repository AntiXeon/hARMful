// This file is part of hARMful.
//
// hARMful is free software: you can redistribute
// it and/or modify it under the terms of the GNU
// General  Public License  as published  by  the
// Free Software Foundation,  either version 3 of
// the  License,  or (at your option)  any  later
// version.
//
// hARMful is  distributed in  the hope  that  it
// will  be  useful, but  WITHOUT  ANY  WARRANTY;
// without   even   the   implied   warranty   of
// MERCHANTABILITY  or  FITNESS FOR  A PARTICULAR
// PURPOSE.  See the  GNU General  Public License
// for more details.
//
// You  should have  received a  copy of  the GNU
// General  Public  License  along  with hARMful.
// If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <assert.h>

using namespace std ;

#include "types.static"
#include "strings.static"

int main(int argc, char** argv) {
    assert(argc > 2) ;
    cout << endl ;

    initTypesConversion() ;

    fstream output_file ;
    output_file.open(argv[2], ios_base::out) ;
    assert(output_file.is_open()) ;

    output_file
        << "/*******************************************/" << endl <<
            "/* HOPEful - Part of the hARMful Engine    */" << endl <<
            "/*                                         */" << endl <<
            "/* AUTHOR :     Denis CARLUS               */" << endl <<
            "/* VERSION:     1.0                        */" << endl <<
            "/* CREATION:    03/19/2015                 */" << endl <<
            "/* UPDATE:      03/19/2015                 */" << endl <<
            "/*                                         */" << endl <<
            "/* Inline OpenGL3.3 functions.             */" << endl <<
            "/*******************************************/" << endl << endl ;

    output_file
        << "/**********************************************" << endl <<
           "This file is part of hARMful." << endl << endl <<

           "hARMful is free software: you can redistribute" << endl <<
           "it and/or modify it under the terms of the GNU" << endl <<
           "General  Public License  as published  by  the" << endl <<
           "Free Software Foundation,  either version 3 of" << endl <<
           "the  License,  or (at your option)  any  later" << endl <<
           "version." << endl << endl <<

           "hARMful is  distributed in  the hope  that  it" << endl <<
           "will  be  useful, but  WITHOUT  ANY  WARRANTY;" << endl <<
           "without   even   the   implied   warranty   of" << endl <<
           "MERCHANTABILITY  or  FITNESS FOR  A PARTICULAR" << endl <<
           "PURPOSE.  See the  GNU General  Public License" << endl <<
           "for more details." << endl << endl <<

           "You  should have  received a  copy of  the GNU" << endl <<
           "General  Public  License  along  with hARMful." << endl <<
           "If not, see <http://www.gnu.org/licenses/>." << endl <<
           "**********************************************/" << endl << endl;

    fstream file ;
    file.open(argv[1], ios_base::in) ;
    if (file.is_open()) {
        string line ;
        while (getline(file, line)) {
            if (line.length() > 1) {

                string returnedType ;
                string convertedReturnedType ;
                string returnOrNotReturn ;
                string functionName ;
                string convertedFunctionName ;
                string parametersList ;
                string convertedParametersList ;
                string parameterNamesList ;

                vector<string> glParametersArray ;
                vector<string> convertedParametersArray ;
                vector<string> parametersNamesArray ;

                size_t positionFunctionName = 0 ;

                // Return type
                extractReturnedType(line, returnedType, positionFunctionName) ;
                convertedReturnedType = typesConversion[returnedType] ;
                returnOrNotReturn = (convertedReturnedType == "void") ? "" : "return " ;

                // Function name
                extractFunctionName(line, functionName, positionFunctionName) ;
                convertFunctionName(functionName, convertedFunctionName) ;

                // Parameters
                extractParametersList(line, parametersList) ;
                explodeParametersList(parametersList, glParametersArray) ;
                convertParametersTypes(glParametersArray, convertedParametersArray, parametersNamesArray) ;
                implodeParametersList(convertedParametersArray, convertedParametersList) ;
                implodeParametersNameList(parametersNamesArray, parameterNamesList) ;


                // Test explosion of parameters string
                output_file
                    << "inline "
                    << convertedReturnedType << " " << convertedFunctionName << "(" << convertedParametersList << ") {" << endl
                    << "    " << returnOrNotReturn << functionName << "(" << parameterNamesList << ") ;" << endl
                    << "}" << endl
                << endl ;
            }
            else if (line.length() == 1 && line[0] == '\n') {
                output_file << endl ;
            }
        }
    }

    output_file.close() ;
    file.close() ;

    return 0 ;
}
