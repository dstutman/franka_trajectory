#pragma once

#include "GxIAPI.h"

namespace Camera {
    typedef enum {
        CAMERA_STATUS_SUCCESS,
        CAMERA_STATUS_FAILURE,
    } CAMERA_STATUS;

    class Camera {
        protected:
            GX_DEV_HANDLE _device;
            int64_t _payload_size;


        public:
            Camera();
            ~Camera();
            CAMERA_STATUS capture_to_file(const char *file_name);
    };
    void camera();
}
