/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       GUILEStrings.h             */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    03/22/2014                 */
/* UPDATE:      03/22/2014                 */
/*                                         */
/* Group of all the strings used in one    */
/* place.                                  */
/*******************************************/

#ifndef __GUILE__TEXT_STRINGS_INCLUDE__
#define __GUILE__TEXT_STRINGS_INCLUDE__


namespace Guile {
    namespace GUIPanelMsg {
        namespace Error {
            extern const char* UndefinedLayer ;
            extern const char* CreationFailed ;
        } ;
    } ;

    namespace GUITabbedElementMsg {
        namespace Error {
            extern const char* IsInconsistentOnDestruction ;
            extern const char* IsInconsistentBeforeAddingTab ;
            extern const char* IsInconsistentAfterAddingTab ;
            extern const char* IsInconsistent ;
            extern const char* UndefinedPanel ;
        } ;
    }
} ;


#endif
