//
//  ofxBpm.h
//  ofxBpm
//
//  Created by mirrorboy on 2013/08/14.
//
//

#pragma once

class ofxBpm {
    
public:
    ofxBpm(float bpm = 120.);
    
    static const int OFX_BPM_MAX = 300;
    static const int OFX_BPM_MIN = 1;

    void start();
    void update();

    void stop();
    void reset();
    
    void setBpm(float bpm);
    float bpm() const;

    bool is4Beat() const;
    bool is8Beat() const;
    bool is16Beat() const;
    bool isPlaying() const;

    int getCountOf4Beat() const;
    int getCountOf8Beat() const;
    int getCountOf16Beat() const;

private:
    float _bpm;
        
    bool  _is32Beat;
    bool  _isPlaying;
    int _countOf32Beat;
    
    double _totalTime;
    double _durationOf32Beat;
    double _remainderOf32Beat;
    
    float _preTime;
    
    inline int getCountOf32Beat() const;
};
