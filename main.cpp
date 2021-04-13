#define NOMINMAX
#include <Windows.h>

#include "valve_sdk/sdk.hpp"
#include "helpers/utils.hpp"
#include "helpers/config_manager.hpp"
#include "helpers/input.hpp"
#ifndef _DEBUG
#endif // !_DEBUG

#include "features/skinchanger/skins.hpp"

#include "hooks.hpp"
#include "menu/menu.hpp"
#include "options.hpp"

#include <TlHelp32.h>

static unsigned char global_opCodes[] = { 0x8b, 0xff, 0x55, 0x8b, 0xec };
static unsigned char readfile_opCodes[] = { 0xff, 0x25, 0x30, 0x04, 0x91 };

auto CheckHook = [](PDWORD pdwAddress, unsigned char* opCodes)
{
	for (int i = 0; i < 5; i++)
	{
		if (((unsigned char*)pdwAddress)[i] != opCodes[i]) *((unsigned int*)0) = 0xDEAD;//MessageBox(0, "Hook detected", 0, 0);
	}
};


DWORD WINAPI OnDllAttach(PVOID base)
{

	while (!GetModuleHandleA(("serverbrowser.dll")))
		Sleep(1000);
  	

    try {
		//Utils::AttachConsole();

        Utils::ConsolePrint(("Initializing...\n"));

        Interfaces::Initialize();
        Interfaces::Dump();

        NetvarSys::Get().Initialize();
        InputSys::Get().Initialize();
		CConfig::Get().Initialize();
		CSkinChanger::Get().Initialize();

        Hooks::Initialize();

        Utils::ConsolePrint(("Finished.\n"));

        while (!Globals::Unload)
            Sleep(1000);

		Hooks::Unload();

		FreeLibraryAndExitThread(HMODULE(base), 0);

    } catch(const std::exception& ex) {
        Utils::ConsolePrint(("An error occured during initialization:\n"));
        Utils::ConsolePrint(("%s\n"), ex.what());
        Utils::ConsolePrint(("Press any key to exit.\n"));
        Utils::ConsoleReadKey();
        Utils::DetachConsole();

		FreeLibraryAndExitThread(HMODULE(base), 0);
	}
}

BOOL WINAPI OnDllDetach()
{
    Utils::DetachConsole();

    Hooks::Unload();

    return TRUE;
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDll, _In_ DWORD fdwReason, _In_opt_ LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hinstDll);
		CreateThread(nullptr, 0, OnDllAttach, hinstDll, 0, nullptr);

		return TRUE;
	}
}
