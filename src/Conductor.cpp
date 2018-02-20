#include "../include/Conductor.h"


//---------------------------------------
float Conductor::calcBeatsInMs(int bpm) {
	return bpm / 60 / 1000;
}

//---------------------------------------
float Conductor::calcCurrentBeat() {
	auto timeDiffInMs = std::chrono::duration_cast<ChronoMs>((HiResClock::now() - startTime));
	float timeDiffInM = (timeDiffInMs.count() - _offsetInMs) / 1000.0 / 60.0;
	return timeDiffInM * (float) _bpm;
}

//---------------------------------------
void Conductor::startTimer() {
	startTime = HiResClock::now();
	totalBeats = calcTotalBeats(_lengthInS, _bpm) - offsetBeats; 
	offsetBeats = calcTotalBeats((double) _offsetInMs / 1000, _bpm);
	beatSinceRefresh = 0.0;
}

//---------------------------------------
void Conductor::refreshMembers() {
	currTime = HiResClock::now();  
	timeDiff = std::chrono::duration_cast<ChronoMs>(currTime - startTime);
	currBeat = calcCurrentBeat();
	numBeatsSinceRefresh = fabs(currBeat) - fabs(beatSinceRefresh);
}