#pragma once

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"

#pragma comment(lib, "pluginsdk/x64dbg.lib")

#define PLUG_EXPORT extern "C" __declspec(dllexport)

extern int pluginHandle, h_menu;
extern HWND__ *hwnd_dlg;
extern HINSTANCE__ *instance;

enum ThemidieMenus : int {
    MENU_START,
    MENU_ABOUT
};