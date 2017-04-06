#include <utils/LogSystem.hpp>

int main(int, char** argv) {
    const std::string AppName = "TestLogSystem" ;
    Doom::LogSystem::Gravity minGravity = Doom::LogSystem::Gravity::Info ;

    Doom::LogSystem::Initialize(AppName + ".log", minGravity) ;
    std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;

    auto logSharedPtr = logWeakPtr.lock() ;
    if (logSharedPtr) {
        Doom::LogSystem::Gravity infoLevel = Doom::LogSystem::Gravity::Info ;
        logSharedPtr -> writeLine(infoLevel, "This is a simple information log.") ;
        logSharedPtr -> writeLine(infoLevel, "A message with ", 2, " floating point values: ", 42.1234, " and ", 5.8f) ;

        logSharedPtr -> printLine(infoLevel, "This message is only on the console.") ;
        logSharedPtr -> printLine(infoLevel, "The console can print the following ", 2, " values: ", 789.123, " and ", 456.7f) ;

        Doom::LogSystem::Gravity debugLevel = Doom::LogSystem::Gravity::Debug ;
        logSharedPtr -> writeLine(debugLevel, "This message cannot be printed because it is a Debug message...") ;
    }

    return EXIT_SUCCESS ;
}
