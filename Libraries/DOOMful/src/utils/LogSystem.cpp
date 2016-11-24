#include <utils/LogSystem.hpp>
#include <utils/Translation.hpp>
#include <DOOMStrings.hpp>

namespace Doom {
    std::shared_ptr<LogSystem> LogSystem::Instance ;

    LogSystem::LogSystem(const std::string& path, const Gravity& minLevel) {
        m_minLevel = minLevel ;
        m_printer = std::make_shared<FilePrinter>(path) ;
    }

    LogSystem::~LogSystem() noexcept {
        m_printer = nullptr ;
    }

    std::string LogSystem::formatCurrentDateTime() {
        return "[" + Time::GetDateTime() + "] " ;
    }

    void LogSystem::Initialize(const std::string& path, const Gravity& minLevel) throw(std::runtime_error) {
        if (Instance) {
            std::string errorMessage = Translation::Get(Texts::LogSys_AlreadyInitialized) ;
            throw std::runtime_error(errorMessage) ;
        }

        Instance = std::shared_ptr<LogSystem>(new LogSystem(path, minLevel), garbage) ;
    }

    std::shared_ptr<LogSystem> LogSystem::GetInstance() throw(std::runtime_error) {
        if (!Instance) {
            std::string errorMessage = Translation::Get(Texts::LogSys_NotInitialized) ;
            throw std::runtime_error(errorMessage) ;
        }

        return Instance ;
    }
}
