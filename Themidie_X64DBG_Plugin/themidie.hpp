#pragma once

#include "plugin.hpp"
#include "resource.h"

#define PLUGIN_NAME "Themidie"
#define PLUGIN_VERSION 1

#define error(message) MessageBoxA(0, message, "Themidie", MB_ICONEXCLAMATION);

void plugin_setup(PLUG_SETUPSTRUCT *setup_struct);