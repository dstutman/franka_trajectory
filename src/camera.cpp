#include "camera.hpp"
#include "DxImageProc.h"

#include <cassert>
#include <iostream>

void camera() {
    assert(GXInitLib() == GX_STATUS_SUCCESS);

    // Find an open the camera
    uint32_t num_devices = 0;
    GXUpdateDeviceList(&num_devices, 1000);

    GX_OPEN_PARAM open_params;
    open_params.accessMode = GX_ACCESS_EXCLUSIVE;
    open_params.openMode = GX_OPEN_INDEX;
    open_params.pszContent = (char *) "1";
    GX_DEV_HANDLE device_handle;
    assert(GXOpenDevice(&open_params, &device_handle) == GX_STATUS_SUCCESS);

    // Determine device properties
    int64_t color_filter = GX_COLOR_FILTER_NONE;
    int64_t payload_size = 0;
    assert(GXGetEnum(device_handle, GX_ENUM_PIXEL_COLOR_FILTER, &color_filter) == GX_STATUS_SUCCESS);
    assert(GXGetEnum(device_handle, GX_INT_PAYLOAD_SIZE, &payload_size) == GX_STATUS_SUCCESS);

    // Enable acquisition with soft-trigger
    assert(GXSetEnum(device_handle, GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS) == GX_STATUS_SUCCESS);
    assert(GXSetEnum(device_handle, GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_ON) == GX_STATUS_SUCCESS);

    // Configure transfers
    uint64_t num_buffers = 5;
    uint64_t transfer_size = 64 * 1024;
    uint64_t transfer_urb = 64;
    assert(GXSetAcqusitionBufferNumber(device_handle, num_buffers) == GX_STATUS_SUCCESS);
    assert(GXSetInt(device_handle, GX_DS_INT_STREAM_TRANSFER_SIZE, transfer_size) == GX_STATUS_SUCCESS);
    assert(GXSetInt(device_handle, GX_DS_INT_STREAM_TRANSFER_NUMBER_URB, transfer_urb) == GX_STATUS_SUCCESS);
    // Dequeue a frame buffer
    PGX_FRAME_BUFFER frame_buffer = NULL;
    while (true) {
        switch (GXDQBuf(device_handle, &frame_buffer, 1000)) {
            case GX_STATUS_TIMEOUT:
                continue;
            case GX_STATUS_SUCCESS:
                break;
            default:
                assert(false);
        }
    }
    assert(frame_buffer->nStatus == GX_FRAME_STATUS_SUCCESS);
    std::cout << "Acquired frame";

    // Convert the image format
    uint8_t *const rgb_buffer = new uint8_t[payload_size * 3];
    switch (frame_buffer->nPixelFormat) {
        case GX_PIXEL_FORMAT_BAYER_GR8:
        case GX_PIXEL_FORMAT_BAYER_RG8:
        case GX_PIXEL_FORMAT_BGR8:
        case GX_PIXEL_FORMAT_BAYER_BG8:
            assert(DxRaw8toRGB24(frame_buffer->pImgBuf, rgb_buffer, frame_buffer->nWidth, frame_buffer->nHeight,
                                 RAW2RGB_NEIGHBOUR, DX_PIXEL_COLOR_FILTER(color_filter), false) == DX_OK);
            break;
        default:
            // Unimplemented
            assert(false);
    }

    // When done, re-enqueue the buffer
    assert(GXQBuf(device_handle, frame_buffer) == GX_STATUS_SUCCESS);

    GXCloseDevice(device_handle);
}