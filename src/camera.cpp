#include "camera.hpp"

#include <cassert>

void camera() {
    assert(GXInitLib() == GX_STATUS_SUCCESS);

    uint32_t num_devices = 0;
    GXUpdateDeviceList(&num_devices, 1000);

    GX_OPEN_PARAM open_params;
    open_params.accessMode = GX_ACCESS_EXCLUSIVE;
    open_params.openMode = GX_OPEN_INDEX;
    open_params.pszContent = (char*)"1";

    GX_DEV_HANDLE device_handle;

    assert(GXOpenDevice(&open_params, &device_handle) == GX_STATUS_SUCCESS);
}
