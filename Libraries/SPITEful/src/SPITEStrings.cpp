#include <SPITEStrings.h>


namespace Spite {

    namespace FileMsg {
        namespace Error {
            const char* UnableToOpen =                                          "Unable to open " ;
            const char* OnlyRegularFiles =                                      "Only open regular files are allowed." ;
            const char* UnsupportedPlatform =                                   "Unsupported platform." ;
            const char* MkdirFailed =                                           "MKDIR unable to create " ;

            const char* CannotSaveFile =                                 		"Cannot save file at " ;
            const char* NoOutputMode =                                   		": not opened in output mode." ;
            const char* CannotReadFile =                                 		"Cannot read file at " ;
            const char* NoInputMode =                                    		": not opened in input mode." ;

            const char* InsufficientMemory =                             		"Unable to open %s because of memory lack." ;
            const char* FailureOnOpening =                               		"An unexpected error occured while opening file " ;
            const char* UnknownAccessMode =                              		"Unknown file access mode." ;
        } ;
    } ;

    namespace JPEGMsg {
        namespace Error {
            const char* DecompressiongInitFailed =                       		"Error on initialization of JPEG decompression for " ;
            const char* FailureWhileDecompressing =                      		"An error occurred while decompressing " ;
        } ;
    } ;

    namespace PNGMsg {
        namespace Error {
            const char* NotPNGFile =                                     		"The provided file is not a PNG image: %s." ;
            const char* InitializationStructureFailed =                  		"Unable to initialize PNG structure for " ;
            const char* InitializationInfosFailed =                      		"Unable to initialize PNG infos for " ;
        } ;
    } ;

    namespace ColorFormatMsg {
        namespace Error {
            const char* UnknownFormat =                                  		"Unknown color format." ;
        }
    } ;

    namespace RawImageMsg {
        namespace Error {
            const char* UndefinedColorFormatWhenSettingSize =            		"Color format must be defined before setting the image size." ;
        }
    }

    namespace WriterMsg {
        namespace Error {
            const char* EndOfFile =                                      		"End of file is reached while writing." ;
        }
    }

    namespace ReaderMsg {
        namespace Error {
            const char* EndOfFile =                                      		"End of file is reached while reading." ;
        }
    }

} ;
