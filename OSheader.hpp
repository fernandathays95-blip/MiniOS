#ifndef OSHEADER_HPP
#define OSHEADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura básica de "processo"
typedef struct {
    int pid;
    char name[32];
    int state; // 0 = pronto, 1 = rodando, 2 = parado
} Process;

// Funções básicas que estarão disponíveis
void print_system_info();
void create_process(int pid, const char* name);
void show_process(Process* p);

#endif // OSHEADER_HPP
