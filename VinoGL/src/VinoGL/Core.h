#pragma once

#ifdef VN_PLATFORM_WINDOWS
	#ifdef VN_BUILD_DLL
		#define VINO_API __declspec(dllexport)
	#else
		#define VINO_API __declspec(dllimport)
	#endif
#else
	#error Only Windows is supported at the moment
#endif