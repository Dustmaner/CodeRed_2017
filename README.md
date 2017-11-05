# CodeRed_2017
Submission for Code Red Event at UH 2017

For this submission I've decided to modify craigsapp's Midi read/write c++ code (https://github.com/craigsapp/midifile) in order to make a simple c++ code which gives a randomly generated chord progression in an annotated way which would make creating unique music faster.

This would help a lot with my project for my Video Game Design class at UH by making my workflow way faster. My biggest challenge of attempting this project was that I had never known the inner workings of midi files much less how to integrate them into c++. Had I more time I would like to all the conditions which chords must follow from going from one to another, because as of now my program only has the simplest fully functioning conditions. Such as, "Chord progressions must always start on I/i", and  "they must also have a V/v at least once".

Just run the project and you should be able to get 2 files: "NOTES.txt" and "CHORDS.mid"

"NOTES" gives you randomly generated blueprints to create your own song.

"CHORDS" gives you a midi file with the same chord progression as "NOTES".


(You may need to disable deprecation, use _CRT_SECURE_NO_WARNINGS)
