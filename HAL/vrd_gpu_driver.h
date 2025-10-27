// File: HAL/vrd_gpu_driver.h
// Virtual Render Device (VRD GPU) driver definitions
// This header defines GPU control macros, command codes and register layout.

#ifndef VRD_GPU_DRIVER_H
#define VRD_GPU_DRIVER_H

#include "../OSheader.hpp"

// ==========================================
// 🔧 DEFINES — GPU Commands
// ==========================================

#define VRD_CMD_INIT        0x01  // Inicializa GPU
#define VRD_CMD_CLEAR       0x02  // Limpa framebuffer
#define VRD_CMD_DRAW_PIXEL  0x03  // Desenha um pixel
#define VRD_CMD_INFO        0x04  // Mostra informações da GPU
#define VRD_CMD_SHUTDOWN    0x05  // Desliga GPU

// ==========================================
// 🎨 CORES BÁSICAS (formato RGB 24 bits)
// ==========================================

#define VRD_COLOR_BLACK   0x000000
#define VRD_COLOR_WHITE   0xFFFFFF
#define VRD_COLOR_RED     0xFF0000
#define VRD_COLOR_GREEN   0x00FF00
#define VRD_COLOR_BLUE    0x0000FF
#define VRD_COLOR_YELLOW  0xFFFF00
#define VRD_COLOR_CYAN    0x00FFFF
#define VRD_COLOR_MAGENTA 0xFF00FF

// ==========================================
// 📊 Estrutura simulada de registradores GPU
// ==========================================

typedef struct {
    unsigned int VRD_STATUS;     // 0 = desligado, 1 = ativo
    unsigned int VRD_WIDTH;
    unsigned int VRD_HEIGHT;
    unsigned int VRD_LAST_CMD;   // último comando executado
} VRD_GPU_REGISTERS;

extern VRD_GPU_REGISTERS vrd_registers;

// ==========================================
// ⚙️ Funções de controle GPU
// ==========================================

void vrd_gpu_send_command(unsigned int cmd, int arg1, int arg2, unsigned int color);

#endif // VRD_GPU_DRIVER_H
