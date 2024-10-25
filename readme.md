
## **MIDI Programming for Windows in C**  

### *SMF and Playback*  


This project is an implementation of a MIDI subsystem capable of managing SMF ( Standard MIDI Files ),  
and a player suitable to reproduce any MIDI file compativle with SMF.  
All the code was made from the scratch so, there are structures to define all needed by the MIDI protocol.  
>  
> - MIDI message.  
> - MIDI event and meta.  
> - MIDI track.  
> - MIDI song ( or sequence ).  
> - MIDI file reader ( Standard MIDI File ).  
> - MIDI file writer ( Standard MIDI File ).  
> - MIDI player ( or sequencer ).  
>  
It runs under MSWindows so, it uses the low level API offered by the system.  
That is, the MIDI device coded in the mmsystem.h header. It was compiled using the MinGW compiler ( Minimalist GNU for Windows ).  
You have the command line installer also available, and explanations to easy install it in your system.  
Some code refactoring was made, and another example about  
what you can create using this library is ready to use in the examples folder.  
We hope that you enjoy this work, and we also expect that you can take benefit from it.  
