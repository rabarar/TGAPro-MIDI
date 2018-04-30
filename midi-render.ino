
#include <MIDI.h>
#include "noteList.h"
#include "pitches.h"
MIDI_CREATE_DEFAULT_INSTANCE();

static const unsigned sMaxNumNotes = 16;
MidiNoteList<sMaxNumNotes> midiNotes;

using namespace midi;

void handleNotesChanged(bool isFirstNote = false)
{
    if (midiNotes.empty())
    {
       // handleGateChanged(false);
       // noTone(sAudioOutPin); // Remove to keep oscillator running during envelope release.
    }
    else
    {
        // Possible playing modes:
        // Mono Low:  use midiNotes.getLow
        // Mono High: use midiNotes.getHigh
        // Mono Last: use midiNotes.getLast

        byte currentNote = 0;
        if (midiNotes.getLast(currentNote))
        {
          //  tone(sAudioOutPin, sNotePitches[currentNote]);

            if (isFirstNote)
            {
               // handleGateChanged(true);
            }
            else
            {
                //pulseGate(); // Retrigger envelopes. Remove for legato effect.
            }
        }
    }
}

void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
    const bool firstNote = midiNotes.empty();
    midiNotes.add(MidiNote(inNote, inVelocity));
    handleNotesChanged(firstNote);
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
    midiNotes.remove(inNote);
    handleNotesChanged();
}

void setup() {
  // put your setup code here, to run once:

  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin();

}

void loop() {
 // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();

    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
}
