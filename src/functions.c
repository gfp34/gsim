#include "functions.h"

#define DEFAULT_STACK_SIZE 8192
#define TEXT_ADDRESS 0x400000
#define DATA_ADDRESS 0x10000000
#define STACK_HIGH_ADDR 0x7fffffff


extern byte* text;
extern byte* data;
extern byte* stack;

extern size_t textSize;
extern size_t dataSize;
extern size_t stackSize;

extern reg registers[];
extern reg pc;
extern reg hi;
extern reg lo;


static byte* getRealAddr(uint32_t progAddr) {
    if(progAddr >= TEXT_ADDRESS && progAddr <= TEXT_ADDRESS + textSize) {
        return &text[progAddr - TEXT_ADDRESS];
    } else if(progAddr >= DATA_ADDRESS && progAddr <= DATA_ADDRESS + dataSize) {
        return &data[progAddr - DATA_ADDRESS];
    } else if(progAddr >= STACK_HIGH_ADDR - stackSize && progAddr <= STACK_HIGH_ADDR) {
        return &stack[STACK_HIGH_ADDR - progAddr];
    } else {
        // Memory does not exist
        return NULL;
    }
}

err_code add(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rs] + registers[rt];
    if((registers[rs] > 0 && registers[rt] > 0 && registers[rd] < 0)
        || (registers[rs] < 0 && registers[rt] < 0 && registers[rd] > 0)) {
        return OVERFLOW;
    } else {
        return SUCCESS;
    }
}

err_code addi(uint8_t rs, uint8_t rt, int16_t imm) {
    registers[rt] = registers[rs] + (reg) imm;
    if((registers[rs] > 0 && imm > 0 && registers[rt] < 0)
       || (registers[rs] < 0 && imm < 0 && registers[rt] > 0)) {
        return OVERFLOW;
    } else {
        return SUCCESS;
    }
}

err_code addiu(uint8_t rs, uint8_t rt, int16_t imm) {
    registers[rt] = registers[rs] + (reg) imm;
    return SUCCESS;
}

err_code addu(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rs] + registers[rt];
    return SUCCESS;
}

err_code and(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rs] & registers[rt];
    return SUCCESS;
}

err_code andi(uint8_t rs, uint8_t rt, int16_t imm) {
    registers[rt] = registers[rs] & ((reg) imm & 0xFFFF); // imm is zero extended
    return SUCCESS;
}

err_code beq(uint8_t rs, uint8_t rt, int16_t offset) {
    if(registers[rs] == registers[rt])
        pc += ((reg) offset) << 2;  // Last 2 00s taken of 16 bit inst offsetreturn SUCCESS;
    return SUCCESS;
}

err_code bne(uint8_t rs, uint8_t rt, int16_t offset) {
    if(registers[rs] != registers[rt])
        pc += ((reg) offset) << 2;  // Last 2 00s taken of 16 bit inst offset
    return SUCCESS;
}

err_code div_(uint8_t rs, uint8_t rt) {
    // TODO Implement overflow detection
    if(registers[rt] == 0) {
        return DIV_BY_ZERO;
    } else {
        lo = registers[rs] / registers[rt];
        hi = registers[rs] % registers[rt];
        return SUCCESS;
    }
}

err_code divu(uint8_t rs, uint8_t rt) {
    if(registers[rt] == 0) {
        return DIV_BY_ZERO;
    } else {
        lo = registers[rs] / registers[rt];
        hi = registers[rs] % registers[rt];
        return SUCCESS;
    }
}

err_code j(uint32_t target) {
    pc = target << 2;  // Last 2 00s taken of 26 bit inst offset
    return JUMPED;
}

err_code jal(uint32_t target) {
    registers[31] = pc + 4;
    pc = target << 2;  // Last 2 00s taken of 26 bit inst offset
    return JUMPED;
}

err_code jalr(uint8_t rs, uint8_t rd) {
    registers[rd] = pc + 4;
    pc = registers[rs];
    return JUMPED;
}

err_code jr(uint8_t rs) {
    pc = registers[rs];
    return JUMPED;
}

