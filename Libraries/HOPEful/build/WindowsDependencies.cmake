if (WIN32)
set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY VS_PACKAGE_REFERENCES
    "unofficial-flayan-glew_2.1.*;glfw_3.3.*;assimp_native_4.0.*"
)
endif()
