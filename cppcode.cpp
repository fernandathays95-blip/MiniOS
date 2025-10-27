#include "OSheader.hpp"

int main() {
    printf("=== Welcome to MiniOS ===\n");

    // Criar um processo
    create_process(1, "Init");

    // Mostrar informações do processo
    show_process(&system_process);

    // Informações do sistema
    print_system_info();
    printf("=== Starting VRD GPU Test ===\n");

    vrd_gpu_init(640, 480);
    vrd_gpu_clear(0x000000); // preto
    vrd_gpu_draw_pixel(10, 10, 0xFFFFFF); // pixel branco
    vrd_gpu_info();
    vrd_gpu_shutdown();
    return 0;
}

// Função extra do sistema
void print_system_info() {
    printf("MiniOS v0.1\n");
    printf("Compiled for learning purposes\n");
}
