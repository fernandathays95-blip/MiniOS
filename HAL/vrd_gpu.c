// File: HAL/vrd_gpu.c
// Virtual Render Device (VRD GPU) HAL implementation
// Implements a simple in-memory framebuffer and a command interface.
//
// Dependências:
//   - ../OSheader.hpp
//   - HAL/vrd_gpu_driver.h
//
// Observação: este é um HAL simulado para estudo/integração em um OS de aprendizado.
//            Não interage com hardware real; tudo é em memória e mensagens no stdout.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../OSheader.hpp"
#include "vrd_gpu_driver.h"

// -----------------------------
// Estrutura interna da GPU HAL
// -----------------------------
typedef struct {
    const char* name;
    int width;
    int height;
    int initialized;
    unsigned int* framebuffer; // buffer de pixels em RGB24 (0xRRGGBB)
} VRD_GPU;

static VRD_GPU vrd_gpu = {0};

// -----------------------------
// Registradores simulados
// (declarados extern em vrd_gpu_driver.h)
// -----------------------------
VRD_GPU_REGISTERS vrd_registers = {0};

// -----------------------------
// Implementação das funções HAL
// -----------------------------

// Inicializa a GPU virtual (aloca framebuffer)
void vrd_gpu_init(int width, int height) {
    if (vrd_gpu.initialized) {
        printf("[VRD_GPU] Already initialized.\n");
        return;
    }

    if (width <= 0 || height <= 0) {
        printf("[VRD_GPU] Error: invalid resolution %dx%d\n", width, height);
        return;
    }

    vrd_gpu.name = "VRD Virtual GPU";
    vrd_gpu.width = width;
    vrd_gpu.height = height;
    vrd_gpu.framebuffer = (unsigned int*)calloc((size_t)width * (size_t)height, sizeof(unsigned int));
    if (vrd_gpu.framebuffer == NULL) {
        printf("[VRD_GPU] Error: failed to allocate framebuffer (%d x %d)\n", width, height);
        return;
    }
    vrd_gpu.initialized = 1;

    // Atualiza registradores simulados
    vrd_registers.VRD_WIDTH = (unsigned int)width;
    vrd_registers.VRD_HEIGHT = (unsigned int)height;
    vrd_registers.VRD_STATUS = 1;

    printf("[VRD_GPU] Initialized %dx%d framebuffer.\n", width, height);
}

// Limpa a tela preenchendo com a cor indicada (0xRRGGBB)
void vrd_gpu_clear(unsigned int color) {
    if (!vrd_gpu.initialized) {
        printf("[VRD_GPU] Error: GPU not initialized!\n");
        return;
    }

    size_t total = (size_t)vrd_gpu.width * (size_t)vrd_gpu.height;
    for (size_t i = 0; i < total; ++i) {
        vrd_gpu.framebuffer[i] = color & 0x00FFFFFFu;
    }

    printf("[VRD_GPU] Screen cleared to 0x%06X.\n", color & 0x00FFFFFFu);
}

// Desenha um pixel em (x,y) com a cor (0xRRGGBB)
void vrd_gpu_draw_pixel(int x, int y, unsigned int color) {
    if (!vrd_gpu.initialized) {
        printf("[VRD_GPU] Error: GPU not initialized!\n");
        return;
    }
    if (x < 0 || x >= vrd_gpu.width || y < 0 || y >= vrd_gpu.height) {
        printf("[VRD_GPU] Warning: Pixel out of bounds (%d,%d)\n", x, y);
        return;
    }

    size_t idx = (size_t)y * (size_t)vrd_gpu.width + (size_t)x;
    vrd_gpu.framebuffer[idx] = color & 0x00FFFFFFu;
}

// Mostra informações da GPU (status e resolução)
void vrd_gpu_info() {
    printf("\n=== VRD GPU INFO ===\n");
    printf("Name   : %s\n", vrd_gpu.name ? vrd_gpu.name : "Unknown");
    printf("Width  : %d\n", vrd_gpu.width);
    printf("Height : %d\n", vrd_gpu.height);
    printf("Status : %s\n", vrd_gpu.initialized ? "Initialized" : "Not initialized");
    printf("LastCmd: 0x%X\n", vrd_registers.VRD_LAST_CMD);
}

// Libera recursos e zera estado
void vrd_gpu_shutdown() {
    if (vrd_gpu.framebuffer) {
        free(vrd_gpu.framebuffer);
        vrd_gpu.framebuffer = NULL;
    }
    vrd_gpu.initialized = 0;

    vrd_registers.VRD_STATUS = 0;
    vrd_registers.VRD_WIDTH = 0;
    vrd_registers.VRD_HEIGHT = 0;
    vrd_registers.VRD_LAST_CMD = 0;

    printf("[VRD_GPU] Shutdown complete.\n");
}

// -----------------------------
// Interface de comando (driver -> HAL)
// -----------------------------
// cmd: código do comando (VRD_CMD_...)
// arg1/arg2: parâmetros (ex: x, y ou width, height)
// color: cor (quando aplicável)
void vrd_gpu_send_command(unsigned int cmd, int arg1, int arg2, unsigned int color) {
    // registra o último comando
    vrd_registers.VRD_LAST_CMD = cmd;

    switch (cmd) {
        case VRD_CMD_INIT:
            // usa arg1 = width, arg2 = height
            vrd_gpu_init(arg1, arg2);
            break;

        case VRD_CMD_CLEAR:
            // usa color
            vrd_gpu_clear(color);
            break;

        case VRD_CMD_DRAW_PIXEL:
            // arg1 = x, arg2 = y, color = cor
            vrd_gpu_draw_pixel(arg1, arg2, color);
            break;

        case VRD_CMD_INFO:
            vrd_gpu_info();
            break;

        case VRD_CMD_SHUTDOWN:
            vrd_gpu_shutdown();
            break;

        default:
            printf("[VRD_GPU] Unknown command: 0x%X\n", cmd);
            break;
    }
}

// -----------------------------
// Função utilitária opcional:
// dump simples do framebuffer (texto) para debug.
// imprime como ASCII rudimentar ('.' para preto, '#' para pixel não-preto).
// -----------------------------
void vrd_gpu_dump_ascii(int max_width, int max_height) {
    if (!vrd_gpu.initialized) {
        printf("[VRD_GPU] Dump: GPU not initialized.\n");
        return;
    }

    int w = vrd_gpu.width;
    int h = vrd_gpu.height;
    int mw = (max_width > 0 && max_width < w) ? max_width : w;
    int mh = (max_height > 0 && max_height < h) ? max_height : h;

    printf("\n[VRD_GPU] Framebuffer dump (top-left %dx%d):\n", mw, mh);
    for (int y = 0; y < mh; ++y) {
        for (int x = 0; x < mw; ++x) {
            unsigned int px = vrd_gpu.framebuffer[(size_t)y * (size_t)w + (size_t)x];
            putchar(px == 0 ? '.' : '#');
        }
        putchar('\n');
    }
}
