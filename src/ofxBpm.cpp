//
//  ofxBpm.cpp
//  ofxBpm
//
//  Created by mirrorboy on 2013/08/14.
//
//


#include "ofxBpm.h"
#include "ofMain.h"

ofxBpm::ofxBpm(float bpm,int beatPerBar):beatPerBar(beatPerBar){
    
    isPlaying = false;
    isTick = false;
    
    setBpm(bpm);
};

void ofxBpm::setup(float bpm, int beatPerBar) {
    this->bpm = bpm;
    this->beatPerBar = beatPerBar;
}

void ofxBpm::start(){
    
    stop();
    
    isPlaying = true;
    reset();
    
    startThread(true);   // blocking, verbose
    
}

void ofxBpm::stop(){
    
    //stopThread();
    waitForThread(true);
    
    isPlaying = false;
}

void ofxBpm::reset(){

    if( lock() ){
        barIndex = 0;
        remainderOfTick = 0;
        countOfTick = -1;
        preTime = ofGetElapsedTimeMicros();
        totalTime = 0;
        
        unlock();
    }
}


void ofxBpm::threadedFunction(){
    
    //この
    while( isThreadRunning() != 0 ){
        
        if( lock() ){
            
            if(isPlaying == true){
                
                long nowTime = ofGetElapsedTimeMicros();
                long deltaTime = nowTime - preTime;
                preTime = nowTime;
                
                if(totalTime + remainderOfTick >= durationOfTick){
                    
                    
                    if((countOfTick % (OFX_BPM_TICK / beatPerBar)) == 0){
                        
                        barIndex = beatPerBar * countOfTick/OFX_BPM_TICK;
                        
                        ofNotifyEvent(beatEvent);
                    }
                    
                    remainderOfTick = (totalTime + remainderOfTick) % durationOfTick;
                    
                    totalTime = 0.;
                    
                    isTick = true;
                    

                    
                    countOfTick++;
                    
                    countOfTick %= OFX_BPM_TICK;
                    
                }else{
                    
                    isTick = false;
                }
                
                totalTime += deltaTime;
                
                unlock();
                
                yield();
            }
        }
    }
    
}

void ofxBpm::setBeatPerBar(int beatPerBar){
    
    if(lock()){

        this->beatPerBar = beatPerBar;
        unlock();
    }
}

void ofxBpm::setBpm(float bpm){
    
    if( lock() ){
        if(bpm < OFX_BPM_MIN){
            
            this->bpm = OFX_BPM_MIN;
            
        }else if(bpm >= OFX_BPM_MAX){
            
            this->bpm = OFX_BPM_MAX;
            
        }else{
            
            this->bpm = bpm;
            
        }
        
        durationOfTick = 60. * 1000. * 1000. / (this->bpm * (OFX_BPM_TICK >> 2));
        
        unlock();
    }
}

float ofxBpm::getBpm() const{
    
    return bpm;
}
