# Themidie

x64dbg plugin to bypass Themida 3.x Anti-Debugger / VM / Monitoring programs checks (64bits only)

  - [x64dbg](https://github.com/x64dbg/x64dbg)
  - [DLL injection](https://en.wikipedia.org/wiki/DLL_injection) ([LoadLibrary](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya))
  - Hooks ([MinHook](https://github.com/TsudaKageyu/minhook))


### Usage

- Download the [latest version](https://github.com/VenTaz/Themidie/releases) of Themidie and extract Themidie.dll and Themidie.dp64 to x64dbg's plugins folder 
- Download the [latest version](https://github.com/VenTaz/Themidie/releases) of ScyllaHide and extract HookLibraryx64.dll and ScyllaHideX64DBGPlugin.dp64 to x64dbg's plugins folder 
![Plugins Folder](https://raw.githubusercontent.com/VenTaz/Themidie/main/Images/plugins.png?token=AJWI4MHVFXWD5OG4MNYRLNS7X4RZA)

- Start x64dbg, click on the plugins tab, go to ScyllaHide -> Options
![ScyllaHide Options](https://raw.githubusercontent.com/VenTaz/Themidie/main/Images/scylla_options.png?token=AJWI4MD4UKTDLAZJQOUBE5K7X4SP2)

- Disable everything, enable "Kill Anti-Attach" only and click on the "OK" button
![ScyllaHide Kill Anti Attach](https://raw.githubusercontent.com/VenTaz/Themidie/main/Images/scylla_kill_anti_attach.png?token=AJWI4MEOU2LX4BEBLDSPXG27X4SWO)

- Go back to the plugins tab, go to Themidie -> Start and select and open the executable that you want to debug
![Themidie Start](https://raw.githubusercontent.com/VenTaz/Themidie/main/Images/themidie_start.png?token=AJWI4ME6N7PJEVPZXLK4HH27X4TBQ)

- When this MessageBox will apear, you will be able to attach x64dbg to the target process and debug it. 
![Themidie MessageBox](https://raw.githubusercontent.com/VenTaz/Themidie/main/Images/themidie_messagebox.png?token=AJWI4MHYJ26TASGIJ6NSJB27X4UJ2)


### Hooks

Themidie hooks the following functions:

| Module | Function name
| - | - 
| kernel32.dll | [GetModuleHandleA](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlea)
| user32.dll | [FindWindowA](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa)
| Advapi32.dll | [RegOpenKeyA](https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeya) 
| Advapi32.dll | [RegQueryValueExA](https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regqueryvalueexa)
| ntdll.dll | [NtSetInformationThread](https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntsetinformationthread)
| ntdll.dll | [NtQueryVirtualMemory](https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntqueryvirtualmemory) 


### Limitations
Themidie only works for x64 executables, tested on various Themida 3.x+ versions, Windows 10 2004, latest x64dbg and ScyllaHide versions.


#### Contact
Discord: VenTaz#8766
Email: support@hactify.ru
