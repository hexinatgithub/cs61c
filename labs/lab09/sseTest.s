	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.intel_syntax noprefix
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3               ## -- Begin function main
LCPI0_0:
	.quad	4607182418800017408     ## double 1
LCPI0_1:
	.quad	4613937818241073152     ## double 3
LCPI0_2:
	.quad	4618441417868443648     ## double 6
LCPI0_3:
	.quad	4616189618054758400     ## double 4
LCPI0_4:
	.quad	4611686018427387904     ## double 2
LCPI0_5:
	.quad	4620693217682128896     ## double 8
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	# for i = 0
	lea	rdi, [rip + L_.str]
	movsd	xmm0, qword ptr [rip + LCPI0_0] ## xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + LCPI0_1] ## xmm1 = mem[0],zero
	movsd	xmm5, qword ptr [rip + LCPI0_2] ## xmm5 = mem[0],zero
	xorps	xmm3, xmm3
	mov	al, 6
	movaps	xmm2, xmm1
	movaps	xmm4, xmm1
	call	_printf
	# for i = 1
	lea	rdi, [rip + L_.str.1]
	movsd	xmm1, qword ptr [rip + LCPI0_3] ## xmm1 = mem[0],zero
	movsd	xmm0, qword ptr [rip + LCPI0_4] ## xmm0 = mem[0],zero
	movsd	xmm5, qword ptr [rip + LCPI0_5] ## xmm5 = mem[0],zero
	xorps	xmm2, xmm2
	mov	al, 6
	movaps	xmm3, xmm0
	movsd	xmm4, qword ptr [rip + LCPI0_2] ## xmm4 = mem[0],zero
	call	_printf
	xor	eax, eax
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"|%g %g| * |%g %g| = |%g %g|\n"

L_.str.1:                               ## @.str.1
	.asciz	"|%g %g|   |%g %g|   |%g %g|\n"


.subsections_via_symbols
