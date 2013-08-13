//
//  ofxBpm.cpp
//  ofxBpm
//
//  Created by mirrorboy on 2013/08/14.
//
//


#include "ofxBpm.h"
#include "ofMain.h"

ofxBpm::ofxBpm(float bpm){

    _isPlaying = false;
    _is32Beat = false;
    
    setBpm(bpm);
};

void ofxBpm::start(){
    
    _isPlaying = true;
    reset();
}

void ofxBpm::stop(){
    
    _isPlaying = false;
}

void ofxBpm::reset(){
    
    _remainderOf32Beat = 0;
    _countOf32Beat = -1;    
    _preTime = ofGetElapsedTimeMicros();
    _totalTime = 0;

}

void ofxBpm::update(){
    
    
    if(_isPlaying == true){
    
        double nowTime = ofGetElapsedTimeMicros();
        double deltaTime = nowTime - _preTime;
        _preTime = nowTime;
        
        if(_totalTime + _remainderOf32Beat >= _durationOf32Beat){
            
            _remainderOf32Beat = (_totalTime + _remainderOf32Beat) - _durationOf32Beat;
            
            _totalTime = 0.;
            
            _is32Beat = true;
            _countOf32Beat++;
            _countOf32Beat %= 32;
                        
        }else{

            _is32Beat = false;
        }
        
        _totalTime += deltaTime;
    }
}

void ofxBpm::setBpm(float bpm){
    
    if(bpm < OFX_BPM_MIN){
     
        _bpm = OFX_BPM_MIN;
        
    }else if(bpm >= OFX_BPM_MAX){
        
        _bpm = OFX_BPM_MAX;
        
    }else{
    
        _bpm = bpm;

    }
    
    _durationOf32Beat = 60. * 1000. * 1000. / (bpm * 8.);

}

float ofxBpm::bpm() const{
    
    return _bpm;
}

bool ofxBpm::isPlaying() const{
    
    return _isPlaying;
}

bool ofxBpm::is4Beat() const{
    return (is8Beat() && (getCountOf32Beat() % 8 == 0));
}

bool ofxBpm::is8Beat() const{
    return (is16Beat() && (getCountOf32Beat() % 4 == 0));
}

bool ofxBpm::is16Beat() const{
    return (_isPlaying && _is32Beat && (getCountOf32Beat() % 2 == 0));
}


int ofxBpm::getCountOf4Beat() const{
    
    return (_countOf32Beat / 8);
}

int ofxBpm::getCountOf8Beat() const{
    
    return (_countOf32Beat / 4);
}

int ofxBpm::getCountOf16Beat() const{
    
    return (_countOf32Beat / 2);
}

int ofxBpm::getCountOf32Beat() const{
    return (_countOf32Beat);
}