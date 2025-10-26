#include "OSheader.hpp"

int main() {
    printf("=== Welcome to MiniOS ===\n");

    // Criar um processo
    create_process(1, "Init");

    // Mostrar informações do processo
    show_process(&system_process);

    // Informações do sistema
    print_system_info();

    return 0;
}

// Função extra do sistema
void print_system_info() {
    printf("MiniOS v0.1\n");
    printf("Compiled for learning purposes\n");
}
