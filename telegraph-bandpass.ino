#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "CosChaotic2BPF.h"

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise1;         //xy=235,329
CosChaotic2BPF           bandpass;
AudioOutputI2S           i2s1;           //xy=635,328

//AudioConnection          patchCord1(noise1, 0, i2s1, 0);
//AudioConnection          patchCord2(noise1, 0, i2s1, 1);
AudioConnection          patchCord1(noise1, 0, bandpass, 0);
AudioConnection          patchCord2(bandpass, 0, i2s1, 0);
AudioConnection          patchCord3(bandpass, 0, i2s1, 1);
// GUItool: end automatically generated code
AudioControlSGTL5000     codec;     //xy=334,437

int potA2 = A13;
int potB2 = A0;
int potC2 = A12;
int potD2 = A7;
int potE2 = A6;

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* 
  North Coast Modular Collective Telegraph Bandpass
  ---------------------------------------------------------
  Copyright 2019 North Coast Modular Collective
  MIT License:
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
  documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
  the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and 
  to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of 
  the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  ----------------------------------------------------------
   

*/


void setup(){
    Serial.begin(9600);
    AudioMemory(200);
    
    codec.enable();
    codec.volume(0.5);
    codec.lineOutLevel(13);
    codec.dacVolume(1);
    
    AudioNoInterrupts(); 
    // set initial bandpass settings
    // more init code?
    

    noise1.amplitude(0.5);


    AudioInterrupts();
}


void loop(){
    float filterFrequency = map(analogRead(potB2), 0, 1023, 0, 2200); 
    bandpass.setParamValue("frequency",filterFrequency);
//
    float filterQ = mapf((float)analogRead(potE2), 0.0, 1023.0, 0.0, 1.0); 
    bandpass.setParamValue("Q",filterQ);
//
    float filterFeedbackGain = map(analogRead(potD2), 0, 1023, 0, 100); 
    bandpass.setParamValue("g",filterFeedbackGain);
//
//    int filterFeedbackPhaseOffset = mapf(analogRead(potD2), 0.0, 1023.0, 0.0, 100.0); 
//    bandpass.setParamValue("phaseOffset",filterFeedbackPhaseOffset);

//    Serial.println(filterQ);
//    Serial.println("HIIIIIII");
    
    delay(50);

    
    //read pin values and set bandpass params
}
