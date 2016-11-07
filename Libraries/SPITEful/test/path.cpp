#include <debug/Test.h>
#include <utils/Path.h>
#include <iostream>

using namespace std ;
using namespace Spite ;

int main() {
    Log_InitSystem("path.log", LogDebug) ;

    string cwd ;
    Path::GetCurrentDirectory(cwd) ;
    cout << "CWD  = " << cwd << endl << endl ;

    Path relative1("../../file_test.png") ;
    cout << "../../file_test.png" << endl ;
    cout << "Path = " << relative1.getAbsolutePath() << endl ;
    cout << "Name = " << relative1.getFilename() << endl ;
    cout << "Ext. = " << relative1.getExtension() << endl ;

    cout << endl ;

    Path relative2("picture.jpeg") ;
    cout << "picture.jpeg" << endl ;
    cout << "Path = " << relative2.getAbsolutePath() << endl ;
    cout << "Name = " << relative2.getFilename() << endl ;
    cout << "Ext. = " << relative2.getExtension() << endl ;

    cout << endl ;

    Path relative3("./here") ;
    cout << "./here" << endl ;
    cout << "Path = " << relative3.getAbsolutePath() << endl ;
    cout << "Name = " << relative3.getFilename() << endl ;
    cout << "Ext. = " << relative3.getExtension() << endl ;

    cout << endl ;

    Path relative4("../toto.is.gone/here") ;
    cout << "../toto.is.gone/here" << endl ;
    cout << "Path = " << relative4.getAbsolutePath() << endl ;
    cout << "Name = " << relative4.getFilename() << endl ;
    cout << "Ext. = " << relative4.getExtension() << endl ;

    cout << endl ;

    Path relative5("../../bin/cacao/file_test.png") ;
    cout << "../../bin/cacao/file_test.png" << endl ;
    cout << "Path = " << relative5.getAbsolutePath() << endl ;
    cout << "Name = " << relative5.getFilename() << endl ;
    cout << "Ext. = " << relative5.getExtension() << endl ;

    cout << endl ;    

    Path absolute("/home/bibi09/toto.cpp") ;
    cout << "/home/bibi09/toto.cpp" << endl ;
    cout << "Path = " << absolute.getAbsolutePath() << endl ;
    cout << "Name = " << absolute.getFilename() << endl ;
    cout << "Ext. = " << absolute.getExtension() << endl ;
}