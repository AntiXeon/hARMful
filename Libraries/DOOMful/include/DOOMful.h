/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		DOOMful.h                  */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/22/2014                 */
/* UPDATE:      03/22/2014                 */
/*                                         */
/* Main file to include to access DOOMful  */
/* API.                                    */
/*******************************************/

#ifndef __DOOM__MAIN_INCLUDE__
#define __DOOM__MAIN_INCLUDE__


#define DOOM_VERSION	100


#include "DOOMStrings.h"
#include "Types.h"

// DEBUG TOOLS
#include "debug/Print.h"
#include "debug/Test.h"
#include "debug/Log.h"


// UTILITIES
#include "utils/Processor.h"
#include "utils/Time.h"
#include "utils/Console.h"
#include "utils/DefragmentedList.h"
#include "utils/Mutex.h"
#include "utils/PairList.h"
#include "utils/Profiler.h"
#include "utils/Random.h"
#include "utils/SizedStack.h"
#include "utils/String.h"
#include "utils/Thread.h"
#include "utils/ThreadManager.h"


// INTERFACES
#include "interfaces/IClearable.h"
// Model - View - Controller
#include "interfaces/MVC/IModel.h"
#include "interfaces/MVC/IView.h"
#include "interfaces/MVC/IController.h"

// DESIGN PATTERNS
// Factory
#include "patterns/Factory/Factory.h"
//  Iterator
#include "patterns/Iterator/Iterable.h"
#include "patterns/Iterator/Iterator.h"
//  Observer
#include "patterns/Observer/Observable.h"
#include "patterns/Observer/ObserverInterface.h"
//  Singleton
#include "patterns/Singleton/Singleton.h"
// Object Pool
#include "patterns/ObjectPool/ObjectPool.h"

// EXCEPTIONS
#include "exceptions/ArrayOutOfBoundException.h"
#include "exceptions/Exception.h"
#include "exceptions/ExceptionSkeleton.h"
#include "exceptions/InvalidArraySizeException.h"
#include "exceptions/IOException.h"


#endif