err_code lb(uint8_t rs, uint8_t rt, int16_t offset) {
    uint32_t addr = registers[rs] + (reg) offset;
    byte* realAddr = getRealAddr(addr);
    if(realAddr == NULL) {
        return NONEXISTANT_MEMORY;
    } else {
        registers[rt] = (reg) ((int8_t)*realAddr);
        return SUCCESS;
    }
}

err_code lbu(uint8_t rs, uint8_t rt, int16_t offset) {
    uint32_t addr = registers[rs] + (reg) offset;
    byte* realAddr = getRealAddr(addr);
    if(realAddr == NULL) {
        return NONEXISTANT_MEMORY;
    } else {
        registers[rt] = (reg) ((uint8_t)*realAddr);
        return SUCCESS;
    }
}

err_code lh(uint8_t rs, uint8_t rt, int16_t offset) {
    uint32_t addr = registers[rs] + (reg) offset;
    byte* realAddr = getRealAddr(addr);
    if(realAddr == NULL) {
        return NONEXISTANT_MEMORY;
    } else {
        registers[rt] = (reg) ((int16_t)((realAddr[0] << 8) + realAddr[1]));
        return SUCCESS;
    }
}

err_code lhu(uint8_t rs, uint8_t rt, int16_t offset) {
    uint32_t addr = registers[rs] + (reg) offset;
    byte* realAddr = getRealAddr(addr);
    if(realAddr == NULL) {
        return NONEXISTANT_MEMORY;
    } else {
        registers[rt] = (reg) ((uint16_t)((realAddr[0] << 8) + realAddr[1]));
        return SUCCESS;
    }
}

err_code lui(uint8_t rt, int16_t imm) {
    registers[rt] = (((uint32_t) imm) << 16) & 0xFFFF0000;
    return SUCCESS;
}

err_code lw(uint8_t rs, uint8_t rt, int16_t offset) {
    uint32_t addr = registers[rs] + (reg) offset;
    byte* realAddr = getRealAddr(addr);
    if(realAddr == NULL) {
        return NONEXISTANT_MEMORY;
    } else {
        registers[rt] = (reg) ((realAddr[0] << 24) + (realAddr[1] << 16) +
                                    (realAddr[2] << 8) + realAddr[3]);
        return SUCCESS;
    }
}

err_code mfhi(uint8_t rd) {
    registers[rd] = hi;
    return SUCCESS;
}

err_code mthi(uint8_t rs) {
    hi = registers[rs];
    return SUCCESS;
}

err_code mflo(uint8_t rd) {
    registers[rd] = lo;
    return SUCCESS;
}

err_code mtlo(uint8_t rs) {
    lo = registers[rs];
    return SUCCESS;
}

err_code mult(uint8_t rs, uint8_t rt) {
    int64_t tmp = (int64_t)registers[rs] * (int64_t)registers[rt];
    hi = (reg)((tmp >> 32) & 0xFFFFFFFF);
    lo = (reg)(tmp & 0xFFFFFFFF);
    return SUCCESS;
}

err_code multu(uint8_t rs, uint8_t rt) {
    uint64_t tmp = (uint64_t)(uint32_t)registers[rs] * (uint64_t)(uint32_t)registers[rt];
    hi = (reg)((tmp>>32) & 0xFFFFFFFF);
    lo = (reg)(tmp & 0xFFFFFFFF);
    return SUCCESS;
}

err_code nor(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = ~(registers[rs] | registers[rt]);
    return SUCCESS;
}

err_code xor(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rs] ^ registers[rt];
    return SUCCESS;
}

err_code or(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rs] | registers[rt];
    return SUCCESS;
}

err_code ori(uint8_t rs, uint8_t rt, int16_t imm) {
    registers[rt] = registers[rs] | ((uint32_t)imm & 0xFFFF);
    return SUCCESS;
}

err_code sb(uint8_t rs, uint8_t rt, int16_t offset) {
    uint32_t addr = registers[rs] + (reg) offset;
    byte* realAddr = getRealAddr(addr);
    if(realAddr == NULL) {
        return NONEXISTANT_MEMORY;
    } else {
        *realAddr = (byte)registers[rt];
        return SUCCESS;
    }
}

