#ifndef TEZZYBIRD_MAIN_HPP_
#define TEZZYBIRD_MAIN_HPP_

#ifdef __APPLE__
	#include "MacOS/MacHelper.hpp"
	MacHelper __macHelper;
#endif // __APPLE__

#ifdef __linux__
	#include "Linux/LinuxHelper.hpp"
	LinuxHelper __linuxHelper;
#endif // __linux__

#ifdef _WIN32
	#include "Win32/WindowsHelper.hpp"
	WindowsHelper __windowsHelper;
#endif // _WIN32

//

#endif // TEZZYBIRD_MAIN_HPP_

