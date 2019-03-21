#include "Sound.h"
#include <string>

Sound::Sound()
{
}

Sound::~Sound()
{
}

//Loads a sound file
bool const Sound::LoadSound(const std::string &filename)
{
	if (!HAPI.LoadSound(filename))
	{
		HAPI.UserMessage("Sound file not found!", "Error");
		return false;
	}

	return true;
}

//Plays sound file
void const Sound::PlaySound(const std::string &filename)
{
	HAPI.PlaySound(filename);
}
