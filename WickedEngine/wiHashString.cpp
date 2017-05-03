#include "wiHashString.h"

using namespace std;

hash<std::string> hasher;

wiHashString::wiHashString(const char* value):wiHashString(string(value))
{
}
wiHashString::wiHashString(const std::string& value)
{
	str = value;
	hash = hasher(str);
}

bool operator==(const wiHashString& a, const wiHashString& b)
{
	return a.GetHash() == b.GetHash();
}

wiHashString::~wiHashString()
{
}
