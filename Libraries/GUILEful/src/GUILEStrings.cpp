/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       GUILEStrings.cpp           */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    03/22/2014                 */
/* UPDATE:      03/22/2014                 */
/*                                         */
/* Group of all the strings used in one    */
/* place.                                  */
/*******************************************/


#include <GUILEStrings.h>


namespace Guile {
    namespace GUIPanelMsg {
        namespace Error {
            const char* UndefinedLayer =                                        "Panel has undefined layout." ;
            const char* CreationFailed =                                        "Layout creation failed." ;
        } ;
    } ;

    namespace GUITabbedElementMsg {
        namespace Error {
            const char* IsInconsistentOnDestruction =                           "Inconsistent amount of tabs on destruction." ;
            const char* IsInconsistentBeforeAddingTab =                         "Inconsistent amount of tabs before adding tab." ;
            const char* IsInconsistentAfterAddingTab =                          "Inconsistent amount of tabs after adding tab." ;
            const char* IsInconsistent =                                        "Inconsistent amount of tabs." ;
            const char* UndefinedPanel =                                        "Added tab has undefined contained panel." ;
        } ;
    }
} ;
