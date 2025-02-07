#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include "../render_engine_ui.h"
#include "../telemetry_info.h"
#include "../settings_info.h"
#include "usb_camera_plugin.h"

#define CAMERA_DEVICE "/dev/video0"
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 512
#define FRAME_FORMAT V4L2_PIX_FMT_YUYV

PLUGIN_VAR RenderEngineUI* g_pEngine = NULL;
PLUGIN_VAR const char* g_szPluginName = "USB Camera Plugin";
PLUGIN_VAR const char* g_szUID = "USB-CAM-PLUGIN-001";
static int camera_fd = -1;

#ifdef __cplusplus
extern "C" {
#endif

void init(void* pEngine) {
    g_pEngine = (RenderEngineUI*)pEngine;
    camera_fd = open(CAMERA_DEVICE, O_RDWR);
    if (camera_fd < 0) {
        perror("Failed to open camera");
        return;
    }
    
    struct v4l2_format format;
    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = FRAME_WIDTH;
    format.fmt.pix.height = FRAME_HEIGHT;
    format.fmt.pix.pixelformat = FRAME_FORMAT;
    format.fmt.pix.field = V4L2_FIELD_NONE;
    
    if (ioctl(camera_fd, VIDIOC_S_FMT, &format) < 0) {
        perror("Failed to set camera format");
        close(camera_fd);
        camera_fd = -1;
    }
}

char* getName() {
    return (char*)g_szPluginName;
}

char* getUID() {
    return (char*)g_szUID;
}

void render(vehicle_and_telemetry_info_t* pTelemetryInfo, plugin_settings_info_t2* pCurrentSettings, float xPos, float yPos, float fWidth, float fHeight) {
    if (NULL == g_pEngine || camera_fd < 0) return;

    // Capture frame
    char buffer[FRAME_WIDTH * FRAME_HEIGHT * 2];
    read(camera_fd, buffer, sizeof(buffer));
    
    // Render a simple overlay to indicate camera plugin is active
    g_pEngine->setColors(g_pEngine->getColorOSDInstruments());
    g_pEngine->drawText(xPos + 10, yPos + 10, g_pEngine->getFontIdRegular(), "USB Camera Active");
}

void cleanup() {
    if (camera_fd >= 0) {
        close(camera_fd);
        camera_fd = -1;
    }
}

#ifdef __cplusplus
}
#endif
