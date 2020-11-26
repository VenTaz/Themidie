#include "themidie.hpp"

int plugin_handle = 0, h_menu = 0;

HWND__ *hwnd_dlg = 0;
HINSTANCE__ *instance = 0;
ICONDATA main_icon = { 0 };


PLUG_EXPORT bool 
pluginit(PLUG_INITSTRUCT *init_struct)
{
    init_struct->pluginVersion = PLUGIN_VERSION;
    init_struct->sdkVersion = PLUG_SDKVERSION;
    strncpy_s(init_struct->pluginName, PLUGIN_NAME, _TRUNCATE);
    plugin_handle = init_struct->pluginHandle;
    return 1;
}


PLUG_EXPORT void 
plugsetup(PLUG_SETUPSTRUCT *setup_struct)
{
    hwnd_dlg = setup_struct->hwndDlg;
    h_menu = setup_struct->hMenu;

    HRSRC__ *res_main_icon = FindResourceW(instance, MAKEINTRESOURCEW(IDB_PNG1), L"PNG");
    void *loaded_main_icon = LoadResource(instance, res_main_icon);
    main_icon.data = LockResource(loaded_main_icon);
    main_icon.size = SizeofResource(instance, res_main_icon);

    _plugin_menuseticon(h_menu, (const ICONDATA*)&main_icon);

    plugin_setup(setup_struct);
}


PLUG_EXPORT bool 
plugstop() { return 1; }


PLUG_EXPORT BOOL APIENTRY 
DllMain(HINSTANCE__ *module, unsigned long reason, void *reserved)
{
    instance = module;
    return 1;
}