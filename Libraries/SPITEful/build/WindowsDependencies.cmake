if (WIN32)
set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY VS_PACKAGE_REFERENCES
    "libpng_1.6.*;libjpeg-turbo-native-win_2.0.*"
)
endif()
