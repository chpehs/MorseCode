# Morse code translator
  There are a few ways to create Morse code translator, but the easiest is to create an array of strings, where each string represents a letter in the alphabet.
To translate a word into Morse code, you simply need to look up each letter in the array and concatenate the corresponding string.
  To play the Morse code, you will need to use a loop to iterate over each character in the translated string. 
For each character, you will need to check whether it is a dot or a dash. If it is a dot, turn on the point light for a short duration. 
If it is a dash,turn on the point light for a longer duration.

All of the code in MorseCodePawn.h and MorseCodePawn.cpp

Widget Blueprint:

![Documentation](https://user-images.githubusercontent.com/78034801/190930176-0e7fcb9f-396b-44a4-838e-7e8bad004ec0.png)

P.S. I messed up a timer for a light a bit
