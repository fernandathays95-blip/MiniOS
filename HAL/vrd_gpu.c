// File: HAL/vrd_gpu.c
// Virtual Render Device (VRD GPU) HAL layer
// This file is part of the compiled OS HAL system

#include "../OSheader.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa o estado da GPU
typedef struct {
    const char* name;
    int width;
    int height;
    int initialized;
    unsigned int* framebuffer; // buffer de pixels
} VRD_GPU;

static VRD_GPU vrd_gpu;

// Inicializa a GPU virtual
void vrd_gpu_init(int width, int height) {
    if (vrd_gpu.initialized) {
        printf("[VRD_GPU] Already initialized.\n");
        return;
    }

    vrd_gpu.name = "VRD Virtual GPU";
    vrd_gpu.width = width;
    vrd_gpu.height = height;
    vrd_gpu.framebuffer = (unsigned int*)calloc(width * height, sizeof(unsigned int));
    vrd_gpu.initialized = 1;

    printf("[VRD_GPU] Initialized %dx%d framebuffer.\n", width, height);
}

// Limpa a tela (framebuffer)
void vrd_gpu_clear(unsigned int color) {
    if (!vrd_gpu.initialized) {
        printf("[VRD_GPU] Error: GPU not initialized!\n");
        return;
    }

    for (int i = 0; i < vrd_gpu.width * vrd_gpu.height; i++) {
        vrd_gpu.framebuffer[i] = color;
    }

    printf("[VRD_GPU] Screen cleared.\n");
}

// Desenha um pixel (x, y)
void vrd_gpu_draw_pixel(int x, int y, unsigned int color) {
    if (!vrd_gpu.initialized) {
        printf("[VRD_GPU] Error: GPU not initialized!\n");
        return;
    }
    if (x < 0 || x >= vrd_gpu.width || y < 0 || y >= vrd_gpu.height) {
        printf("[VRD_GPU] Warning: Pixel out of bounds (%d,%d)\n", x, y);
        return;
    }

    vrd_gpu.framebuffer[y * vrd_gpu.width + x] = color;
}

// Mostra informações da GPU
void vrd_gpu_info() {
    printf("\n=== VRD GPU INFO ===\n");
    printf("Name   : %s\n", vrd_gpu.name);
    printf("Width  : %d\n", vrd_gpu.width);
    printf("Height : %d\n", vrd_gpu.height);
    printf("Status : %s\n", vrd_gpu.initialized ? "Initialized" : "Not initialized");
}

// Finaliza e libera recursos
void vrd_gpu_shutdown() {
    if (vrd_gpu.framebuffer) {
        free(vrd_gpu.framebuffer);
        vrd_gpu.framebuffer = NULL;
    }
    vrd_gpu.initialized = 0;
    printf("[VRD_GPU] Shutdown complete.\n");
}
