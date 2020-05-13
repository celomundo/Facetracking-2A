#include "ofApp.h"


using namespace ofxCv;


//--------------------------------------------------------------
void ofApp::setup(){
    
    //camera stuff
    vector<ofVideoDevice> devices = cam.listDevices();
    for(int i=0; i < devices.size(); i++)
    {
        ofLogNotice() << devices[i].id << ":" << devices[i].deviceName;
    }
    
    //sound stuff
    mySound.load("PresenceVoxEdit.wav");
    mySound.setLoop(true);
    volume1=1;
    speed1=1;
   
    
    //camera stuff
    cam.setDeviceID(0);
    cam.initGrabber(1280, 720);
    tracker.setup();
    
   

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //camera stuff
    cam.update();
    if(cam.isFrameNew())
    {
        tracker.update(toCv(cam));
        if(tracker.getFound()){
            facePoints = tracker.getImagePoints();
            facePos = tracker.getPosition();
            mouthHeight= tracker.getGesture(ofxFaceTracker::JAW_OPENNESS);
            speed1=ofMap(facePos.x,0,ofGetWidth(),0.5,2);
            mySound.setSpeed(speed1);
            mySound.setVolume(ofMap(mouthHeight,0,1,0,1));
            
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    int nBands = 60;
    float *mySpectrum=ofSoundGetSpectrum(nBands);
    float width=ofGetWidth()/nBands;
    
    
    ofSetColor(255);
     cam.draw(0,0);
    
     if(tracker.getFound()){
         
           //tracker.draw();
         
    for (int i=0;i<nBands;i++){
        
        ofSetColor(ofMap(i,0,nBands,200,255),ofMap(facePos.x,0,ofGetWidth(),25,255),ofMap(i,0,nBands,25,255));
        
        float radius=mySpectrum[i]*(i+1)*ofGetHeight();
        
        ofDrawCircle(facePoints[i],radius/200);
        //ofDrawBitmapString(i,facePoints[i]);
        
        
        }
         
     }
     ofSetColor(0,146,255);
     ofDrawBitmapString("press 's' to stop the audio\n'p' to play the audio", 31, 92);
    ofDrawBitmapString("Move your face\n to change color and audio speed", 31, 122);
    
    
            
    }
void ofApp::mousePressed(int x, int y, int button){
    /*
    if(x<ofGetWidth()){
        //volume1=ofMap(y,0,ofGetHeight(),1,0.7);
        //mySound.setVolume(volume1);
        speed1=ofMap(x,0,ofGetWidth(),0.5,20);
        mySound.setSpeed(speed1);
        //mySound.play();
        //green=ofMap(y,0,ofGetHeight(),0,255);
    }
    */

}
    

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key==' '){
        
    mySound.play();
        
    }else{
    
        if(key=='s')
        {
           mySound.setPaused(true);
            
        }
        if(key=='p')
        {
            mySound.setPaused(false);
                
        }
        
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
