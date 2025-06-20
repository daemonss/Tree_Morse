#include "morse.h"
#include "spesifikasi.h"
#include "boolean.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void buildMorseTree(MorseTree *tree) {
    Create_tree(tree);
    
    AddNode(tree, 1, "Root", 2, NIL, NIL, "-");
    AddNode(tree, 2, "A", 4, 3, 1, "!");
    AddNode(tree, 3, "B", 6, NIL, 1, "?");
    AddNode(tree, 4, "K", 8, 5, 2, "!!");
    AddNode(tree, 5, "Z", 10, NIL, 2, "!?");
    AddNode(tree, 6, "M", 12, 7, 3, "?!");
    AddNode(tree, 7, "N", 14, NIL, 3, "??");
    AddNode(tree, 8, "G", 16, 9, 4, "!!!");
    AddNode(tree, 9, "H", 18, NIL, 4, "!!?");
    AddNode(tree, 10, "T", 20, 11, 5, "!?!");
    AddNode(tree, 11, "R", NIL, NIL, 5, "!??");
    AddNode(tree, 12, "S", 22, 13, 6, "?!!");
    AddNode(tree, 13, "O", 24, NIL, 6, "?!?");
    AddNode(tree, 14, "P", 26, 15, 7, "??""!");  
    AddNode(tree, 15, "Q", 28, NIL, 7, "???");
    AddNode(tree, 16, "I", 30, 17, 8, "!!!!");
    AddNode(tree, 17, "V", 32, NIL, 8, "!!!?");
    AddNode(tree, 18, "F", NIL, 19, 9, "!!""?!"); 
    AddNode(tree, 19, "L", 33, NIL, 9, "!!""??"); 
    AddNode(tree, 20, "W", NIL, 21, 10, "!?""!!"); 
    AddNode(tree, 21, "5", 34, NIL, 10, "!?""!?"); 
    AddNode(tree, 22, "E", 35, 23, 12, "?""!!!"); 
    AddNode(tree, 23, "D", NIL, NIL, 12, "?""!!?"); 
    AddNode(tree, 24, "C", NIL, 25, 13, "?""!?""!"); 
    AddNode(tree, 25, "Y", NIL, NIL, 13, "?""!?""?"); 
    AddNode(tree, 26, "J", 36, 27, 14, "?""?""!!"); 
    AddNode(tree, 27, "4", NIL, NIL, 14, "?""?""!?"); 
    AddNode(tree, 28, "X", 37, 29, 15, "?""?""?""!"); 
    AddNode(tree, 29, "U", NIL, NIL, 15, "?""?""?""?"); 
    AddNode(tree, 30, "1", NIL, 31, 16, "!!!!!");
    AddNode(tree, 31, "3", NIL, NIL, 16, "!!!!""!?"); 
    AddNode(tree, 32, "8", NIL, NIL, 17, "!!""!??");
    AddNode(tree, 33, "9", NIL, NIL, 19, "!!""????"); 
    AddNode(tree, 34, "SPASI", NIL, NIL, 21, "!?""!??"); 
    AddNode(tree, 35, "2", NIL, NIL, 22, "?""!!!!"); 
    AddNode(tree, 36, "7", NIL, NIL, 26, "?""?""!!!"); 
    AddNode(tree, 37, "6", NIL, NIL, 28, "?""?""?""!!"); 
}

void encodeToMorse(const char *text, char *morseResult, MorseTree *tree) {
    morseResult[0] = '\0';
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        char c = text[i];
        const char *morseChar = getMorseForChar(c);
        
        strcat(morseResult, morseChar);
        
        if (i < len - 1) {
            strcat(morseResult, " ");
        }
    }
}

void decodeFromMorse(const char *morse, char *textResult, MorseTree *tree) {
    textResult[0] = '\0';
    char* morseCopy = strdup(morse);
    if (!morseCopy) return;
    
    char* token = strtok(morseCopy, " ");
    while (token != NULL) {
        boolean found = false;
        
        for (int i = 1; i <= tree->size; i++) {
            if (strcmp(tree->nodes[i].morse_code, token) == 0) {
                if (strcmp(tree->nodes[i].info, "SPASI") == 0) {
                    strcat(textResult, " ");
                } else {
                    strcat(textResult, tree->nodes[i].info);
                }
                found = true;
                break;
            }
        }
        
        if (!found) strcat(textResult, "?");
        token = strtok(NULL, " ");
    }
    
    free(morseCopy);
}