if (UNIX)
    find_package(GLEW REQUIRED)
    if (GLEW_FOUND)
        include_directories(${GLEW_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
    endif()

    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    if (GLFW_FOUND)
        include_directories(${GLFW_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
    endif()

    find_package(assimp REQUIRED)
    if (assimp_FOUND)
        # Because ASSIMP find_package seems to be broken...
        set(ASSIMP_LIBRARY "assimp")
        target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY})
    endif()
    
    
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/")
    
    find_package(LibJpegTurbo REQUIRED)
    if (JPEGTURBO_FOUND)
        include_directories(${JPEGTURBO_INCLUDE_DIR})
        target_link_libraries(${PROJECT_NAME} ${JPEGTURBO_LIBRARIES})
        target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})
    endif()
endif()
