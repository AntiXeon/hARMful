#include <files/images/ImageFile.h>
#include <SPITEStrings.h>
#include <debug/Test.h>
#include <string.h>
#include <stdio.h>

namespace Spite {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ImageFile::ImageFile(const std::string& path) : File(path),
                                                    m_file(NULL),
                                                    m_dataPosition(0) {}

    ImageFile::~ImageFile() {
        m_dataPosition = 0 ;

        if (m_file != NULL) {
            close() ;
        }
    }

                                                             /*** UTILITIES ***/
    bool ImageFile::load(IFileData* output) throw(Doom::IOException) {
        open(File::Open_ReadOnly) ;

        if (getDescriptor() == NULL) {
            ThrowException(
                           Doom::IOException,
                           FileMsg::Error::UnableToOpen + getPath().getAbsolutePath()
                          ) ;
        }

        return parse(output) ;
    }

    bool ImageFile::save(
                        IFileData* /*filedata*/,
                        const std::string& /*path*/
                       ) throw(Doom::IOException) {
        // @TODO: Implementation!
        return false ;
    }


    void ImageFile::open(OpenMode mode) {
        const char* filepath = m_path.getAbsolutePath().c_str() ;

        switch(mode) {
            case File::Open_ReadOnly:
                m_file = fopen(filepath, "rb") ;
                return ;

            case File::Open_Append:
                m_file = fopen(filepath, "ab") ;
                return ;

            case File::Open_WriteOnly:
                m_file = fopen(filepath, "wb") ;
                return ;

            case File::Open_ReadWrite:
                m_file = fopen(filepath, "rb+") ;
                return ;

            case File::Open_ReadAppend:
                m_file = fopen(filepath, "ab+") ;
                return ;

            default:
                m_file = NULL ;
                return ;
        }
    }

    void ImageFile::close() {
        fclose(m_file) ;
        m_file = NULL ;
    }


    FILE* ImageFile::getDescriptor() const {
        return m_file ;
    }

} ;
