#ifndef __SPITE__TEXT_STRINGS_INCLUDE__
#define __SPITE__TEXT_STRINGS_INCLUDE__


namespace Spite {

    namespace FileMsg {
        namespace Error {
            extern const char* UnableToOpen ;
            extern const char* OnlyRegularFiles ;
            extern const char* UnsupportedPlatform ;
            extern const char* MkdirFailed ;

            extern const char* CannotSaveFile ;
            extern const char* NoOutputMode ;
            extern const char* CannotReadFile ;
            extern const char* NoInputMode ;

            extern const char* InsufficientMemory ;
            extern const char* FailureOnOpening ;
            extern const char* UnknownAccessMode ;
        } ;
    } ;

    namespace JPEGMsg {
        namespace Error {
            extern const char* DecompressiongInitFailed ;
            extern const char* FailureWhileDecompressing ;
        } ;
    } ;

    namespace PNGMsg {
        namespace Error {
            extern const char* NotPNGFile ;
            extern const char* InitializationStructureFailed ;
            extern const char* InitializationInfosFailed ;
        } ;
    } ;

    namespace ColorFormatMsg {
        namespace Error {
            extern const char* UnknownFormat ;
        }
    } ;

    namespace RawImageMsg {
        namespace Error {
            extern const char* UndefinedColorFormatWhenSettingSize ;
        }
    }

    namespace WriterMsg {
        namespace Error {
            extern const char* EndOfFile ;
        }
    }

    namespace ReaderMsg {
        namespace Error {
            extern const char* EndOfFile ;
        }
    }

} ;


// Files

#define     STR_ERROR__FILE__MEMORY_LACK                                        "Unable to open %s because of memory lack."
#define     STR_ERROR__FILE__ERROR_ON_OPENING                                   "An unexpected error occured while opening file "
#define     STR_EROOR__FILE__UNKNOWN_ACCESS_MODE                                "Unknown file access mode."

// JPEG
#define     STR_ERROR__FILE__JPEG_DECOMPRESSION_INIT                            "Error on initialization of JPEG decompression for "
#define     STR_ERROR__FILE__JPEG_WHILE_DECOMPRESSING                           "An error occurred while decompressing "

// PNG
#define     STR_ERROR__FILE__PNG_NOT_A_PNG                                      "The provided file is not a PNG image: %s."
#define     STR_ERROR__FILE__PNG_INIT_STRUCT                                    "Unable to initialize PNG structure for "
#define     STR_ERROR__FILE__PNG_INIT_INFOS                                     "Unable to initialize PNG infos for "


// Color formats
#define     STR_ERROR__COLOR_FORMAT__UNKNOWN                                    "Unknown color format."

// Raw image
#define     STR_ERROR__RAW_IMAGE__DEFINE_COLOR_FORMAT_BEFORE_SIZE               "Color format must be defined before setting the image size."


// Writers
#define     STR_ERROR__WRITERS__EOF                                             "End of file is reached while writing."

// Readers
#define     STR_ERROR__READERS__EOF                                             "End of file is reached while reading."

#endif
