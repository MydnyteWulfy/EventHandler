#pragma once

//Copyright (c) Brendan Joffs, 2023 | File: DllSupport.h //

#ifndef SYSTEM_DLL_SUPPORT //check to see if another module has already enabled dll support
#define SYSTEM_DLL_SUPPORT //define dll support

	#ifdef SYSTEM_BUILD_DLL 

		#ifdef SYSTEM_WINDOWS
			#define __Reference __declspec(dllexport) //if we are building a dll, export symbols (windows)
		#else
			#define __Reference //if we are building a dll, export symbols (linux)
		#endif

	#else

		#ifdef SYSTEM_WINDOWS
			#define __Reference __declspec(dllimport) //if we are using a dll, import symbols (windows)
		#else
			#define __Reference
		#endif

	#endif	

#endif