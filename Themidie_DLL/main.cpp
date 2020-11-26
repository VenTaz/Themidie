#include "MinHook.h"
#include "hooks.hpp"

#define error(message) MessageBoxA(0, message, "Themidie", 16L);

bool DllMain(HINSTANCE__ *module, unsigned long call_reason, void *reserved)
{
	if (call_reason == 1)
	{
		LdrDisableThreadCalloutsForDll(module);

		if (MH_Initialize() != 0) 
			error("Could not initialize hooks");

		if (MH_CreateHook(&GetModuleHandleA, &gmha_hook, (void**)&og_gmha) != 0)
			error("Could not hook GetModuleHandleA");

		if (MH_CreateHook(&FindWindowA, &fwa_hook, (void**)&og_fwa) != 0)
			error("Could not hook FindWindowA");

		if (MH_CreateHook(&RegOpenKeyA, &roka_hook, (void**)&og_roka) != 0) 
			error("Could not hook RegOpenKeyA");

		if (MH_CreateHook(&RegQueryValueExA, &rqvea_hook, (void**)&og_rqvea) != 0) 
			error("Could not hook RegQueryValueExA");

		if (MH_CreateHook(&NtSetInformationThread, &nsit_hook, (void**)&og_nsit) != 0) 
			error("Could not hook NtSetInformationThread");

		if (MH_CreateHook(&NtQueryVirtualMemory, &nqvm_hook, (void**)&og_nqvm) != 0) 
			error("Could not hook NtQueryVirtualMemory");

		if (MH_EnableHook(0) != 0) 
			error("Could not enable hooks");

	}

	return 1;
}