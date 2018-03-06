#include "../include/ScoreKeeper.h"

NoteAccuracy assessAccuracy(float currBeat, float targetBeat) {
    float offByBeats = std::abs(targetBeat - currBeat);

    if (offByBeats < 0.025)
        return WONDERFUL;
    else if (offByBeats < 0.05)
        return GOOD;
    else if (offByBeats < 0.1)
        return MEDIOCRE;
    else if (offByBeats < 0.2)
        return BAD;
    else if (offByBeats < 1 && offByBeats > 0.2)
        return GARBAGE;
}
