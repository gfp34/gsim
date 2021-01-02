#include <stdlib.h>
#include <string.h>

#include "simulator.h"

#define PC_INIT_LOC 0x8
#define TEXT_SIZE_LOC 0xc
#define DATA_SIZE_LOC 0x14
#define TEXT_START_LOC 0x34
#define STACK_HIGH_ADDR 0x7fffffff
#define DEFAULT_STACK_SIZE 8192
#define TEXT_ADDRESS 0x400000
#define DATA_ADDRESS 0x10000000
 
byte* text;
byte* data;
byte* stack;

size_t textSize;
size_t dataSize;
size_t stackSize;

reg registers[NUM_REGISTERS];
reg pc;
reg hi; 
reg lo;


static unsigned int bintoint(byte* src) {
	return (src[0] << 24) + (src[1] << 16) +
			(src[2] << 8) + src[3];
}

static void inttobin(byte* dest, unsigned int i) {
    dest[0] = i >> 24 & 0xFF;
    dest[1] = i >> 16 & 0xFF;
    dest[2] = i >> 8 & 0xFF;
    dest[3] = i & 0xFF;
}


void sim_init(byte* execFile, int argc, char* argv[]) {
	// Get location size of text segment (amount of instructions)
    textSize = bintoint(&execFile[TEXT_SIZE_LOC]);
	text = malloc(textSize);
	// Copy text region of file into text array of instuctions
	memcpy(text, &execFile[TEXT_START_LOC], textSize);
	
	// Get location size of data segment (number of bytes)
	unsigned int dataLoc = TEXT_START_LOC + textSize;
    dataSize = bintoint(&execFile[DATA_SIZE_LOC]);
	data = malloc(dataSize);
	// Copy data region of file into data array
	memcpy(data, &execFile[dataLoc], dataSize);

	// Create stack segment
	stackSize = DEFAULT_STACK_SIZE;
    stack = calloc(stackSize, sizeof(byte));
	// Set top of stack to be the command line arguments
	unsigned char* sp = stack;
    for(int i=argc-1; i>=1; i--) {
        strcpy((char*) sp, argv[i]);
        sp += strlen(argv[i]) + 1;
    }
    // Add padding if needed to make pointer 16 bit aligned
    unsigned int argsLen = sp - stack;
    unsigned int paddingLen = (((argsLen-1) | 15) + 1);
    sp = stack + paddingLen;


    // Set next words to be address of first args, address of padding, and the number of arguments
    inttobin(sp, STACK_HIGH_ADDR - argsLen);
    sp += sizeof(uint32_t);
    inttobin(sp, STACK_HIGH_ADDR - paddingLen);
    sp += sizeof(uint32_t);
    inttobin(sp, argc - 1);
    sp += sizeof(uint32_t);

	// Get pc init value and set $pc to it
	// Set $sp to its init value
	// Set all other registers to 0
	pc = bintoint(&execFile[PC_INIT_LOC]);
	for (int i=0; i<NUM_REGISTERS; i++) {
        registers[i] = 0;
    }
	registers[29] = STACK_HIGH_ADDR - (sp - stack);
	hi = 0;
	lo = 0;  	
}

