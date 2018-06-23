//
//  ofxBpm.h
//  ofxBpm
//
//  Created by mirrorboy on 2013/08/14.
//
//

/*
You must add listener on testApp and listen beat timing.
 
example on testApp.cpp
 
 
ofAddListener(bpm.beatEvent, this, &testApp::play);

void testApp::play(void){
 
  //sound.play();
  //but, you could not draw somethings.
}

 */

#pragma once
#include "ofMain.h"
#include "ofThread.h"

class ofxBpm : private ofThread{
    
public:
    static const float OFX_BPM_MAX;
    static const float  OFX_BPM_DEFAULT;
    static const float OFX_BPM_MIN;
    static const int OFX_BPM_TICK;

    explicit ofxBpm(float bpm = OFX_BPM_DEFAULT,int beatPerBar = 4);
    
    void setup(float bpm, int beatPerBar);
    void start();
    void stop();
    void reset();
    
    void setBpm(float bpm);
    float getBpm() const;
    
    void setBeatPerBar(int beatPerBar);
    
    ofEvent<void> beatEvent;

    float bpm;
    int barIndex;
    bool isTick;
    bool isPlaying;
    int countOfTick;
    long totalTime;
    long durationOfTick;
    long remainderOfTick;
    
    float preTime;
    int beatPerBar;
private:
    void threadedFunction();
        
    
    
    
    
    inline int getCountOfTick() const;
};

//init
const float ofxBpm::OFX_BPM_MAX = 300. ;
const float ofxBpm::OFX_BPM_DEFAULT = 120.;
const float ofxBpm::OFX_BPM_MIN = 1.;
const int ofxBpm::OFX_BPM_TICK = 960;
