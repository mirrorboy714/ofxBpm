//
//  ofxBpm.cpp
//  ofxBpm
//
//  Created by mirrorboy on 2013/08/14.
//
//


#include "ofxBpm.h"
#include "ofMain.h"

//init
const float ofxBpm::OFX_BPM_MAX = 300. ;
const float ofxBpm::OFX_BPM_DEFAULT = 120.;
const float ofxBpm::OFX_BPM_MIN = 1.;
const int ofxBpm::OFX_BPM_TICK = 960;

ofxBpm::ofxBpm(float bpm,int beatPerBar):_beatPerBar(beatPerBar){
    _isPlaying = false;
    _isTick = false;
    setBpm(bpm);
};


void ofxBpm::start(){
    stop();
    _isPlaying = true;
    reset();
    startThread(true);   // blocking, verbose
}

void ofxBpm::stop(){
    //stopThread();
    waitForThread(true);
    _isPlaying = false;
}

void ofxBpm::reset(){
    if (lock()) {
        _remainderOfTick = 0;
        _countOfTick = -1;
        _preTime = ofGetElapsedTimeMicros();
        _totalTime = 0;
        unlock();
    }
}

void ofxBpm::threadedFunction(){
    //この
    while( isThreadRunning() != 0 ){
        if( lock() ){
            if(_isPlaying == true) {
                long nowTime = ofGetElapsedTimeMicros();
                long deltaTime = nowTime - _preTime;
                _preTime = nowTime;
                if (_totalTime + _remainderOfTick >= _durationOfTick) {
                    if ((_countOfTick % (OFX_BPM_TICK / _beatPerBar)) == 0) {
                        ofNotifyEvent(beatEvent);
                    }
                    _remainderOfTick = (_totalTime + _remainderOfTick) % _durationOfTick;
                    _totalTime = 0.;
                    _isTick = true;
                    _countOfTick++;
                    _countOfTick %= OFX_BPM_TICK;
                } else {
                    _isTick = false;
                }
                _totalTime += deltaTime;
                unlock();
                yield();
            }
        }
    }
}

void ofxBpm::setBeatPerBar(int beatPerBar){
    if(lock()){
        _beatPerBar = beatPerBar;
        unlock();
    }
}

void ofxBpm::setBpm(float bpm){
    if( lock() ){
        if (bpm < OFX_BPM_MIN) {
            _bpm = OFX_BPM_MIN;
        } else if (bpm >= OFX_BPM_MAX){
            _bpm = OFX_BPM_MAX;
        } else {
            _bpm = bpm;
        }
        _durationOfTick = 60. * 1000. * 1000. / (bpm * (OFX_BPM_TICK >> 2));
        unlock();
    }
}

float ofxBpm::getBpm() const{
    return _bpm;
}

bool ofxBpm::isPlaying() const{
    return _isPlaying;
}
