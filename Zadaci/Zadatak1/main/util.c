#include "util.h"

#include <Windows.h>

int FixupCurrentDirectory()
{
	// 
	// Get the path of the main module.
	// 

	char path[MAX_PATH] = { '\0' };
	if (!GetModuleFileNameA(NULL, path, MAX_PATH))
		return 0;
	
	// 
	// Remove the executable name from the path.
	// 

	char* lastSlash = strrchr(path, '\\');
	if (lastSlash == NULL)
		return 0;

	*lastSlash = '\0';

	return SetCurrentDirectoryA(path);
}