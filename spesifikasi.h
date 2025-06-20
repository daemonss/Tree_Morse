#ifndef SPESIFIKASI_H
#define SPESIFIKASI_H

#include "boolean.h"

#define MAX_NODES 50
#define NIL -1

typedef char infotype[10];
typedef int address;

typedef struct {
    infotype info;
    address ps_fs;  // First son
    address ps_nb;  // Next brother
    address ps_pr;  // Parent
    char morse_code[10]; // Menyimpan kode morse sesuai tabel
} TreeNode;

typedef struct {
    TreeNode nodes[MAX_NODES];
    int size;
} MorseTree;

void Create_tree(MorseTree *tree);
void Clear_tree(MorseTree *tree);
boolean IsEmpty(MorseTree *tree);
void InOrder(MorseTree *tree, address root);
void AddNode(MorseTree *tree, address idx, const char *info, address fs, address nb, address pr, const char *morse);
const char* getMorseForChar(char c);

#endif