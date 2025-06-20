#include "spesifikasi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  

void Create_tree(MorseTree *tree) {
    tree->size = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        strcpy(tree->nodes[i].info, "");
        tree->nodes[i].ps_fs = NIL;
        tree->nodes[i].ps_nb = NIL;
        tree->nodes[i].ps_pr = NIL;
        strcpy(tree->nodes[i].morse_code, "");
    }
}

void Clear_tree(MorseTree *tree) {
    tree->size = 0;
}

boolean IsEmpty(MorseTree *tree) {
    return (tree->size == 0);
}

void InOrderRec(MorseTree *tree, address root) {
    if (root == NIL) return;
    InOrderRec(tree, tree->nodes[root].ps_fs);
    printf("%s ", tree->nodes[root].info);
    InOrderRec(tree, tree->nodes[root].ps_nb);
}

void InOrder(MorseTree *tree, address root) {
    printf("Karakter yang didukung: ");
    InOrderRec(tree, root);
    printf("\n");
}

void AddNode(MorseTree *tree, address idx, const char *info, address fs, address nb, address pr, const char *morse) {
    if (idx >= MAX_NODES) return;
    
    strcpy(tree->nodes[idx].info, info);
    tree->nodes[idx].ps_fs = fs;
    tree->nodes[idx].ps_nb = nb;
    tree->nodes[idx].ps_pr = pr;
    strcpy(tree->nodes[idx].morse_code, morse);
    
    if (idx >= tree->size) tree->size = idx + 1;
}

const char* getMorseForChar(char c) {
    switch(toupper(c)) {
        case 'A': return "!";
        case 'B': return "?";
        case 'K': return "!!";
        case 'Z': return "!?";
        case 'M': return "?!";
        case 'N': return "??";
        case 'G': return "!!!";
        case 'H': return "!!?";
        case 'T': return "!?!";
        case 'R': return "!??";
        case 'S': return "?!!";
        case 'O': return "?!?";
        case 'P': return "??""!";  
        case 'Q': return "???";
        case 'I': return "!!!!";
        case 'V': return "!!!?";
        case 'F': return "!!""?!";
        case 'L': return "!!""??"; 
        case 'W': return "!?""!!"; 
        case '5': return "!?""!?"; 
        case 'E': return "?""!!!"; 
        case 'D': return "?""!!?"; 
        case 'C': return "?""!?""!"; 
        case 'Y': return "?""!?""?"; 
        case 'J': return "?""?""!!";
        case '4': return "?""?""!?"; 
        case 'X': return "?""?""?""!"; 
        case 'U': return "?""?""?""?"; 
        case '1': return "!!!!!";
        case '3': return "!!!!""!?"; 
        case '8': return "!!""!??"; 
        case '9': return "!!""????"; 
        case '2': return "?""!!!!"; 
        case '7': return "?""?""!!!"; 
        case '6': return "?""?""?""!!"; 
        case ' ': return "!?""!??";
        default: return "?";
    }
}