err_code sh(uint8_t rs, uint8_t rt, int16_t offset) {
    uint32_t addr = registers[rs] + (reg) offset;
    byte* realAddr = getRealAddr(addr);
    if(realAddr == NULL) {
        return NONEXISTANT_MEMORY;
    } else {
        realAddr[0] = (byte)(registers[rt] >> 8);
        realAddr[1] = (byte)(registers[rt]);
        return SUCCESS;
    }
}

err_code sw(uint8_t rs, uint8_t rt, int16_t offset) {
    uint32_t addr = registers[rs] + (reg) offset;
    byte* realAddr = getRealAddr(addr);
    if(realAddr == NULL) {
        return NONEXISTANT_MEMORY;
    } else {
        realAddr[0] = (byte)(registers[rt] >> 24);
        realAddr[1] = (byte)(registers[rt] >> 16);
        realAddr[2] = (byte)(registers[rt] >> 8);
        realAddr[3] = (byte)(registers[rt]);
        return SUCCESS;
    }
}

err_code slt(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rs] < registers[rt];
    return SUCCESS;
}

err_code slti(uint8_t rs, uint8_t rt, int16_t imm) {
    registers[rt] = registers[rs] < (reg)imm;
    return SUCCESS;
}

err_code stliu(uint8_t rs, uint8_t rt, int16_t imm) {
    registers[rt] = registers[rs] < (reg)imm;
    return SUCCESS;
}

err_code sltu(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rs] < registers[rt];
    return SUCCESS;
}

err_code sll(uint8_t rt, uint8_t rd, uint8_t shamt) {
    registers[rd] = registers[rt] << shamt;
    return SUCCESS;
}

err_code sllv(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rt] << registers[rs];
    return SUCCESS;
}

err_code srl(uint8_t rt, uint8_t rd, uint8_t shamt) {
    registers[rd] = (uint32_t)registers[rt] >> shamt;
    return SUCCESS;
}

err_code srlv(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = (uint32_t)registers[rt] >> registers[rs];
    return SUCCESS;
}

err_code sra(uint8_t rt, uint8_t rd, uint8_t shamt) {
    registers[rd] = registers[rt] >> shamt;
    return SUCCESS;
}

err_code srav(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rt] >> registers[rs];
    return SUCCESS;
}

err_code sub(uint8_t rs, uint8_t rt, uint8_t rd) {
    // TODO Implement overflow detection
    registers[rd] = registers[rs] - registers[rt];
    return SUCCESS;
}

err_code subu(uint8_t rs, uint8_t rt, uint8_t rd) {
    registers[rd] = registers[rs] - registers[rt];
    return SUCCESS;
}

/**
 * Parameters in $a0 - $a3 ($4 - $7)
 * Code indicating call in $v0 ($2)
 * Return values in $v0 and $v1 ($2 and $3)
 */

err_code syscall() {
    switch(registers[2]) {
        case 1:
            printf("%d", registers[4]);
            return SUCCESS;
        case 4:
            printf("%s", getRealAddr(registers[4]));
            return SUCCESS;
        case 5: {
            char* buf = NULL;
            size_t buflen = 0;
            // Read int
            getline(&buf, &buflen, stdin);
            char* endptr;
            uint32_t in = strtol(buf, &endptr, 10);
            if(endptr == buf) {     // No number inputted
                registers[3] = 0xffffffff;
            } else {
                registers[2] = in;
                registers[3] = 0;
            }
            return SUCCESS;
        }
        case 8: {
            char* buf = (char*) getRealAddr(registers[4]); // Address of buf in str 1
            size_t buflen = registers[5];
            registers[2] = registers[4];
            fgets(buf, buflen, stdin);
            return SUCCESS;
        }
        case 10:
            return EXIT;
        case 11:
            printf("%c", (char) registers[4]);
            return SUCCESS;
        case 17:
            return EXIT;
        default:
            return BAD_SYSCALL;
    }
}
