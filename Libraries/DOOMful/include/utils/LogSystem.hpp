#ifndef __DOOM__LOG_SYSTEM__
#define __DOOM__LOG_SYSTEM__

#include <patterns/singleton/Singleton.hpp>
#include <utils/Time.hpp>
#include <utils/printers/Console.hpp>
#include <utils/printers/FilePrinter.hpp>
#include <cstdint>
#include <memory>
#include <mutex>

namespace Doom {
    /**
     * System to write logs in the Console and/or in a file.
     */
    class LogSystem : private Singleton {
        public:
            /**
             * Level of gravity of the log messages.
             */
            enum class Gravity: int8_t {
                Critical = 0,
                Error,
                Warning,
                Info,
                Debug
            } ;

        private:
            /**
             * The unique instance of the LogSystem.
             */
            static std::shared_ptr<LogSystem> Instance ;

            /**
             * Avoid concurrent accesses to the LogSystem.
             */
            std::mutex m_mutex ;

            /**
             * Console of the LogSystem.
             */
            Console m_console ;

            /**
             * File printer to save important log messages.
             */
            std::shared_ptr<FilePrinter> m_printer ;

            /**
             * Minimal level to write logs, lower gravity messages are ignored.
             */
            Gravity m_minLevel ;

        private:
            /**
             * Instantiate the LogSystem.
             * @param   path        Path to the file that will contain the
             *                      output log messages.
             * @param   minLevel    Minimal level of the log system messages to
             *                      be written.
             */
            LogSystem(const std::string& path, const Gravity& minLevel) ;

            /**
             * Destruction of the LogSystem.
             */
            virtual ~LogSystem() noexcept ;

            /**
             * Function to delete the LogSystem from the shared_ptr of the
             * unique instance.
             * @param sys   The pointer to manually delete.
             */
            friend void garbage(LogSystem* sys) ;

            /**
             * Format the current date and time to be printed in the logs.
             * @return String representing the printed date and time in the
             *         logs.
             */
            std::string formatCurrentDateTime() ;

        public:
            /**
             * Initialize the LogSystem. This is required before any call to the
             * GetInstance function.
             * @param   path        Path to the file that will contain the
             *                      output log messages.
             * @param   minLevel    Minimal level of the log system messages to
             *                      be written.
             * @exception   An exception is thrown if the LogSystem is
             *              initialized more than once.
             */
            static void Initialize(const std::string& path, const Gravity& minLevel) throw(std::runtime_error) ;

            /**
             * Get the unique instance of the LogSystem.
             * @exception   A runtime error is thrown if the instance is got
             *              before it has been initialized.
             */
            static std::shared_ptr<LogSystem> GetInstance() throw(std::runtime_error) ;

            /**
             * Write a message on the Console and the FilePrinter.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             */
            template<class T>
            void writeLine(const Gravity& level, const T& value) {
                if (level <= m_minLevel) {
                    std::string dateTime = formatCurrentDateTime() ;

                    m_mutex.lock() ;
                    {
                        m_console.writeLine(dateTime, value) ;
                        m_printer -> writeLine(dateTime, value) ;
                    }
                    m_mutex.unlock() ;
                }
            }

            /**
             * Write a message on the Console and the FilePrinter.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
            template<class T, class ... Args>
            void writeLine(const Gravity& level, const T& value, const Args& ... args) {
                if (level <= m_minLevel) {
                    std::string dateTime = formatCurrentDateTime() ;

                    m_mutex.lock() ;
                    {
                        m_console.write(dateTime) ;
                        m_console.writeLine(value, args...) ;

                        m_printer -> write(dateTime) ;
                        m_printer -> writeLine(value, args...) ;
                    }
                    m_mutex.unlock() ;
                }
            }

            /**
             * Write a message on the Console.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             */
            template<class T>
            void printLine(const Gravity& level, const T& value) {
                if (level <= m_minLevel) {
                    std::string dateTime = formatCurrentDateTime() ;

                    m_mutex.lock() ;
                    {
                        m_console.writeLine(dateTime, value) ;
                    }
                    m_mutex.unlock() ;
                }
            }

            /**
             * Write a message on the Console.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
            template<class T, class ... Args>
            void printLine(const Gravity& level, const T& value, const Args& ... args) {
                if (level <= m_minLevel) {
                    std::string dateTime = formatCurrentDateTime() ;

                    m_mutex.lock() ;
                    {
                        m_console.write(dateTime) ;
                        m_console.writeLine(value, args...) ;
                    }
                    m_mutex.unlock() ;
                }
            }
    } ;

    void garbage(LogSystem* sys) {
        if (sys != nullptr) {
            delete sys ;
        }
    }
}

#endif
