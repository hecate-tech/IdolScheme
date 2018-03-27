#pragma once

#ifndef CMATH
	#include <cmath>
#endif

#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

enum NoteAccuracy {
    WONDERFUL,
    GOOD,
    MEDIOCRE,
    BAD,
    GARBAGE,
    WRONG
};

enum ScoreGrade {
    SPLUS,
    S,
    A,
    B,
    C,
    D,
    F
};

class ScoreKeeper {
public:
    int wonderfulCount;
    int goodCount;
    int mediocreCount;
    int badCount;
    int garbageCount;
    int wrongCount;

    int score;
    float accuracy;

    ScoreGrade grade;
};

NoteAccuracy assessAccuracy(float currBeat, float targetBeat); 
#endif
