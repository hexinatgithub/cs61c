.data
shouldben1:	.asciiz "Should be -1, and firstposshift and firstposmask returned: "
shouldbe0:	.asciiz "Should be 0 , and firstposshift and firstposmask returned: "
shouldbe16:	.asciiz "Should be 16, and firstposshift and firstposmask returned: "
shouldbe31:	.asciiz "Should be 31, and firstposshift and firstposmask returned: "

.text
main:
	la	$a0, shouldbe31
	jal	print_str
	lui	$a0, 0x8000	# should be 31
	jal	first1posshift
	move	$a0, $v0
	jal	print_int
	jal	print_space

	lui	$a0, 0x8000
	jal	first1posmask
	move	$a0, $v0
	jal	print_int
	jal	print_newline

	la	$a0, shouldbe16
	jal	print_str
	lui	$a0, 0x0001	# should be 16
	jal	first1posshift
	move	$a0, $v0
	jal	print_int
	jal	print_space

	lui	$a0, 0x0001
	jal	first1posmask
	move	$a0, $v0
	jal	print_int
	jal	print_newline

	la	$a0, shouldbe0
	jal	print_str
	li	$a0, 1		# should be 0
	jal	first1posshift
	move	$a0, $v0
	jal	print_int
	jal	print_space

	li	$a0, 1
	jal	first1posmask
	move	$a0, $v0
	jal	print_int
	jal	print_newline

	la	$a0, shouldben1
	jal	print_str
	move	$a0, $0		# should be -1
	jal	first1posshift
	move	$a0, $v0
	jal	print_int
	jal	print_space

	move	$a0, $0
	jal	first1posmask
	move	$a0, $v0
	jal	print_int
	jal	print_newline

	li	$v0, 10
	syscall

first1posshift:
	### YOUR CODE HERE ###
	addiu	$sp, $sp, -4
	sw	$ra, 0($sp)

	beq	$a0, $0, L2	# if a0 == 0
	slti	$t0, $a0, 0
	bne	$t0, $0, L3	# $a0 < 0
	la	$t0, first1posshift
L1:
	sll	$a0, $a0, 1
	jalr	$t0
	subi	$v0, $v0, 1
	j	endfirst1pos
L2:
	addi	$v0, $0, -1	# return -1
	j	endfirst1pos
L3:
	addi	$v0, $0, 31
endfirst1pos:
	lw	$ra, 0($sp)
	addiu	$sp, $sp, 4
	jr	$ra

first1posmask:
	### YOUR CODE HERE ###
	addiu	$sp, $sp, -4
	sw	$ra, 0($sp)

	beq	$a0, $0, L2		# if a0 == 0
	ori	$t0, $a0, 0x80000000
	beq	$t0, 0x80000000, L3	# $a0 < 0
	la	$t0, first1posmask
	j	L1

print_int:
	move	$a0, $v0
	li	$v0, 1
	syscall
	jr	$ra

print_str:
	li	$v0, 4
	syscall
	jr	$ra

print_space:
	li	$a0, ' '
	li	$v0, 11
	syscall
	jr	$ra

print_newline:
	li	$a0, '\n'
	li	$v0, 11
	syscall
	jr	$ra
