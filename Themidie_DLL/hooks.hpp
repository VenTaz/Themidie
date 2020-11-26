#pragma once
#include "ntdll.h"

typedef HINSTANCE__ *(*GMHA)(const char*);
GMHA og_gmha = 0;

typedef HWND__ *(*FWA)(const char*, const char*);
FWA og_fwa = 0;

typedef long (*ROKA)(HKEY__*, const char*, HKEY__**);
ROKA og_roka = 0;

typedef long (*RQVEA)(HKEY__*, const char*, unsigned long*, unsigned long*, unsigned char*, unsigned long*);
RQVEA og_rqvea = 0;

typedef long (*NSIT)(HANDLE, _THREADINFOCLASS, void*, unsigned long);
NSIT og_nsit = 0;

typedef long (*NQVM)(HANDLE, void*, _MEMORY_INFORMATION_CLASS, void*, unsigned long long, unsigned long long*);
NQVM og_nqvm = 0;

const char *bad_modules[3] = {
	"dateinj01.dll",
	"cmdvrt32.dll",
	"SbieDll.dll"
};

const char *bad_windows[7] = {
	"File Monitor - Sysinternals: www.sysinternals.com",
	"Process Monitor - Sysinternals: www.sysinternals.com",
	"Registry Monitor - Sysinternals: www.sysinternals.com",
	"Regmon",
	"Filemon",
	"18467-41",
	"PROCMON_WINDOW_CLASS"
};

const char *good_keys[3] = {
	"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
	"SYSTEM\\ControlSet001\\Control\\Class\\{",
	"Hardware\\description\\System"
};

const char *bad_key = "HARDWARE\\ACPI\\DSDT\\VBOX__";

const char *good_values[4] = {
	"EnableLUA",
	"DriverDesc",
	"SystemBiosVersion",
	"VideoBiosVersion"
};

unsigned long
get_process_id_by_thread_handle(void *thread)
{
	_THREAD_BASIC_INFORMATION thread_basic_information;

	if (NT_SUCCESS(NtQueryInformationThread(thread, ThreadBasicInformation, &thread_basic_information, sizeof(_THREAD_BASIC_INFORMATION), 0)))
		return HandleToULong(thread_basic_information.ClientId.UniqueProcess);

	return 0;
}

HINSTANCE__ *
gmha_hook(const char *module_name)
{
	for (int i = 0; i < _countof(bad_modules); i++)
		if (strstr(module_name, bad_modules[i])) return 0;

	return og_gmha(module_name);
}

HWND__ * 
fwa_hook(const char *class_name, const char *window_name)
{
	if (class_name == 0 || window_name == 0) return og_fwa(class_name, window_name);

	for (int i = 0; i < _countof(bad_windows); i++)
		if (strstr(class_name, bad_windows[i]) || strstr(window_name, bad_windows[i])) return 0;

	return og_fwa(class_name, window_name);
}

long
roka_hook(HKEY__ *key, const char* sub_key, HKEY__ **result)
{

	for (int i = 0; i < _countof(good_keys); i++)
		if (strstr(sub_key, good_keys[i])) return 0L;

	if (strstr(sub_key, bad_key)) return 1L;

	return og_roka(key, sub_key, result);
}

long
rqvea_hook(HKEY__ *key, const char *value_name, unsigned long *reserved, unsigned long *type, unsigned char *lp_data, unsigned long *lpcb_data)
{
	for (int i = 0; i < _countof(good_values); i++)
		if (strstr(value_name, good_values[i])) return 0L;

	return og_rqvea(key, value_name, reserved, type, lp_data, lpcb_data);
}

long
nsit_hook(HANDLE thread_handle, _THREADINFOCLASS thread_information_class, void *thread_information, unsigned long thread_information_length)
{
	if (thread_information_class == ThreadHideFromDebugger && thread_information_length == 0)
		if (thread_handle == NtCurrentThread || HandleToULong(NtCurrentTeb()->ClientId.UniqueProcess) == get_process_id_by_thread_handle(thread_handle))
			return 0L;

	return og_nsit(thread_handle, thread_information_class, thread_information, thread_information_length);
}

long
nqvm_hook(HANDLE process_handle, void *base_address, _MEMORY_INFORMATION_CLASS memory_information_class, void *memory_information, unsigned long long memory_information_length, unsigned long long *return_length)
{
	static int is_loaded = 0;
	static int nqvm_count = 0;

	if (process_handle == NtCurrentProcess && !is_loaded)
	{
		if (memory_information_class == MemoryBasicInformation && nqvm_count == 0 || memory_information_class == MemoryRegionInformation && nqvm_count == 1)
			nqvm_count++;
		else if (memory_information_class == MemoryMappedFilenameInformation && nqvm_count == 2)
		{
			MH_DisableHook(&GetModuleHandleA);
			is_loaded = 1;
			MessageBoxA(0, "The executable is now loaded in the memory. You can attach x64dbg to the target process.", "Themidie", 64L);
		}
	}

	return og_nqvm(process_handle, base_address, memory_information_class, memory_information, memory_information_length, return_length);
}
