if (WIN32)
    set(DEPENDENCIES_DIR ${CMAKE_HOME_DIRECTORY}/dependencies)

    # ===== GLEW =====
    set(GLEW_VERSION 2.1.0)
    set(GLEW_HOME_DIRECTORY ${DEPENDENCIES_DIR}/glew)

    include(ExternalProject)
    ExternalProject_Add(
         glewBuild
         #-- Directories
         SOURCE_DIR ${GLEW_HOME_DIRECTORY}
         BINARY_DIR ${GLEW_HOME_DIRECTORY}
         #-- Configure
         CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM} -DBUILD_UTILS=OFF -DGLEW_REGAL=OFF -DGLEW_OSMESA=OFF ${GLEW_HOME_DIRECTORY}/build/cmake
         #-- Download
         URL https://github.com/nigels-com/glew/releases/download/glew-${GLEW_VERSION}/glew-${GLEW_VERSION}.zip
         URL_HASH SHA512=33c5454f9b94a81172c8e83d88f292b9e80d2e58ef162c63e7e6e429362bed681a1457277143f50e652a180898e37378ca71aec1dd1782c6f638f9acd1ec0bcb
         #-- Install
         UPDATE_DISCONNECTED
    )

    set(GLEW_LIB_PATH ${GLEW_HOME_DIRECTORY}/lib/$(Configuration))
    set(GLEW_LIB_PATH_OPTIMIZED ${GLEW_LIB_PATH}/glew32.lib)
    set(GLEW_LIB_PATH_DEBUG ${GLEW_LIB_PATH}/glew32d.lib)
    add_library(glew SHARED IMPORTED)
    set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${GLEW_LIB_PATH_OPTIMIZED})

    include_directories(${GLEW_HOME_DIRECTORY}/include)
    target_link_libraries(${PROJECT_NAME} debug ${GLEW_LIB_PATH_DEBUG} optimized ${GLEW_LIB_PATH_OPTIMIZED})
    add_dependencies(${PROJECT_NAME} glewBuild)


    # ===== GLFW =====
    set(GLFW_HOME_DIRECTORY ${DEPENDENCIES_DIR}/glfw)

    include(ExternalProject)
    ExternalProject_Add(
         glfwBuild
         #-- Directories
         SOURCE_DIR ${GLFW_HOME_DIRECTORY}
         BINARY_DIR ${GLFW_HOME_DIRECTORY}
         #-- Configure
         CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM} -DBUILD_SHARED_LIBS=ON -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF ${GLFW_HOME_DIRECTORY}
         #-- Install
         UPDATE_DISCONNECTED
    )

    set(GLFW_LIB_PATH ${GLFW_HOME_DIRECTORY}/src/$(Configuration)/glfw3dll.lib)
    add_library(glfw SHARED IMPORTED)
    set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${GLFW_LIB_PATH})

    include_directories(${GLFW_HOME_DIRECTORY}/include)
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIB_PATH})
    add_dependencies(${PROJECT_NAME} glfwBuild)


    # ===== ASSIMP =====
    set(ASSIMP_HOME_DIRECTORY ${DEPENDENCIES_DIR}/assimp)

    include(ExternalProject)
    ExternalProject_Add(
         assimpBuild
         #-- Directories
         SOURCE_DIR ${ASSIMP_HOME_DIRECTORY}
         BINARY_DIR ${ASSIMP_HOME_DIRECTORY}
         #-- Configure
         CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM} -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF ${ASSIMP_HOME_DIRECTORY}
         #-- Install
         UPDATE_DISCONNECTED
    )

    if(MSVC12)
      SET(ASSIMP_MSVC_VERSION "vc120")
    elseif(MSVC14)
      SET(ASSIMP_MSVC_VERSION "vc140")
    ENDIF(MSVC12)

    set(ASSIMP_LIB_PATH ${ASSIMP_HOME_DIRECTORY}/lib/$(Configuration)/assimp-${ASSIMP_MSVC_VERSION}-mt.lib)
    add_library(assimp SHARED IMPORTED)
    set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${ASSIMP_LIB_PATH})
    set_target_properties(assimp PROPERTIES OUTPUT_NAME assimp)

    include_directories(${ASSIMP_HOME_DIRECTORY}/include)
    target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIB_PATH})
    add_dependencies(${PROJECT_NAME} assimpBuild)
endif()
