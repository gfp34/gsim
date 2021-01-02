#ifndef GSIM_SIMULATOR_H
#define GSIM_SIMULATOR_H

#include <stdint.h>

typedef enum err_code {
    SUCCESS,
    JUMPED,
    OVERFLOW,
    DIV_BY_ZERO,
    NONEXISTANT_MEMORY,
    BAD_SYSCALL,
    FUNC_NOT_IMPLEMENTED,
    BREAK,
    UNALIGNED_INST,
    EXIT
} err_code;

#include "functions.h"

#define NUM_REGISTERS 32  // Total number of registers

/*
MIPS registers and conventional usages
$0			$zero		Hard-wired to 0
$1			$at			Reserved for pseudo-instructions
$2 - $3		$v0, $v1	Return values from functions
$4 - $7		$a0 - $a3	Arguments to functions - not preserved by subprograms
$8 - $15	$t0 - $t7	Temporary data, not preserved by subprograms
$16 - $23	$s0 - $s7	Saved registers, preserved by subprograms
$24 - $25	$t8 - $t9	More temporary registers, not preserved by subprograms
$26 - $27	$k0 - $k1	Reserved for kernel. Do not use.
$28			$gp			Global Area Pointer (base of global data segment)
$29			$sp			Stack Pointer
$30			$fp			Frame Pointer
$31			$ra			Return Address

Other registers
$pc 	Program Counter
$hi 	Higher order 16 bits used in multiplication
$lo		Lower order 16 bits used in multiplication
*/

typedef uint8_t byte;
typedef int32_t reg;
typedef uint32_t inst;

/**
 * Allocate memory for text, data and stack segments.
 * Also initializes registers to their correct values, and puts command
 * line arguments into the stack segment.
 * @param execFile - pointer to byte array of the inputted
 *                      executable file
 * @param argc - Number of arguments
 * @param argv - Pointer array to arguments
 */
void sim_init(byte* execFile, int argc, char* argv[]);


/**
 * Executes instruction pointed to by the pc register, and updates
 * the such register to point to the next appropriate instruction.
 * Also keeps track of error codes returned by each function and stops
 * the running if necessary.
 */
void sim_run();

/**
 * Free allocated memory after execution has ended.
 */
void sim_exit();

#endif // GSIM_SIMULATOR_H
