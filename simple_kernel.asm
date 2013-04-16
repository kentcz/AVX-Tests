; --------------------------------------------------------------------------
; simple_kernel.asm
;
; NASM implementation of a function that returns the sum of all the elements
; in a floating-point array.  The function has prototype:
;
;   double sum(double[] array, int length)
; --------------------------------------------------------------------------
section .data
msg:	db	"Hello World\n",

mypi1:	dq	3.14159
mypi2:	dq	3.14159
mypi3:	dq	3.14159
mypi4:	dq	3.141590

vone1:	dq	1.0
vone2:	dq	1.0
vone3:	dq	1.0
vone4:	dq	1.0

msk1:	dq	0x800fffffffffffff
msk2:	dq	0x800fffffffffffff
msk3:	dq	0x800fffffffffffff
msk4:	dq	0x800fffffffffffff


section .text
BITS 64

	global simple_kernel

simple_kernel:
		push rbp
		mov rbp, rsp

		; arg[0] (rdi) is the address of array
		; arg[1] (rsi) is the number of iterations 

		;
		; Fill the AVX registers
		;
		vmovupd ymm0, [rdi]
		vmovupd ymm1, [rdi + 32]
		vmovupd ymm2, [rdi + 64]
		vmovupd ymm3, [rdi + 96]
		vmovupd ymm4, [rdi + 128]
		vmovupd ymm5, [rdi + 160]
		vmovupd ymm6, [rdi + 192]
		vmovupd ymm7, [rdi + 224]
		vmovupd ymm8, [rdi + 256]
		vmovupd ymm9, [rdi + 288]
		vmovupd ymm10, [rdi + 320]
		vmovupd ymm11, [rdi + 352]
		vmovupd ymm12, [rdi + 384]
		vmovupd ymm13, [rdi + 416]
		vmovupd ymm14, [rdi + 448]
		vmovupd ymm15, [rdi + 480]



outloop:
		cmp rsi, 0
		jle done
		dec rsi


		mov rax, 1000
inloop:	
		cmp rax, 0
		jle e_outloop
		dec rax

		;
		; Modify registers
		;
		;vaddpd ymm0, ymm0, ymm12
		;vaddpd ymm1, ymm1, ymm13
		;vaddpd ymm2, ymm2, ymm14
		;vaddpd ymm3, ymm3, ymm15
		;vaddpd ymm4, ymm4, ymm12
		;vaddpd ymm5, ymm5, ymm13
		;vaddpd ymm6, ymm6, ymm14
		;vaddpd ymm7, ymm7, ymm15
		;vaddpd ymm8, ymm8, ymm12
		;vaddpd ymm9, ymm9, ymm13
		;vaddpd ymm10, ymm10, ymm14
		;vaddpd ymm11, ymm11, ymm15

		vmulpd ymm3, ymm3, ymm15
		vmulpd ymm5, ymm5, ymm13
		vmulpd ymm7, ymm7, ymm15
		vmulpd ymm9, ymm9, ymm13
		vmulpd ymm11, ymm11, ymm15
		vmulpd ymm0, ymm0, ymm13
		vaddpd ymm2, ymm2, ymm14
		vaddpd ymm4, ymm4, ymm12
		vaddpd ymm6, ymm6, ymm14
		vaddpd ymm8, ymm8, ymm12
		vaddpd ymm10, ymm10, ymm14
		vaddpd ymm1, ymm1, ymm12
		vaddpd ymm3, ymm3, ymm12
		vaddpd ymm5, ymm5, ymm14
		vaddpd ymm7, ymm7, ymm12
		vaddpd ymm9, ymm9, ymm14
		vaddpd ymm11, ymm11, ymm12
		vaddpd ymm0, ymm0, ymm14
		vmulpd ymm2, ymm2, ymm13
		vmulpd ymm4, ymm4, ymm15
		vmulpd ymm6, ymm6, ymm13
		vmulpd ymm8, ymm8, ymm15
		vmulpd ymm10, ymm10, ymm13
		vmulpd ymm1, ymm1, ymm15
		vmulpd ymm3, ymm3, ymm15
		vmulpd ymm5, ymm5, ymm13
		vmulpd ymm7, ymm7, ymm15
		vmulpd ymm9, ymm9, ymm13
		vmulpd ymm11, ymm11, ymm15
		vmulpd ymm0, ymm0, ymm13
		vaddpd ymm2, ymm2, ymm14
		vaddpd ymm4, ymm4, ymm12
		vaddpd ymm6, ymm6, ymm14
		vaddpd ymm8, ymm8, ymm12
		vaddpd ymm10, ymm10, ymm14
		vaddpd ymm1, ymm1, ymm12
		vaddpd ymm3, ymm3, ymm12
		vaddpd ymm5, ymm5, ymm14
		vaddpd ymm7, ymm7, ymm12
		vaddpd ymm9, ymm9, ymm14
		vaddpd ymm11, ymm11, ymm12
		vaddpd ymm0, ymm0, ymm14
		vmulpd ymm2, ymm2, ymm13
		vmulpd ymm4, ymm4, ymm15
		vmulpd ymm6, ymm6, ymm13
		vmulpd ymm8, ymm8, ymm15
		vmulpd ymm10, ymm10, ymm13
		vmulpd ymm1, ymm1, ymm15




		jmp inloop


