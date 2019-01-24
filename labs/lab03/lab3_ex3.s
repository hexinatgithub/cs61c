	.file	1 "lab3_ex3.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls
	.option	pic0
	.section	.text.startup,"ax",@progbits
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$2,%hi(source) # $2 source high
	lw	$4,%lo(source)($2) # $4 = tmp = source[0]
	nop
	beq	$4,$0,$L6 # tmp != 0
	nop

	lui	$3,%hi(dest) # $3 dest high
	addiu	$3,$3,%lo(dest) # $3 = dest
	addiu	$2,$2,%lo(source) # $2 = source
$L3:
	sw	$4,0($3) # dest[k] = tmp
	lw	$4,4($2) tmp = source[k + 1]
	addiu	$3,$3,4 # dest++
	addiu	$2,$2,4 # source++
	bne	$4,$0,$L3 # tmp != 0
	nop

$L6:
	move	$2,$0
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

	.comm	dest,40,4
	.globl	source
	.data
	.align	2
	.type	source, @object
	.size	source, 28
source:
	.word	3
	.word	1
	.word	4
	.word	1
	.word	5
	.word	9
	.word	0
	.ident	"GCC: (crosstool-NG ) 6.3.0"
