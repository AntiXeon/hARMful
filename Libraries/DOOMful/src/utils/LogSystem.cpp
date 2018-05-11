#include <utils/LogSystem.hpp>
#include <utils/Translation.hpp>
#include <DOOMStrings.hpp>

namespace Doom {
    std::shared_ptr<LogSystem> LogSystem::Instance ;
    std::mutex LogSystem::ClassMutex ;

    LogSystem::LogSystem(const std::string& path, const Gravity minLevel) {
        m_minLevel = minLevel ;
        m_printer = std::make_shared<FilePrinter>(path) ;
    }

    LogSystem::~LogSystem() noexcept {
        m_printer = nullptr ;
    }

    std::string LogSystem::formatCurrentDateTime() {
        return "[" + Time::GetDateTime() + "] " ;
    }

    void LogSystem::Initialize(const std::string& path, const Gravity minLevel) {
        ClassMutex.lock() ;
        {
            // The instance has already been initialized. This is not supported
            // and this behavior throws an exception. However, this is not a
            // critical error and the exception can be caught to continue the
            // execution.
            if (Instance) {
                std::string errorMessage = Translation::Get(Texts::LogSys_AlreadyInitialized) ;
                throw std::runtime_error(errorMessage) ;
            }

            Instance = std::shared_ptr<LogSystem>(new LogSystem(path, minLevel)) ;
        }
        ClassMutex.unlock() ;
    }

    std::weak_ptr<LogSystem> LogSystem::GetInstance() {
        ClassMutex.lock() ;
        {
            // The instance has not been initialized. The instance pointer is
            // thus a null pointer and the application should not use it.
            if (!Instance) {
                std::string errorMessage = Translation::Get(Texts::LogSys_NotInitialized) ;
                throw std::runtime_error(errorMessage) ;
            }
        }
        ClassMutex.unlock() ;

        return Instance ;
    }
}
