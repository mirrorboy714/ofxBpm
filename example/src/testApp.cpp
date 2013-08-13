#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0,0,0);
    ofSetFrameRate(60);
    sound.loadSound("pi.wav");
    sound.setVolume(1.0);
    sound.play();
    
    bpm = ofxBpm(120);

}

//--------------------------------------------------------------
void testApp::update(){
    
    bpm.update();
    
    if(bpm.is8Beat()){
        
        if(bpm.getCountOf8Beat() == 0){
            sound.setVolume(1.0);
        }else{
            sound.setVolume(0.3);
        }

        sound.play();

    }
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){


}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    bpm.start();
    ofDrawBitmapString("Start");

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    bpm.stop();
    ofDrawBitmapString("Stop",ofGetHeight);

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
