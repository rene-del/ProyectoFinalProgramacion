#include "Audio.h"
#include "ResourceManager.h"

Audio* Audio::pInstance = nullptr;

extern ResourceManager* RESOURCE_MANAGER;

Audio::Audio()
{
	open();
	channels();
}

Audio::~Audio()
{
	close();
}

void Audio::open()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		std::cout << Mix_GetError();
	}
}

void Audio::channels()
{
	Mix_AllocateChannels(128);
}

void Audio::playAudio(int channel, int chunkID, int loops)
{
	if ((chunkID > -1) && (chunkID < RESOURCE_MANAGER->getAudiosvectorSize()))
	{
		if (Mix_PlayChannel(channel, RESOURCE_MANAGER->getAudioByID(chunkID), loops) == -1)
		{
			std::cout << Mix_GetError();
		}
	}
}

void Audio::pauseAudio(int channel)
{
	Mix_Pause(channel);
}

void Audio::resumeAudio(int channel)
{	
	Mix_Resume(channel);
}

void Audio::stopAudio(int channel)
{
}

void Audio::audioVolume(int channel, int volume)
{
	if ((channel > -1) && (channel < RESOURCE_MANAGER->getAudiosvectorSize()))
	{
		Mix_Volume(channel, volume);
	}
}

void Audio::close()
{
	Mix_CloseAudio();
}

Audio* Audio::getInstance()
{
	if (pInstance == nullptr)
		pInstance = new Audio();

	return pInstance;
}
