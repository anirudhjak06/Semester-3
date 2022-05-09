	.file	"control.c"
	.text
	.globl	_absdiff
	.def	_absdiff;	.scl	2;	.type	32;	.endef
_absdiff:
LFB0:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	8(%esp), %eax
	cmpl	%eax, %edx
	jle	L2
	subl	%eax, %edx
	movl	%edx, %eax
	ret
L2:
	subl	%edx, %eax
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0"
