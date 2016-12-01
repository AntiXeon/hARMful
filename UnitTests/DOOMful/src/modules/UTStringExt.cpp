#include <modules/UTStringExt.hpp>
#include <utils/StringExt.hpp>
#include <string>
#include <iostream>

using namespace Doom::StringExt ;

namespace UTDoom {
    UTStringExt::UTStringExt() {}

    UTStringExt::~UTStringExt() {}

    void UTStringExt::runTests() {
        changeCase() ;
        trim() ;
        split() ;
        numberToString() ;
        random() ;
    }

    void UTStringExt::changeCase() {
        changeCharCase() ;
        changeFirstCase() ;
        changeWordsCase() ;
    }

    void UTStringExt::changeCharCase() {
        std::string demo = "% lorem IPSUM 9 dolor sit amet." ;

        // Upper case "l" from "lorem".
        {
            const size_t characterIndex = 2 ;
            check(demo[characterIndex] == 'l') ;
            CaseChar(demo, characterIndex, CharacterCase::Upper) ;
            check(demo[characterIndex] == 'L') ;
            check(demo == "% Lorem IPSUM 9 dolor sit amet.") ;
        }

        // Lower case "s" from "IPSUM".
        {
            const size_t characterIndex = 10 ;
            check(demo[characterIndex] == 'S') ;
            CaseChar(demo, characterIndex, CharacterCase::Lower) ;
            check(demo[characterIndex] == 's') ;
            check(demo == "% Lorem IPsUM 9 dolor sit amet.") ;
        }

        // Lower/upper case "%"
        {
            const size_t characterIndex = 0 ;
            check(demo[characterIndex] == '%') ;
            CaseChar(demo, characterIndex, CharacterCase::Lower) ;
            check(demo[characterIndex] == '%') ;
            CaseChar(demo, characterIndex, CharacterCase::Upper) ;
            check(demo[characterIndex] == '%') ;
            check(demo == "% Lorem IPsUM 9 dolor sit amet.") ;
        }

        // Lower/upper case "9"
        {
            const size_t characterIndex = 14 ;
            check(demo[characterIndex] == '9') ;
            CaseChar(demo, characterIndex, CharacterCase::Lower) ;
            check(demo[characterIndex] == '9') ;
            CaseChar(demo, characterIndex, CharacterCase::Upper) ;
            check(demo[characterIndex] == '9') ;
            check(demo == "% Lorem IPsUM 9 dolor sit amet.") ;
        }
    }

    void UTStringExt::changeFirstCase() {
        // Upper case of the first lowercase letter.
        {
            std::string demo = "fusce augue mauris, ullamcorper a" ;
            CaseFirst(demo, CharacterCase::Upper) ;
            check(demo[0] == 'F') ;
            check(demo == "Fusce augue mauris, ullamcorper a") ;
        }

        // Upper case of the first uppercase letter.
        {
            std::string demo = "Maecenas ut massa hendrerit, consequat" ;
            CaseFirst(demo, CharacterCase::Upper) ;
            check(demo[0] == 'M') ;
            check(demo == "Maecenas ut massa hendrerit, consequat") ;
        }

        // Lower case of the first uppercase letter.
        {
            std::string demo = "Fusce augue mauris, ullamcorper a" ;
            CaseFirst(demo, CharacterCase::Lower) ;
            check(demo[0] == 'f') ;
            check(demo == "fusce augue mauris, ullamcorper a") ;
        }

        // Lower case of the first lowercase letter.
        {
            std::string demo = "maecenas ut massa hendrerit, consequat" ;
            CaseFirst(demo, CharacterCase::Lower) ;
            check(demo[0] == 'm') ;
            check(demo == "maecenas ut massa hendrerit, consequat") ;
        }

        // Lower case of the first number.
        {
            std::string demo = "8 nam suscipit arcu sit amet" ;
            CaseFirst(demo, CharacterCase::Lower) ;
            check(demo[0] == '8') ;
            check(demo == "8 nam suscipit arcu sit amet") ;
        }

        // Upper case of the special character.
        {
            std::string demo = "@ nam suscipit arcu sit amet" ;
            CaseFirst(demo, CharacterCase::Upper) ;
            check(demo[0] == '@') ;
            check(demo == "@ nam suscipit arcu sit amet") ;
        }
    }

    void UTStringExt::changeWordsCase() {
        // Usual sentence.
        {
            std::string demo = "Mauris quis auctor tellus." ;
            CaseWords(demo, CharacterCase::Upper) ;
            check(demo == "Mauris Quis Auctor Tellus.") ;
        }

        // Sentence without upper case.
        {
            std::string demo = "praesent porta urna dui, sed." ;
            CaseWords(demo, CharacterCase::Upper) ;
            check(demo == "Praesent Porta Urna Dui, Sed.") ;
        }

        // Sentence with special characters and numbers.
        {
            std::string demo = "23 nulla *#fr8; vitae (diam) ! eu." ;
            CaseWords(demo, CharacterCase::Upper) ;
            check(demo == "23 Nulla *#fr8; Vitae (diam) ! Eu.") ;
        }
    }

    void UTStringExt::trim() {
        // String without extra spaces.
        {
            std::string demo = "Curabitur elementum, arcu vitae" ;
            Trim(demo) ;
            check(demo == "Curabitur elementum, arcu vitae") ;
        }

        // String with extra spaces.
        {
            std::string demo = "  Duis non tellus neque.    " ;
            Trim(demo) ;
            check(demo == "Duis non tellus neque.") ;
        }

        // String with extra spaces.
        {
            std::string demo = "Aliquam gravida nisi      efficitur.   " ;
            Trim(demo) ;
            check(demo == "Aliquam gravida nisi      efficitur.") ;
        }

        // String with numbers only.
        {
            std::string demo = "     897'274.23" ;
            Trim(demo) ;
            check(demo == "897'274.23") ;
        }
    }

    void UTStringExt::split() {
        // Split with different characters.
        {
            std::string demo = "Proin@bibendum commodo#sem" ;
            std::vector<std::string> list = Split(demo, " #@") ;
            check(list.size() == 4) ;
            check(list[0] == "Proin") ;
            check(list[1] == "bibendum") ;
            check(list[2] == "commodo") ;
            check(list[3] == "sem") ;
        }

        // Split with possible empty strings.
        {
            std::string demo = "@Sed viverra dictum #@@ pharetra. " ;
            std::vector<std::string> list = Split(demo, " #@") ;
            check(list.size() == 4) ;
            check(list[0] == "Sed") ;
            check(list[1] == "viverra") ;
            check(list[2] == "dictum") ;
            check(list[3] == "pharetra.") ;
        }
    }

    void UTStringExt::numberToString() {
        // Integer conversion.
        {
            int demo = 58246 ;
            std::string demoStr = ToStringi(demo) ;
            check(demoStr == "58246") ;
        }

        // Float conversion (precision = 2).
        {
            float demo = 36745.264f ;
            std::string demoStr = ToStringf(demo) ;
            check(demoStr == "36745.26") ;
        }
    }

    void UTStringExt::random() {
        // Check length of the generated string with alphanumerical characters.
        {
            const int RandomLength = 17 ;
            std::string demo = Random(RandomLength) ;
            check(demo.size() == RandomLength) ;
        }

        // Check length of the generated string with any characters.
        {
            const int RandomLength = 10 ;
            std::string demo = Random(RandomLength, "#5") ;
            check(demo.size() == RandomLength) ;
        }
    }
}
