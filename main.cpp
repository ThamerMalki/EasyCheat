#include"Memory.h"
#include"OffsetsList.h"
#include"Colors.h"
#include<iostream>

class NamePadding {
public:
	char preNamePadding[549];
	char maxCharactersInName[16];
	char postNamePadding[3609];
};


int main()
{
	Colors colors;
	OffsetsList offsets;
	Memory memory("ac_client.exe");

	const auto ModuleBaseAddress = memory.GetModuleAddress("ac_client.exe");

	const auto localPlayerAddress = memory.Read<std::uintptr_t>(ModuleBaseAddress + offsets.localPlayer);

	const auto healthAddress = localPlayerAddress + offsets.health;
	const auto mtpAmmoAddress = localPlayerAddress + offsets.mtpAmmo;
	const auto armorAddress = localPlayerAddress + offsets.armor;
	const auto nameAddress = localPlayerAddress + offsets.nameOffsetWithinPadding;

	std::string name = memory.Read<NamePadding>(nameAddress).preNamePadding;

	std::cout << std::endl;
	std::cout << colors.green <<
		"  ______                 _____ _                _\n"
		" |  ____|               / ____| |              | |\n"
		" | |__   __ _ ___ _   _| |    | |__   ___  __ _| |_ \n"
		" |  __| / _` / __| | | | |    | '_ \\ / _ \\/ _` | __|\n"
		" | |___| (_| \\__ \\ |_| | |____| | | |  __/ (_| | |_ \n"
		" |______\\__,_|___/\\__, |\\_____|_| |_|\\___|\\__,_|\\__|\n"
		"                   __/ |                            \n"
		"                  |___/                             \n";


	std::cout << std::endl << colors.yellow << "=-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-=\n\n"<< colors.reset;
	std::cout << "Welcome to EasyCheat, " <<colors.magenta<<name<<colors.reset<<"\n\n";
	std::cout <<colors.red<< " [F1] Health Hack\n [F2] Ammo Hack\n [F3] Armor Hack\n"<< colors.reset;

	while (true)
	{
		if (GetAsyncKeyState(VK_F1) & 0x8000)
			memory.Write(healthAddress, 9999);
		else if (GetAsyncKeyState(VK_F2) & 0x8000)
			memory.Write(mtpAmmoAddress, 1111);
		else if (GetAsyncKeyState(VK_F3) & 0x8000)
			memory.Write(armorAddress, 9999);
	}

}