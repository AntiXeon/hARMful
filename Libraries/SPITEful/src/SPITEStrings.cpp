#include <SPITEStrings.hpp>

/**
 * Tag to be detected when using xgettext on this file.
 * @param  str The string to be detected by xgettext.
 * @return     The same string as input.
 */
#define i18n(str) str

namespace Spite {
    namespace FileMsg {
        namespace Error {
            const std::string UnableToOpen = i18n("Unable to open ") ;
            const std::string OnlyRegularFiles = i18n("Only open regular files are allowed.") ;
            const std::string UnsupportedPlatform = i18n("Unsupported platform.") ;
            const std::string MkdirFailed = i18n("MKDIR unable to create ") ;

            const std::string CannotSaveFile = i18n("Cannot save file at ") ;
            const std::string NoOutputMode = i18n(": not opened in output mode.") ;
            const std::string CannotReadFile = i18n("Cannot read file at ") ;
            const std::string NoInputMode = i18n(": not opened in input mode.") ;

            const std::string InsufficientMemory = i18n("Unable to open %s because of memory lack.") ;
            const std::string FailureOnOpening = i18n("An unexpected error occured while opening file ") ;
            const std::string UnknownAccessMode = i18n("Unknown file access mode.") ;
        } ;
    } ;

    namespace JPEGMsg {
        namespace Error {
            const std::string DecompressiongInitFailed = i18n("Error on initialization of JPEG decompression for ") ;
            const std::string FailureWhileDecompressing = i18n("An error occurred while decompressing ") ;
        } ;
    } ;

    namespace PNGMsg {
        namespace Error {
            const std::string NotPNGFile = i18n("The provided file is not a PNG image: %s.") ;
            const std::string InitializationStructureFailed = i18n("Unable to initialize PNG structure for ") ;
            const std::string InitializationInfosFailed = i18n("Unable to initialize PNG infos for ") ;
        } ;
    } ;

    namespace ColorFormatMsg {
        namespace Error {
            const std::string UnknownFormat = i18n("Unknown color format.") ;
        }
    } ;

    namespace RawImageMsg {
        namespace Error {
            const std::string UndefinedColorFormatWhenSettingSize = i18n("Color format must be defined before setting the image size.") ;
        }
    }

    namespace WriterMsg {
        namespace Error {
            const std::string EndOfFile = i18n("End of file is reached while writing.") ;
        }
    }

    namespace ReaderMsg {
        namespace Error {
            const std::string EndOfFile = i18n("End of file is reached while reading.") ;
        }
    }
} ;
