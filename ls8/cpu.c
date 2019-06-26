#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

void cpu_ram_read(struct cpu *cpu, int address)
{
  return cpu->ram[address];
}

void cpu_ram_write(struct cpu *cpu, int address, int data)
{
  cpu->ram[address] = data;
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    unsigned char ir = cpu_ram_read(cpu, cpu->pc);
    unsigned char operand1 = cpu_ram_read(cpu, cpu->pc+1);
    unsigned char operand2 = cpu_ram_read(cpu, cpu->pc+2);
    int num_increments = (ir >> 6) + 1;
    int v;
    int reg;
    switch (ir) {
      case HLT:
        running = 0;
        break;
      case LDI:
        reg = operand1;
        v = operand2;
        cpu->registers[reg] = v;
        break;
      case PRN:
        reg = operand1;
        printf("%d", cpu->registers[reg]);
        break;
      default:
        printf("Unknown instruction %02x at %02x\n", ir, pc);
        exit(1);
      
    }
    pc += num_increments;
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;
  cpu->notice = 0b00000000;
}
