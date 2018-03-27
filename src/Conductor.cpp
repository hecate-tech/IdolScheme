#include "../include/Conductor.h"


//---------------------------------------
float Conductor::calcBeatsInMs(const int bpm) {
	return float(bpm) / 60 / 1000;
}

//---------------------------------------
float Conductor::calcCurrentBeat() const {
	auto timeDiffInMs = std::chrono::duration_cast<ChronoMs>((HiResClock::now() - startTime));
	const float timeDiffInM = (timeDiffInMs.count() - _offsetInMs) / 1000.f / 60.f;
	return timeDiffInM * float(_bpm);
}

//---------------------------------------
void Conductor::startTimer() {
	startTime = HiResClock::now();
	totalBeats = calcTotalBeats(_lengthInS, _bpm) - offsetBeats; 
	offsetBeats = calcTotalBeats(double(_offsetInMs) / 1000, _bpm);
	beatSinceRefresh = 0.0;
}

//---------------------------------------
void Conductor::refreshMembers() {
	currTime = HiResClock::now();  
	timeDiff = std::chrono::duration_cast<ChronoMs>(currTime - startTime);
	currBeat = calcCurrentBeat();
	numBeatsSinceRefresh = static_cast<float>((currBeat) - fabs(beatSinceRefresh));
}