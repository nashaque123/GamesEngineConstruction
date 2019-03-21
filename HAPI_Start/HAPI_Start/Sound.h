#pragma once
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Sound
{
public:
	Sound();
	~Sound();

	bool const LoadSound(const std::string &filename);
	void const PlaySound(const std::string &filename);
};

