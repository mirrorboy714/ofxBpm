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
    
    void start();
    void stop();
    void reset();
    
    void setBpm(float bpm);
    float getBpm() const;
    
    void setBeatPerBar(int beatPerBar);
    
    bool isPlaying() const;

    ofEvent<void> beatEvent;

private:
    void threadedFunction();
        
    
    
    float _bpm;
    bool  _isTick;
    bool  _isPlaying;
    int _countOfTick;
    long _totalTime;
    long _durationOfTick;
    long _remainderOfTick;
    
    float _preTime;
    int _beatPerBar;
    
    inline int getCountOfTick() const;
};

//init
const float ofxBpm::OFX_BPM_MAX = 300. ;
const float ofxBpm::OFX_BPM_DEFAULT = 120.;
const float ofxBpm::OFX_BPM_MIN = 1.;
const int ofxBpm::OFX_BPM_TICK = 960;
