// File: register/register.h
// Virtual Register Map (VREGMAP)
// Define endereços e valores padrão dos registradores do sistema.
// Este arquivo é usado pelo HAL e pelo kernel.

#ifndef VIRTUAL_REGISTER_H
#define VIRTUAL_REGISTER_H

// =======================================
// 🎮 VRD GPU REGISTERS
// =======================================

// Status e controle
#define REG_GPU_STATUS      0x0001  // 0 = off, 1 = on
#define REG_GPU_COMMAND     0x0002  // último comando
#define REG_GPU_WIDTH       0x0003  // largura do framebuffer
#define REG_GPU_HEIGHT      0x0004  // altura do framebuffer
#define REG_GPU_COLOR       0x0005  // cor ativa
#define REG_GPU_ERROR       0x0006  // código de erro

// =======================================
// 🧠 CPU REGISTERS (simulados)
// =======================================
#define REG_CPU_STATE       0x0100  // estado do processador
#define REG_CPU_MODE        0x0101  // modo atual (user/kernel)
#define REG_CPU_CLOCK       0x0102  // frequência simulada
#define REG_CPU_TEMP        0x0103  // temperatura

// =======================================
// 🧩 MEMORY REGISTERS
// =======================================
#define REG_MEM_SIZE        0x0200  // tamanho total de RAM virtual
#define REG_MEM_USED        0x0201  // uso atual de RAM
#define REG_MEM_BASE_ADDR   0x0202  // endereço base da memória

// =======================================
// ⚡ SYSTEM CONTROL
// =======================================
#define REG_SYS_BOOTFLAG    0x0300  // flag de boot
#define REG_SYS_VERSION     0x0301  // versão do sistema
#define REG_SYS_BUILD_ID    0x0302  // build ID
#define REG_SYS_ERROR_CODE  0x0303  // erro global

// =======================================
// 💾 I/O DEVICE REGISTERS (genéricos)
// =======================================
#define REG_IO_KEYBOARD     0x0400
#define REG_IO_MOUSE        0x0401
#define REG_IO_DISPLAY      0x0402
#define REG_IO_AUDIO        0x0403
#define REG_IO_STORAGE      0x0404

// =======================================
// 🔒 FLAGS E ESTADOS
// =======================================
#define STATE_OFF           0
#define STATE_ON            1
#define MODE_USER           0
#define MODE_KERNEL         1

#define SYS_BOOT_CLEAN      0xAA
#define SYS_BOOT_RECOVERY   0xBB
#define SYS_BOOT_SAFE       0xCC

#endif // VIRTUAL_REGISTER_H
