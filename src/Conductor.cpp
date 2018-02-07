#include "../include/Conductor.h"


float Conductor::calcBeatsInMs(int bpm) {
	return bpm / 60 / 1000;
}

float Conductor::calcCurrentBeat() {
	auto timeDiffInMs = std::chrono::duration_cast<ChronoMs>((HiResClock::now() - startTime));
	float timeDiffInM = (timeDiffInMs.count() - _offsetInMs) / 1000.0 / 60.0;
	return timeDiffInM * (float) _bpm;
}

void Conductor::startTimer() {
	startTime = HiResClock::now();
	totalBeats = calcTotalBeats(_lengthInS, _bpm) - offsetBeats; 
	offsetBeats = calcTotalBeats((double) _offsetInMs / 1000, _bpm);
	beatSinceRefresh = 0.0;
}

void Conductor::refreshMembers() {
	currTime = HiResClock::now();  
	timeDiff = std::chrono::duration_cast<ChronoMs>(currTime - startTime);
	currBeat = calcCurrentBeat();
	numBeatsSinceRefresh = fabs(currBeat) - fabs(beatSinceRefresh);
}

void Conductor::conduct() {
	auto startTimeT = ChronoSysClock::to_time_t((std::chrono::system_clock::time_point&)startTime);
	time_t currTimeT;
	while(timeDiff.count() / 1000 < _lengthInS) {
		refreshMembers();
		currTimeT = ChronoSysClock::to_time_t((std::chrono::system_clock::time_point&)currTime);
		cout << "Start time (s): " << startTimeT;
		cout << "\nCurrent time (s): " << currTimeT;
		cout << "\nOffset (ms): " << _offsetInMs;
		cout << "\nTime (s): " << (double) timeDiff.count() / 1000 << " / " << _lengthInS;
		cout << "\nOffset beats: " << offsetBeats;
		cout << "\nCurrent beat: " << currBeat << " / " << totalBeats << std::endl;
		std::system("clear");
	}
}
