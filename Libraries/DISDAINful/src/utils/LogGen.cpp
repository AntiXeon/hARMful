#ifdef DEBUG_MODE

#include "LogGen.h"
#include <ctime>

using namespace std ;

LogGen LogGen::Singleton ;
ostringstream LogGen::StringStream ;

LogGen::LogGen() throw() {
    LogGen::instance().m_filename = "harmful.log" ;

    LogGen::instance().m_output.open(LogGen::instance().m_filename.c_str()) ;
    LogGen::instance().m_output << "==== LOG SAVED ON " << LogGen::instance().date() << " ====" << endl ;
}

LogGen::~LogGen() throw() {
    LogGen::instance().m_output << endl ;
    LogGen::instance().m_output.close() ;
}

LogGen& LogGen::instance() {
    return LogGen::Singleton ;
}


void LogGen::print(string log) {
    LogGen::instance().m_output << "[" << LogGen::instance().date() << "] " << log << endl ;
}

#endif
