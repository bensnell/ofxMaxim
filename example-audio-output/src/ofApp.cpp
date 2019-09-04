#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(34, 34, 34);
	ofSetVerticalSync(true);
	

	// Fill the audio buffers with zero
	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
	
	// Print the available sound devices
	soundStream.printDeviceList();

	// Setup the sound stream
	ofSoundStreamSettings settings;
	// Set an audio device by name
	auto devices = soundStream.getMatchingDevices("Dante");
	ofLogNotice() << "There are " << devices.size() << "Dante devices.";
	if (!devices.empty()) {
		ofLogNotice() << "Selecting the first one with " << devices[0].outputChannels << " output channels";
		settings.setOutDevice(devices[0]);
	} else {
		ofLogNotice() << "Exiting without an audio device selected.";
		ofExit();
	}
	// Setup the sound stream
	settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = devices[0].outputChannels;
	settings.numInputChannels = 0;
	settings.bufferSize = bufferSize;
	ofLogNotice() << "Setting up sound stream";
	ofLogNotice() << "Sound stream setup? " << soundStream.setup(settings);
	
	// on OSX: if you want to use ofSoundPlayer together with ofSoundStream you need to synchronize buffersizes.
	// use ofFmodSetBuffersize(bufferSize) to set the buffersize in fmodx prior to loading a file.
	ofFmodSetBuffersize(bufferSize);




	// Setup Maxi (not sure if this does anything)
	maxiSettings.setup(sampleRate, devices[0].outputChannels, bufferSize);
	// Setup the ofxMaxim audio buffers
	if (maxiSample.load(ofToDataPath(audioFilename), 0)) {
		ofLogNotice() << "Cher loaded successfully:\t" << maxiSample.getSummary();
		bSampleLoaded = true;
	}


}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(225);
	ofDrawBitmapString("AUDIO OUTPUT EXAMPLE", 32, 32);
	
	ofNoFill();
	
	// draw the left channel:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 150, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Left Channel", 4, 18);
		
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 900, 200);

		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);
					
			ofBeginShape();
			for (unsigned int i = 0; i < lAudio.size(); i++){
				float x =  ofMap(i, 0, lAudio.size(), 0, 900, true);
				ofVertex(x, 100 -lAudio[i]*180.0f);
			}
			ofEndShape(false);
			
		ofPopMatrix();
	ofPopStyle();

	// draw the right channel:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 350, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Right Channel", 4, 18);
		
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 900, 200);

		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);
					
			ofBeginShape();
			for (unsigned int i = 0; i < rAudio.size(); i++){
				float x =  ofMap(i, 0, rAudio.size(), 0, 900, true);
				ofVertex(x, 100 -rAudio[i]*180.0f);
			}
			ofEndShape(false);
			
		ofPopMatrix();
	ofPopStyle();

}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& buffer) {

	// for every frame...
	for (size_t i = 0; i < buffer.getNumFrames(); i++) {

		// (don't query a sample if it hasn't loaded yet) 
		if (bSampleLoaded) {
			// get the next sample from the file
			// the sample loops by default
			sample = maxiSample.play(); // sample returned is in the range [-1, 1]
			// assign the sample to the proper buffers adjusted by volume
			lAudio[i] = buffer[i * buffer.getNumChannels()] = sample * volume;
			rAudio[i] = buffer[i * buffer.getNumChannels() + 1] = sample * volume;
		}
		else {

			// don't return anything
			lAudio[i] = buffer[i * buffer.getNumChannels()] = 0.0;
			rAudio[i] = buffer[i * buffer.getNumChannels()] = 0.0;
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
