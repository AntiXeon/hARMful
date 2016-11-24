#include <utils/LogSystem.hpp>

int main(int, char** argv) {
    const std::string AppName = "TestLogSystem" ;
    Doom::LogSystem::Gravity minGravity = Doom::LogSystem::Gravity::Info ;

    Doom::LogSystem::Initialize(AppName + ".log", minGravity) ;
    std::shared_ptr<Doom::LogSystem> log = Doom::LogSystem::GetInstance() ;

    Doom::LogSystem::Gravity infoLevel = Doom::LogSystem::Gravity::Info ;
    log -> writeLine(infoLevel, "This is a simple information log.") ;
    log -> writeLine(infoLevel, "A message with ", 2, " floating point values: ", 42.1234, " and ", 5.8f) ;

    log -> printLine(infoLevel, "This message is only on the console.") ;
    log -> printLine(infoLevel, "The console can print the following ", 2, " values: ", 789.123, " and ", 456.7f) ;

    Doom::LogSystem::Gravity debugLevel = Doom::LogSystem::Gravity::Debug ;
    log -> writeLine(debugLevel, "This message cannot be printed because it is a Debug message...") ;

    return EXIT_SUCCESS ;
}
