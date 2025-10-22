#include "pitches.h"  // Include file that defines musical note frequencies

// --- Melody Definition ---
// List of musical notes for the melody
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// Duration of each note
// 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  // Loop through all the notes in the melody
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // Calculate the note duration:
    // 1000 ms (1 second) divided by note type (4 = quarter note → 250 ms)
    int noteDuration = 1000 / noteDurations[thisNote];

    // Play the tone on pin 8 with the calculated frequency and duration
    tone(8, melody[thisNote], noteDuration);

    // Add a short pause between notes for clarity
    // Using 130% of note duration gives a natural separation
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // Stop the tone before playing the next one
    noTone(8);
  }
}

void loop() {
  // No need to repeat the melody automatically
}
