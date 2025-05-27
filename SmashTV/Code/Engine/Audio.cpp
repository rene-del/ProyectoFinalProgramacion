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

int Audio::playAudio(int channel, int chunkID, int loops)
{
	int chanelPlayed;

	if ((chunkID > -1) && (chunkID < RESOURCE_MANAGER->getAudiosvectorSize()))
	{
		chanelPlayed = Mix_PlayChannel(channel, RESOURCE_MANAGER->getAudioByID(chunkID), loops);

		if (chanelPlayed == -1)
		{
			std::cout << Mix_GetError() << std::endl;
		}

		return chanelPlayed;
	}
	else
	{
		std::cout << "Invalid chunkID: " << chunkID << std::endl;
	}

	return -1;
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
	if (channel != -1)
	{
		Mix_HaltChannel(channel);
	}
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