e_outloop:

		;
		; Normalize
		;
		vmovupd ymm14, [msk1]			; Load MASK into ymm14
		vmovupd ymm15, [vone1]			; Load VONE into ymm15
				
		;vandpd ymm0, ymm0, ymm14
		;vandpd ymm1, ymm1, ymm14
		;vandpd ymm2, ymm2, ymm14
		;vandpd ymm3, ymm3, ymm14
		;vandpd ymm4, ymm4, ymm14
		;vandpd ymm5, ymm5, ymm14
		;vandpd ymm6, ymm6, ymm14
		;vandpd ymm7, ymm7, ymm14
		;vandpd ymm8, ymm8, ymm14
		;vandpd ymm9, ymm9, ymm14
		;vandpd ymm10, ymm10, ymm14
		;vandpd ymm11, ymm11, ymm14

		;vorpd ymm0, ymm0, ymm15
		;vorpd ymm1, ymm1, ymm15
		;vorpd ymm2, ymm2, ymm15
		;vorpd ymm3, ymm3, ymm15
		;vorpd ymm4, ymm4, ymm15
		;vorpd ymm5, ymm5, ymm15
		;vorpd ymm6, ymm6, ymm15
		;vorpd ymm7, ymm7, ymm15
		;vorpd ymm8, ymm8, ymm15
		;vorpd ymm9, ymm9, ymm15
		;vorpd ymm10, ymm10, ymm15
		;vorpd ymm11, ymm11, ymm15

		vmovupd ymm14, [rdi + 448]			; Reload ymm14 from rdi[14]
		vmovupd ymm15, [rdi + 480]			; Reload ymm15 from rdi[15]

		;vmovupd ymm15, [mypi1]				; Load PI into ymm15


		jmp outloop

		;mov rax, 0
		;cmp rsi, 65 						; jump if rsp <= 0
		;jle done
		;mov rax, rsi
done:
		;
		; Writeback
		;
		vmovupd [rdi], ymm0
		vmovupd [rdi + 32], ymm1
		vmovupd [rdi + 64], ymm2
		vmovupd [rdi + 96], ymm3
		vmovupd [rdi + 128], ymm4
		vmovupd [rdi + 160], ymm5
		vmovupd [rdi + 192], ymm6
		vmovupd [rdi + 224], ymm7
		vmovupd [rdi + 256], ymm8
		vmovupd [rdi + 288], ymm9
		vmovupd [rdi + 320], ymm10
		vmovupd [rdi + 352], ymm11
		vmovupd [rdi + 384], ymm12
		vmovupd [rdi + 416], ymm13
		vmovupd [rdi + 448], ymm14
		vmovupd [rdi + 480], ymm15

		vzeroall 						; shutoff AVX unit

		pop rbp							; restore stack
		ret								; return
