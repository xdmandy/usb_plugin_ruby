#pragma once

#include "../render_engine_ui.h"
#include "../telemetry_info.h"
#include "../settings_info.h"

#ifdef __cplusplus
extern "C" {
#endif

void init(void* pEngine);
char* getName();
char* getUID();
void render(vehicle_and_telemetry_info_t* pTelemetryInfo, plugin_settings_info_t2* pCurrentSettings, float xPos, float yPos, float fWidth, float fHeight);
void cleanup();

#ifdef __cplusplus
}
#endif
