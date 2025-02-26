#ifndef AUDIO_H
#define AUDIO_H

class Audio
{
private:
	Audio();

	static Audio* pInstance;

public:
	~Audio();

	// Init Mixer
	void open();

	// Mixer Channels
	void channels();

	// Play Audio
	void playAudio(int channel, int chunkID, int loops);

	// Pause Audio
	void pauseAudio(int channel);

	// Resume Audio
	void resumeAudio(int channel);

	// Stop Audio
	void stopAudio(int channel);

	// Audio Volume
	void audioVolume(int channel, int volume);

	// Close Mixer
	void close();

	// Instance
	static Audio* getInstance();
};

#endif

