#ifndef GSIM_FUNCTIONS_H
#define GSIM_FUNCTIONS_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "simulator.h"

extern int getline(char **, size_t *, FILE *);


/**
 * Instruction encodings by type:
 * R Type - 000000ss sssttttt dddddaaa aaffffff
 * I Type - ooooooss sssttttt iiiiiiii iiiiiiii
 * J Type - ooooooii iiiiiiii iiiiiiii iiiiiiii
 *
 */


/**
 * Function - mnemonic
 * X Type
 * Opcode: 0x
 * Function: 0x
 */


/**
 * Add - add
 * R Type
 * Opcode: 0x00
 * Function: 0x20
 */
err_code add(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Add Immediate - addi
 * I Type
 * Opcode: 0x08
 * Function: NA
 */
err_code addi(uint8_t rs, uint8_t rt, int16_t imm);


/**
 * Add Unsigned Immediate - addiu
 * I Type
 * Opcode: 0x09
 * Function: NA
 */
err_code addiu(uint8_t rs, uint8_t rt, int16_t imm);


/**
 * Add Unsigned - addu
 * R Type
 * Opcode: 0x00
 * Function: 0x21
 */
err_code addu(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Bitwise AND - and
 * R Type
 * Opcode: 0x00
 * Function: 0x24
 */
err_code and(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Bitwise AND Immediate - andi
 * I Type
 * Opcode: 0x0C
 * Function: NA
 */
err_code andi(uint8_t rs, uint8_t rt, int16_t imm);


/**
 * Branch if Equal - beq
 * I Type
 * Opcode: 0x04
 * Function: NA
 */
err_code beq(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Branch if Less Than or Equal to Zero - blez
 * I Type
 * Opcode: 0x06
 * Function: NA
 */


/**
 * Branch if Not Equal - bne
 * I Type
 * Opcode: 0x05
 * Function: NA
 */
err_code bne(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Branch on Greater Than Zero - bgtz
 * I Type
 * Opcode: 0x07
 * Function: NA
 */


/**
 * Divide - div
 * R Type
 * Opcode: 0x00
 * Function: 0x1A
 */
err_code div_(uint8_t rs, uint8_t rt);


/**
 * Unsigned Divide - divu
 * R Type
 * Opcode: 0x00
 * Function: 0x1B
 */
err_code divu(uint8_t rs, uint8_t rt);


/**
 * Jump to Address - j
 * J Type
 * Opcode: 0x02
 * Function: NA
 */
err_code j(uint32_t target);


/**
 * Jump and Link - jal
 * J Type
 * Opcode: 0x03
 * Function: NA
 */
err_code jal(uint32_t target);


/**
 * Jump and Link Register - jalr
 * R Type
 * Opcode: 0x00
 * Function: 0x09
 */
err_code jalr(uint8_t rs, uint8_t rd);


/**
 * Jump to Address in Register - jr
 * R Type
 * Opcode: 0x00
 * Function: 0x08
 */
err_code jr(uint8_t rs);


/**
 * Load Byte - lb
 * I Type
 * Opcode: 0x20
 * Function: NA
 */
err_code lb(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Load Byte Unsigned - lbu
 * I Type
 * Opcode: 0x24
 * Function: NA
 */
err_code lbu(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Load Halfword - lh
 * I Type
 * Opcode: 0x21
 * Function: NA
 */
err_code lh(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Load Halfword Unsigned - lhu
 * I Type
 * Opcode: 0x25
 * Function: NA
 */
err_code lhu(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Load Upper Immediate - lui
 * I Type
 * Opcode: 0x0F
 * Function: NA
 */
err_code lui(uint8_t rt, int16_t imm);


/**
 * Load Word - lw
 * I Type
 * Opcode: 0x23
 * Function: NA
 */
err_code lw(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Move from HI Register - mfhi
 * R Type
 * Opcode: 0x00
 * Function: 0x10
 */
err_code mfhi(uint8_t rd);


/**
 * Move to HI Register - mthi
 * R Type
 * Opcode: 0x00
 * Function: 0x11
 */
err_code mthi(uint8_t rs);


/**
 * Move from LO Register - mflo
 * R Type
 * Opcode: 0x00
 * Function: 0x12
 */
err_code mflo(uint8_t rd);


/**
 * Move to LO Register - mtlo
 * R Type
 * Opcode: 0x00
 * Function: 0x13
 */
err_code mtlo(uint8_t rs);


/**
 * Multiply - mult
 * R Type
 * Opcode: 0x00
 * Function: 0x18
 */
err_code mult(uint8_t rs, uint8_t rt);


/**
 * Unsigned Multiply - multu
 * R Type
 * Opcode: 0x00
 * Function: 0x19
 */
err_code multu(uint8_t rs, uint8_t rt);


/**
 * Bitwise NOR (NOT-OR) - nor
 * R Type
 * Opcode: 0x00
 * Function: 0x27
 */
err_code nor(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Bitwise XOR (Exclusive-OR) - xor
 * R Type
 * Opcode: 0x00
 * Function: 0x26
 */
err_code xor(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Bitwise OR - or
 * R Type
 * Opcode: 0x00
 * Function: 0x25
 */
err_code or(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Bitwise OR Immediate - ori
 * I Type
 * Opcode: 0x0D
 * Function: NA
 */
err_code ori(uint8_t rs, uint8_t rt, int16_t imm);


/**
 * Store Byte - sb
 * I Type
 * Opcode: 0x28
 * Function: NA
 */
err_code sb(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Store Halfword - sh
 * I Type
 * Opcode: 0x29
 * Function: NA
 */
err_code sh(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Store Word - sw
 * I Type
 * Opcode: 0x2B
 * Function: NA
 */
err_code sw(uint8_t rs, uint8_t rt, int16_t offset);


/**
 * Set to 1 if Less Than - slt
 * R Type
 * Opcode: 0x00
 * Function: 0x2A
 */
err_code slt(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Set to 1 if Less Than Immediate - slti
 * I Type
 * Opcode: 0x0A
 * Function: NA
 */
err_code slti(uint8_t rs, uint8_t rt, int16_t imm);


/**
 * Set to 1 if Less Than Unsigned Immediate - sltiu
 * I Type
 * Opcode: 0x0B
 * Function: NA
 */
err_code stliu(uint8_t rs, uint8_t rt, int16_t imm);


/**
 * Set to 1 if Less Than Unsigned - sltu
 * R Type
 * Opcode: 0x00
 * Function: 0x2B
 */
err_code sltu(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Logical Shift Left - sll
 * R Type
 * Opcode: 0x00
 * Function: 0x00
 */
err_code sll(uint8_t rt, uint8_t rd, uint8_t shamt);


/**
 * Logical Shift Left Varible - sllv
 * R Type
 * Opcode: 0x00
 * Function: 0x04
 */
err_code sllv(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Logical Shift Right (0-extended) - srl
 * R Type
 * Opcode: 0x00
 * Function: 0x02
 */
err_code srl(uint8_t rt, uint8_t rd, uint8_t shamt);


/**
 * Logical Shift Right (0-extended) Variable - srlv
 * R Type
 * Opcode: 0x00
 * Function: 0x06
 */
err_code srlv(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Arithmetic Shift Right (sign-extended) - sra
 * R Type
 * Opcode: 0x00
 * Function: 0x03
 */
err_code sra(uint8_t rt, uint8_t rd, uint8_t shamt);


/**
 * Arithmetic Shift Right (sign-extended) Variable - srav
 * R Type
 * Opcode: 0x00
 * Function: 0x07
 */
err_code srav(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Subtract - sub
 * R Type
 * Opcode: 0x00
 * Function: 0x22
 */
err_code sub(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * Unsigned Subtract - subu
 * R Type
 * Opcode: 0x00
 * Function: 0x23
 */
err_code subu(uint8_t rs, uint8_t rt, uint8_t rd);


/**
 * System call parameters are placed in the argument registers (a0 through a3);
 * the code indicating which system call is being made is placed in register v0.
 * Return values are found in v0 and v1.
 *
 * Code	Prototype	            Function
 * 1	print_int(num)	        Print the integer in a0 to the standard output.
 * 4	print_string(buf)	    Print the NUL-terminated character string whose address is in a0 to the standard output.
 * 5	read_int()	            Reads an entire line of input (including the trailing end-of-line sequence);
 *                                  returns in v0 the converted integer found at the beginning of the line.
 *                                  On success (i.e., an integer was found at the beginning of the input line), a
 *                                  zero is returned in v1; otherwise (the line did not begin with an integer, no data
 *                                  was available, etc.), a non-zero value is returned in v1.
 * 8	read_string(buf,len)	Read a line of input from the standard input, placing it in the buffer whose
 *                                  address (buf) was supplied in a0 with a trailing NUL character. The size of the
 *                                  buffer (len) is supplied in a1; no more than len-1 characters will be read into
 *                                  the buffer, to ensure that there is room for the trailing NUL character. If the
 *                                  input line is shorter than len-1 characters, the entire line (including the
 *                                  trailing newline) will be placed in the buffer. If the input line is longer than
 *                                  len-1 characters, only that many characters are read, and the remaining characters
 *                                  will be read by the next system call. On success, the buffer address is returned
 *                                  in v0; otherwise (e.g., no data was available, or some other input error occurred),
 *                                  a value of zero is returned in v0.
 * 10	exit()	                Terminates the program being simulated and exits from the simulator.
 * 11	print_char(char)	    Prints the ASCII character found in the lowest byte of a0 to the standard output.
 * 12	read_char()	            Reads one character from the standard input, and returns it in v0
 *                                  (right-justified and zero-filled).
 * 13	open(name,flags,mode)	This is the standard UNIX open() system call. name is the address of a NUL-terminated
 *                                  character string specifying the path name of the file to be opened; flags
 *                                  specifies how the file is to be opened; and mode provides a permission mask to
 *                                  be used if the file is being opened for output and must be created. (See the
 *                                  open(2) manual page for full details.) Returns a file descriptor in v0 on success,
 *                                  or a -1 on error.
 * 14	read(fd,buf,len)	    This is the standard UNIX read() system call. fd is the file descriptor to be read
 * from; buf is the address of a character buffer into which data is to be read; and len is the size of the buffer,
 * in bytes. Returns a byte count in v0 (0 indicates end-of-file), or -1 on error.
 * 15	write(fd,buf,len)	    This is the standard UNIX write() system call. fd is the file descriptor to be
 *                                  written to; buf is the address of a character buffer from which data is to be
 *                                  written; and len is the size of the buffer, in bytes. Returns a byte count in
 *                                  v0, or -1 on error.
 * 16	close(fd)	            This is the standard UNIX close() system call.
 *                                  fd is the file descriptor which is to be closed.
 * 17	exit2(code)	            This is the standard UNIX exit() system call. The code in
 *                                  register a0 is used as the termination status when the simulator itself exits.
 */
err_code syscall();

#endif //GSIM_FUNCTIONS_H
