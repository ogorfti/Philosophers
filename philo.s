	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_myThreadFun            ## -- Begin function myThreadFun
	.p2align	4, 0x90
_myThreadFun:                           ## @myThreadFun
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$0, -4(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	addl	$1, %ecx
	movl	%ecx, -4(%rbp)
	cmpl	$10000, %eax            ## imm = 0x2710
	jge	LBB0_3
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	_count(%rip), %eax
	addl	$1, %eax
	movl	%eax, _count(%rip)
	jmp	LBB0_1
LBB0_3:
	xorl	%eax, %eax
                                        ## kill: def $rax killed $eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	leaq	_myThreadFun(%rip), %rdx
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	-16(%rbp), %rdi
	movq	%rcx, %rsi
	movq	%rcx, -24(%rbp)         ## 8-byte Spill
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	callq	_pthread_create
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi         ## 8-byte Reload
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	movl	_count(%rip), %esi
	leaq	L_.str(%rip), %rdi
	movl	-28(%rbp), %r8d         ## 4-byte Reload
	movb	%r8b, %r9b
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movb	%r9b, %al
	callq	_printf
	movl	-28(%rbp), %edi         ## 4-byte Reload
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	callq	_exit
	.cfi_endproc
                                        ## -- End function
	.globl	_count                  ## @count
.zerofill __DATA,__common,_count,4,2
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"count : %d\n"


.subsections_via_symbols
