#ifndef MORSE_H
#define MORSE_H

#include "spesifikasi.h"

void buildMorseTree(MorseTree *tree);
void encodeToMorse(const char *text, char *morseResult, MorseTree *tree);
void decodeFromMorse(const char *morse, char *textResult, MorseTree *tree);

#endif