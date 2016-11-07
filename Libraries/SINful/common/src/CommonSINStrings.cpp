#include <CommonSINStrings.h>


namespace Sin {

    namespace CameraMsg {
        namespace Warning {
            const char* EntityNotFound =                                        "Unable to detach from IEntity %x, IEntity not found." ;
        }
    }

    namespace EntityMsg {
        namespace Error {
            const char* IndexOutOfBounds =                                      "Bad index value to access entities." ;
            const char* BadCategoryID =                                         "The provided EntityCategory is not allowed." ;
        }

        namespace Warning {
            const char* AlreadyNULLPointer =                                    "The IEntity #%i is already removed." ;
        }
    }

    namespace InterpolationMsg {
        namespace Error {
            const char* IndexOutOfBounds =                                      "Bad index value to access interpolations." ;
        }
    }

}
