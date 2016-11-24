#include <utils/LogSystem.hpp>

int main(int, char** argv) {
    const std::string AppName = "TestLogSystem" ;
    Doom::LogSystem::Gravity minGravity = Doom::LogSystem::Gravity::Info ;

    Doom::LogSystem::Initialize(AppName + ".log", minGravity) ;
    std::shared_ptr<Doom::LogSystem> log = Doom::LogSystem::GetInstance() ;

    log -> writeLine(Doom::LogSystem::Gravity::Info, "This is a simple information log.") ;

    return EXIT_SUCCESS ;
}
