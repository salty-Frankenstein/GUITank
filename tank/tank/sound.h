#pragma once
#include <dshow.h>
#include <string>

class Sound {
public:
	Sound();
	Sound(std::wstring _soundName);
	virtual void Play();
	virtual void Stop();

protected:
	IGraphBuilder * pGraph;
	IMediaControl *pCtrl;
	IMediaPosition *pPos;
};

class Music :public Sound {
public:
	Music();
	Music(std::wstring _soundName, REFTIME _loopBegin = 0);
	void Pause();
	void Play()override;
	void Stop()override;
	void Loop();
	bool active;
	bool loop;
	REFTIME loopBegin;
};

