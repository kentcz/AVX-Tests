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
section .text
BITS 64

	global simple_kernel

simple_kernel:
		push rbp
		mov rbp, rsp

		; arg[0] (rdi) is the address of array
		; arg[1] (rsi) is the int value 

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


		mov rax, 2
inloop:	
		cmp rax, 0
		jle outloop
		dec rax

		;
		; Modify registers
		;
		vaddpd ymm0, ymm0, ymm12
		vaddpd ymm1, ymm1, ymm13
		vaddpd ymm2, ymm2, ymm14
		vaddpd ymm3, ymm3, ymm15
		vaddpd ymm4, ymm4, ymm12
		vaddpd ymm5, ymm5, ymm13
		vaddpd ymm6, ymm6, ymm14
		vaddpd ymm7, ymm7, ymm15
		vaddpd ymm8, ymm8, ymm12
		vaddpd ymm9, ymm9, ymm13
		vaddpd ymm10, ymm10, ymm14
		vaddpd ymm11, ymm11, ymm15

		jmp inloop
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
