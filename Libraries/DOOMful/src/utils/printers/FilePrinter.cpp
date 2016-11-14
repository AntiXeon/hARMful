/**
 * FilePrinter.cpp
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *
 * @Author:      Denis CARLUS
 * @Created on:  11-Nov-2016
 * @Last change: 14-Nov-2016
 */

#include <utils/Translation.hpp>
#include <utils/printers/FilePrinter.hpp>

namespace Doom {
    FilePrinter::FilePrinter(const std::string& filepath)
        throw(std::ios_base::failure) : FilePrinter(filepath, false) {}

    FilePrinter::FilePrinter(
        const std::string& filepath,
        const bool& append
    ) throw(std::ios_base::failure) {
        std::ios_base::openmode mode = getAccessMode(append) ;
        m_output.open(filepath, mode) ;
        if (!m_output.is_open()) {
            std::string errorMsg = Translation::Get(Texts::File_NotOpened) + filepath ;
            throw std::ios_base::failure(errorMsg) ;
        }
    }

    FilePrinter::~FilePrinter() {
        if (m_output.is_open()) {
            m_output.close() ;
        }
    }

    std::ios_base::openmode FilePrinter::getAccessMode(const bool& append) {
        if (append) {
            return std::ios_base::out | std::ios_base::app ;
        }
        else {
            return std::ios_base::out ;
        }
    }
}
