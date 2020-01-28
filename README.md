# Artemis
 Test and Calibration sketch for Orion-compatible WSPR tracker boards.
 
 Re-use your own OrionBoardConfig.h file.
 
 This is Alpha Software. Current version is: v0.01a .

Notes on Software Versioning:

#define ARTEMIS_FW_VERSION "v0.01a"  // in ArtemisConfig..h update with each submission to github
Whole numbers are for released versions. (i.e. 1.0, 2.0 etc.)
Numbers to the right of the decimal are allocated consecutively, one per GITHUB submission.(i.e. 0.01, 0.02 etc)
a=alpha b=beta, r=release


Changelog :

v0.01a - Initial submission. Supports re-use of OrionBoardConfig.h file and allows for manual calibration of the Si5351a
clock using a modified version of the Si5351 Calibration example from the Etherkit Si5351 Library. 
Supports U3S clones (i.e. DL6OW etc)and K1FM boards using the OrionBoardConfiguration.h file to describe the hardware. 