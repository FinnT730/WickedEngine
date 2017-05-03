#ifndef WICKEDENGINE_VERSION_DEFINED
#define WICKEDENGINE_VERSION_DEFINED

#include "CommonInclude.h"

#include <string>

namespace wiVersion
{
	long GetVersion();
	// major features
	int GetMajor();
	// minor features, major bug fixes
	int GetMinor();
	// minor bug fixes, alterations
	int GetRevision();
	std::string GetVersionString();
}

#endif // WICKEDENGINE_VERSION_DEFINED
