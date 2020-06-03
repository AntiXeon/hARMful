#ifndef __SPITE__STRINGS__
#define __SPITE__STRINGS__

#include <string>

namespace Spite {
    namespace FileMsg {
        namespace Error {
            extern const std::string UnableToOpen ;
            extern const std::string OnlyRegularFiles ;
            extern const std::string UnsupportedPlatform ;
            extern const std::string MkdirFailed ;

            extern const std::string CannotSaveFile ;
            extern const std::string NoOutputMode ;
            extern const std::string CannotReadFile ;
            extern const std::string NoInputMode ;

            extern const std::string InsufficientMemory ;
            extern const std::string FailureOnOpening ;
            extern const std::string UnknownAccessMode ;

            extern const std::string BadAccessMode ;
        } ;
    } ;

    namespace JPEGMsg {
        namespace Error {
            extern const std::string DecompressiongInitFailed ;
            extern const std::string FailureWhileDecompressing ;
        } ;
    } ;

    namespace PNGMsg {
        namespace Error {
            extern const std::string NotPNGFile ;
            extern const std::string BadPNGHeaderSize ;
            extern const std::string InitializationStructureFailed ;
            extern const std::string InitializationInfosFailed ;
        } ;
    } ;

    namespace ColorFormatMsg {
        namespace Error {
            extern const std::string UnknownFormat ;
        }
    } ;

    namespace RawImageMsg {
        namespace Error {
            extern const std::string UndefinedColorFormatWhenSettingSize ;
        }
    }

    namespace WriterMsg {
        namespace Error {
            extern const std::string EndOfFile ;
        }

        namespace Info {
            extern const std::string HDRExtensionNotMatching ;
            extern const std::string ImageWrittenOK ;
        }
    }

    namespace ReaderMsg {
        namespace Error {
            extern const std::string EndOfFile ;
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
