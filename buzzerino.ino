/*
  buzzerino.ino

  A fork of Mod4a.ino (see more next to this description) made by 
  Marcos Marado <mindboosternoori@gmail.com>.
  
  This is meant to be a general-purpose music player using an one-buzzer
  *duino.  

  By convention, the buzzer is on pin 3, but you can change it on the
  constants section.
  
  Find the latest version at: https://github.com/marado/buzzerino
  CC BY-SA

  -----------------------------------------------------------------------

  "Mod4a.ino" is:
    _____ _____ _____   _     _            ___ 
   |     |   __|   __|_| |_ _|_|___ ___   |_  |
   |   --|__   |   __| . | | | |   | . |  |  _|
   |_____|_____|_____|___|___|_|_|_|___|  |___|

  Mod4a.ino

  Created by Joao Alves on 2015-Feb-17.
  Copyright 2014 - Under creative commons license 3.0:
          Attribution-ShareAlike CC BY-SA
  This software is provided "as is", without technical support, and with no 
  warranty, express or implied, as to its usefulness for any purpose.

  Description:
	Plays tones in the Buzzer

	The circuit:
	* Buzzer - Pin 3

  Notes: 
  -
      
  Links:
  * CSEduino: http://jpralves.net/cseduino
  * Sources: https://github.com/jpralves/cseduino/workshop

	Created on 2015-Feb-17
	By Joao Alves <jpralves@gmail.com> and presented on Lisbon mini MakerFaire
	2014

  -----------------------------------------------------------------------

*/

#include "pitches.h"

/* constants */ 
const int buzzerPin = 3;

/* songs */

// TODO: move this into an included file (one song == one file)

long bpm = 120L; // beats per minute
int bpb = 4; // beats per bar. For instance, a 4/4 signature has bpb = 4, a 2/4 signature has bpb = 2
int notes[] = {NOTE_C4, NOTE_E4, NOTE_G4};
int tempos[] = {1,2,4}; // TODO: we should be dealing with floats (1/2 notes and so on)

/* end of configuration */

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // TODO: input validation. At least check sizeof(notes) and sizeof(tempo) are the same.

  // To calculate noteDuration we must know the time of a beat:
  long rate = 60L*bpb; // seconds in a minute times number of beats in a bar
  long rateMs = rate*1000L; // rate in ms
  long barTimeMs = rateMs/bpm; // one bar times rate in ms, divided by bpm
  long beatTimeMs = barTimeMs/bpb;

  // let's play the song
  for (int thisNote = 0; thisNote < (sizeof(notes) / sizeof(int)); thisNote++) {
    long noteDuration = beatTimeMs*tempos[thisNote];
    tone(buzzerPin, notes[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30; //TODO: un-hardcode. Also, the pauseBetweenNotes should be a function of bpm, not noteDuration
	// TODO: have the song set the "instrument": continuous or with the delay
	// (silence between notes). If we maintain the delay, we need to "steal it"
	// from the node duration, instead of adding to it.
    delay(pauseBetweenNotes); 
    noTone(buzzerPin);
  }
}
