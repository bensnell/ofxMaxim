#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

// Maxim only works with 16 bit mono wav files (24 and 32 bit don't work, and neither does stereo)

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void audioOut(ofSoundBuffer & buffer);
		
		
		ofSoundStream soundStream;

		int	bufferSize = 256;
		int	sampleRate = 48000;
		float volume = 0.4; // [0,1]

		vector <float> lAudio;
		vector <float> rAudio;

		// Maxim audio
		ofxMaxiSample maxiSample;
		string audioFilename = "audio_1_channel_16bit.wav";
		bool bSampleLoaded = false;
		double sample;

		ofxMaxiSettings maxiSettings;

};
