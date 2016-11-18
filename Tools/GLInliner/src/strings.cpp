/**
 * strings.cpp
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *
 * @Author:      Denis CARLUS
 * @Created on:  10-Nov-2016
 * @Last change: 18-Nov-2016
 */

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

static string search(string& line, const string& start, const string& end) {
    size_t positionFirstSpace = line.find(start) + 1 ;
    size_t positionParenthesis = line.find(end) ;
    size_t lengthFunctionName = positionParenthesis - positionFirstSpace ;
    return line.substr(positionFirstSpace, lengthFunctionName) ;
}

static void extractReturnedType(string& line, string& returnedType, size_t& positionFunctionName) {
    // type funcName(paramType1 param1, paramType2 param2, ...);
    size_t positionFirstSpace = line.find(" ") ;
    returnedType = line.substr(0, positionFirstSpace) ;
    positionFunctionName = positionFirstSpace + 1 ;

    if (returnedType == "const") {
        size_t positionSecondSpace = line.find(" ", positionFirstSpace + 1) ;
        returnedType += line.substr(positionFirstSpace, positionSecondSpace - positionFirstSpace) ;
        positionFunctionName = positionSecondSpace + 1 ;
    }
}

static void extractFunctionName(string& line, string& functionName, size_t positionFunctionName) {
    // type funcName(paramType1 param1, paramType2 param2, ...);
    //functionName = search(line, " ", "(") ;

    size_t positionParenthesis = line.find("(") ;
    size_t lengthFunctionName = positionParenthesis - positionFunctionName ;
    functionName = line.substr(positionFunctionName, lengthFunctionName) ;
}

static void convertFunctionName(string& glFunctionName, string& convertedFunctioName) {
    const int caseDiffASCII = 'a' - 'A' ;

    // type funcName(paramType1 param1, paramType2 param2, ...);
    assert(glFunctionName[0] == 'g') ;
    assert(glFunctionName[1] == 'l') ;

    convertedFunctioName = glFunctionName.substr(2);
    // Make first letter be lowercase.
    if (convertedFunctioName[0] >= 'A' && convertedFunctioName[0] <= 'Z') {
        convertedFunctioName[0] = convertedFunctioName[0] + caseDiffASCII ;
    }
}

static void extractParametersList(string& line, string& parameters) {
    // type funcName(paramType1 param1, paramType2 param2, ...);
    parameters = search(line, "(", ")") ;
}

static void explodeParametersList(string& parametersList, vector<string>& parametersArray) {
    string param ;
    size_t positionComma = parametersList.find(",") ;

    // Get the first parameter
    if (positionComma != string::npos) {
        param = parametersList.substr(0, positionComma) ;
    }
    else {
        param = parametersList ;
    }

    if ((!param.empty()) && (param != "void")) {
        parametersArray.push_back(param) ;
    }


    while (positionComma != string::npos) {
        positionComma++ ;
        size_t positionCommaNew = parametersList.find(",", positionComma) ;
        size_t diff = positionCommaNew - positionComma ;

        if (positionComma != string::npos) {
            param = parametersList.substr(positionComma, diff) ;
            parametersArray.push_back(param) ;
            positionComma = positionCommaNew ;
        }
    }
}

static void convertParametersTypes(vector<string>& parametersArray, vector<string>& convertedParametersArray, vector<string>& parametersNames) {
    size_t parametersCount = parametersArray.size() ;

    convertedParametersArray.clear() ;

    for (int index = 0 ; index < parametersCount ; ++index) {
        string parameter = parametersArray[index] ;

        size_t positionFirstSpace = parameter.rfind(" ") ;
        string parameterType = parameter.substr(0, positionFirstSpace) ;
        string parameterName = parameter.substr(positionFirstSpace + 1) ;
        string parameterTypeConverted = typesConversion[parameterType] ;

        map<string,string>::iterator it = typesConversion.find(parameterType) ;
        convertedParametersArray.push_back(parameterTypeConverted + " " + parameterName) ;

        parametersNames.push_back(parameterName) ;
    }
}

static void implodeParametersList(vector<string>& convertedParametersArray, string& convertedParametersList) {
    convertedParametersList = "" ;

    int max = convertedParametersArray.size() - 1 ;
    if (max < 0) return ;

    for (size_t index = 0 ; index < max ; ++index)
        convertedParametersList += convertedParametersArray[index] + ", " ;
    convertedParametersList += convertedParametersArray[max] ;
}

static void implodeParametersNameList(vector<string>& parametersNamesArray, string& parametersNamesList) {
    parametersNamesList = "" ;

    int max = parametersNamesArray.size() - 1 ;
    if (max < 0) return ;

    for (int index = 0 ; index < max ; ++index)
        parametersNamesList += parametersNamesArray[index] + ", " ;
    parametersNamesList += parametersNamesArray[max] ;
}
