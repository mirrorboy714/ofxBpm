#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // use the `setup(bpm, beatPerBpm)` function to initialize the bpm and beatPerBpm
    bpm.setup(120, 4);
    
    // other initialisation method
    //bpm.setBpm(120);
    //bpm.setBeatPerBar(4);

    // use the `start` function to start the bpm
    bpm.start();
    
    // add a listener on the beatEvent to listen to every beat
    ofAddListener(bpm.beatEvent, this, &ofApp::onBeatEvent);
}

void ofApp::onBeatEvent() {
    // we use bpm.barIndex+1 because bpm.barIndex goes from 0 to 3
    gotBeat = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    int x = 10;
    int y = 15;
    ofSetColor(255);
    ofDrawBitmapString("bar : "+ ofToString(bpm.barIndex+1)+"/"+ofToString(bpm.beatPerBar), x, y);
    y += 15;
    ofDrawBitmapString("bpm : "+ofToString(bpm.bpm), x, y);
    y += 15;
    ofDrawBitmapString("isPlaying : "+ ofToString(bpm.isPlaying), x, y);
    y += 15;
    ofDrawBitmapString("press spacebar to start / pause", x, y);
    y += 15;
    ofDrawBitmapString("press left/right to change the bpm", x, y);
    if(gotBeat) {
        y += 30;
        if(bpm.barIndex == 0)
            ofSetColor(0, 255, 0);
        else
            ofSetColor(255, 0, 0);
        ofDrawCircle(ofGetWidth()/2, y, 10);
        gotBeat = false;
    }
}

void ofApp::exit() {
    bpm.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            if(bpm.isPlaying)
                bpm.stop();
            else
                bpm.start();
            break;
        case OF_KEY_LEFT:
            bpm.setBpm(bpm.bpm - 1);
            break;
        case OF_KEY_RIGHT:
            bpm.setBpm(bpm.bpm + 1);
            break;
        case 'r':
            bpm.reset();
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
