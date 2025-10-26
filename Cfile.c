#include "OSheader.hpp"

// Variável global de exemplo
Process system_process;

// Implementa uma função para criar processo
void create_process(int pid, const char* name) {
    system_process.pid = pid;
    strncpy(system_process.name, name, 31);
    system_process.name[31] = '\0';
    system_process.state = 0;
}

// Mostra informações do processo
void show_process(Process* p) {
    printf("PID: %d\n", p->pid);
    printf("Name: %s\n", p->name);
    printf("State: %d\n", p->state);
}
