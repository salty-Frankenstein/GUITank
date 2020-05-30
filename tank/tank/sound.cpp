#include "sound.h"

Sound::Sound() {}

Sound::Sound(std::wstring _soundName) {
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);
	pGraph->QueryInterface(IID_IMediaControl, (void**)&pCtrl);
	pGraph->QueryInterface(IID_IMediaPosition, (void**)&pPos);
	pGraph->RenderFile(_soundName.c_str(), NULL);
}

void Sound::Play() {
	pPos->put_CurrentPosition(0);
	pCtrl->Run();
}

void Sound::Stop() {
	pCtrl->Stop();

}

Music::Music() {}

Music::Music(std::wstring _soundName, REFTIME _loopBegin) 
	: Sound(_soundName) {
	active = false; 
	loop = false;
	loopBegin = _loopBegin;
}

void Music::Play() {
	if (!active)return;
	pCtrl->Run();
	if(loop)Loop();
}

void Music::Stop() {
	pCtrl->Stop();
	pPos->put_CurrentPosition(0);
	active = false;
}

void Music::Pause() {
	if (!active)return;
	pCtrl->Pause();
}

void Music::Loop() {
	REFTIME duration = 0, cur = 0;
	pPos->get_Duration(&duration);
	pPos->get_CurrentPosition(&cur);
	if(cur > duration - 0.1)pPos->put_CurrentPosition(loopBegin);
}