err_code exec_func(inst current_inst) {
    uint8_t opcode = current_inst >> 26 & 0x3F;
    uint8_t rs = current_inst >> 21 & 0x1F;
    uint8_t rt = current_inst >> 16 & 0x1F;
    err_code err = SUCCESS;
    if(pc % 4 != 0) {
        return UNALIGNED_INST;
    }

    if (opcode == 0) {
        // R type instructions
        uint8_t rd = current_inst >> 11 & 0x1F;
        uint8_t shamt = current_inst >> 6 & 0x1F;
        uint8_t function = current_inst & 0x3F;
        switch (function) {
            case 0:
                err = sll(rt, rd, shamt);
                break;
            case 2:
                err = srl(rt, rd, shamt);
                break;
            case 3:
                err = sra(rt, rd, shamt);
                break;
            case 4:
                err = sllv(rs, rt, rd);
                break;
            case 6:
                err = srlv(rs, rt, rd);
                break;
            case 7:
                err = srav(rs, rt, rd);
                break;
            case 8:
                err = jr(rs);
                break;
            case 9:
                err = jalr(rs, rd);
                break;
                // 10 movz?
                // 11 movn?
            case 12:
                err = syscall();
                break;
            case 13:
                err = BREAK;
                break;
                // 15 sync?
            case 16:
                err = mfhi(rd);
                break;
            case 17:
                err = mthi(rs);
                break;
            case 18:
                err = mflo(rd);
                break;
            case 19:
                err = mtlo(rs);
                break;
            case 24:
                err = mult(rs, rt);
                break;
            case 25:
                err = multu(rs, rt);
                break;
            case 26:
                err = div_(rs, rt);
                break;
            case 27:
                err = divu(rs, rt);
                break;
            case 32:
                add(rs, rt, rd);
                break;
            case 33:
                err = addu(rs, rt, rd);
                break;
            case 34:
                err = sub(rs, rt, rd);
                break;
            case 35:
                err = subu(rs, rt, rd);
                break;
            case 36:
                err = and(rs, rt, rd);
                break;
            case 37:
                err = or(rs, rt, rd);
                break;
            case 38:
                err = xor(rs, rt, rd);
                break;
            case 39:
                err = nor(rs, rt, rd);
                break;
            case 42:
                err = slt(rs, rt, rd);
                break;
            case 43:
                err = sltu(rs, rt, rd);
                break;
                // 48 tge??
                // ... bunch of ones that start with t
            default:
                err = FUNC_NOT_IMPLEMENTED;
                break;
        }
    } else if (opcode == 2 || opcode == 3) {
        // J type instructions
        uint32_t target = current_inst & 0x3FFFFFF;
        switch (opcode) {
            case 2:
                err = j(target);
                break;
            case 3:
                err = jal(target);
                break;
        }
    } else {
        // I type instructions
        int16_t imm = current_inst & 0xFFFF;
        switch (opcode) {
            case 4:
                err = beq(rs, rt, imm);
                break;
            case 5:
                err = bne(rs, rt, imm);
                break;
                // 6 blez
                // 7 bgtz
            case 8:
                err = addi(rs, rt, imm);
                break;
            case 9:
                err = addiu(rs, rt, imm);
                break;
            case 10:
                err = slti(rs, rt, imm);
                break;
            case 11:
                err = stliu(rs, rt, imm);
                break;
            case 12:
                err = andi(rs, rt, imm);
                break;
            case 13:
                err = ori(rs, rt, imm);
                break;
                // 14 xori
            case 15:
                err = lui(rt, imm);
                break;
                // 20 - 23 b stuff?
            case 32:
                err = lb(rs, rt, imm);
                break;
            case 33:
                err = lh(rs, rt, imm);
                break;
                // 34 lwl
            case 35:
                err = lw(rs, rt, imm);
                break;
            case 36:
                err = lbu(rs, rt, imm);
                break;
            case 37:
                err = lhu(rs, rt, imm);
                break;
                // 38 lwr (maybe lw reverse?)
            case 40:
                err = sb(rs, rt, imm);
                break;
            case 41:
                err = sh(rs, rt, imm);
                break;
                // 42 swl?
            case 43:
                err = sw(rs, rt, imm);
                break;
                // 46 swr
                // rest are likely cache functions
            default:
                err = FUNC_NOT_IMPLEMENTED;
                break;
        }
    }
    return err;
}

void sim_run() {
    err_code err;
	do {
        inst current_inst = bintoint(&text[(pc - TEXT_ADDRESS)]);
//        printf("pc=0x%X;\t%08X\n", pc, current_inst);
        err = exec_func(current_inst);
        if(err != JUMPED) {
            pc += 4;
        }
	} while(err == SUCCESS || err == OVERFLOW || err == JUMPED);

    switch (err) {
        case DIV_BY_ZERO:
            fprintf(stderr, "Divide by zero error. pc=0x%X", pc);
            break;
        case NONEXISTANT_MEMORY:
            fprintf(stderr, "Illegal memory address. pc=0x%X", pc);
            break;
        case BAD_SYSCALL:
            fprintf(stderr, "Syscall code %d not implemented. pc=0x%X", registers[2], pc);
            break;
        case FUNC_NOT_IMPLEMENTED:
            fprintf(stderr, "Function not implemented. pc=0x%X", pc);
            break;
        case BREAK:
            fprintf(stderr, "Break function called. pc=0x%X", pc);
            break;
        case UNALIGNED_INST:
            fprintf(stderr, "Instrunction call not aligned on work address. pc=0x%X", pc);
            break;
        default:
            break;
    }
}

void sim_exit() {
    free(text);
    free(data);
    free(stack);
}
 
