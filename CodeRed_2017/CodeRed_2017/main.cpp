#include "MidiFile.h"
#include "Options.h"
#include "MidiEvent.h"
#include "MidiEventList.h"
#include "MidiMessage.h"
#include "Binasc.h"


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

using namespace std;

int main(int argc, char** argv)
{
	int v1;
	bool v_check = 0;
	srand(time(0));

	Options options;
	options.process(argc, argv);
	MidiFile midifile;
	MidiFile outputfile;
	outputfile.absoluteTicks();
	outputfile.addTrack(3);
	vector<uchar> midievent;
	midievent.resize(3);        
	int tpq = 120;              
	outputfile.setTicksPerQuarterNote(tpq);
	std::ofstream ofs;
	ofs.open("NOTES.txt", std::ofstream::out);


	ofs << "The Chords in A minor are\nA B C D E F G\n\n"
		<< "And they represent the folowing Major/Minor\n"
		<< "i ii7 III iv v VI VII\n\n"
		<< "As reference(in order):\n"
		<< "ACEG (i)\nBDFA (ii7)\nCEGB (III)\nDFAC (iv)\n"
		<< "EGBD (v)\nFACE (vi)\nGBDF (VII)\n\n"
		<< "Your chord progression will be:\n\n";

	int high[9] = {0};
	int mid[9] = {0};
	int low[9] = {0};
	

	//ofs << "telolet om\n";

	//ofs.close();

	for (int i = 0; i < 8; i++)
	{
		if (i != 0)// if not the first chord, then free to choose 
			v1 = rand() % 6 + 1;
		else
			v1 = 1;

		if (i == 7 && v_check == 0)// if on the last chord and no "v" yet then force "v"
			v1 = 5;

		switch (v1) {
		case 1:
			ofs << "A C E G (i)\n\n";
			high[i] = 64;
			mid[i] = 60;
			low[i] = 69;
			break;
		case 2:
			ofs << "B D F A (ii7)\n\n";
			high[i] = 65;
			mid[i] = 62;
			low[i] = 71;
			break;
		case 3:
			ofs << "C E G B (III)\n\n";
			high[i] = 67;
			mid[i] = 64;
			low[i] = 60;
			break;
		case 4:
			ofs << "D F A C (iv)\n\n";
			high[i] = 69;
			mid[i] = 65;
			low[i] = 62;
			break;
		case 5:
			ofs << "E G B D (v)\n\n";
			high[i] = 71;
			mid[i] = 67;
			low[i] = 64;
			v_check = 1;
			break;
		case 6:
			ofs << "F A C E (vi)\n\n";
			high[i] = 60;
			mid[i] = 69;
			low[i] = 65;
			break;
		case 7:
			ofs << "G B D F (VII)\n\n";
			high[i] = 62;
			mid[i] = 71;
			low[i] = 67;
			break;
		default://you need a "v" at least once
			cout << "E G B D (v)\n\n";
		}		
	}

	ofs.close();

	// data to write to MIDI file: (60 = middle C)
	mid[8] = -1;
	low[8] = -1;
	
	int mrhythm[50] = { 4, 4, 4, 4, 4, 4, 4, 4,-1 };
	int brhythm[50] = { 4, 4, 4, 4, 4, 4, 4, 4,-1 };
	int hrhythm[50] = { 4, 4, 4, 4, 4, 4, 4, 4,-1 };

	// store a mid line in track 1 (track 0 left empty for conductor info)
	int i = 0;
	int actiontime = 0;      // temporary storage for MIDI event time
	midievent[2] = 64;       // store attack/release velocity for note command
	while (mid[i] >= 0) {
		midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
		midievent[1] = mid[i];
		outputfile.addEvent(1, actiontime, midievent);
		actiontime += tpq * mrhythm[i];
		midievent[0] = 0x80;     // store a note on command (MIDI channel 1)
		outputfile.addEvent(1, actiontime, midievent);
		i++;
	}

	// store a base line in track 2
	i = 0;
	actiontime = 0;          // reset time for beginning of file
	midievent[2] = 64;
	while (low[i] >= 0) {
		midievent[0] = 0x90;
		midievent[1] = low[i];
		outputfile.addEvent(2, actiontime, midievent);
		actiontime += tpq * brhythm[i];
		midievent[0] = 0x80;
		outputfile.addEvent(2, actiontime, midievent);
		i++;
	}

	// store a base line in track 3
	i = 0;
	actiontime = 0;          // reset time for beginning of file
	midievent[2] = 64;
	while (high[i] >= 0) {
		midievent[0] = 0x90;
		midievent[1] = high[i];
		outputfile.addEvent(3, actiontime, midievent);
		actiontime += tpq * hrhythm[i];
		midievent[0] = 0x80;
		outputfile.addEvent(3, actiontime, midievent);
		i++;
	}

	outputfile.sortTracks();         // make sure data is in correct order
	outputfile.write("CHORDS.mid"); // write Standard MIDI File twinkle.mid

	return 0;
}