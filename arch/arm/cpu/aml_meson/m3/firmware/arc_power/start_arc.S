    .global _start
;; -- start of program section --------------------------
    .text
;; -- auto-vector space, jump to start of code ---------- 
_start:
    j boot_start
    ; reserved for arm reboot code.
    .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
boot_start:
; Disable Instruction  Cache 
; Disable Data Cache 
; Release power on pins except test_n, which always need pull_up

; Initialize stack pointer registers
  mov  sp, 0x4000;_STACK_END         
  ;mov sp , 0xE000

; Initialise small data pointer registers
;    mov  gp, 0xc1001e00         

; Direct to main entry
		;disable caches
;		lr r0,[0x47]
;		or r0,r0,1
;		sr r0,[0x47]
;		lr r0,[0x11]
;		or r0,r0,1
;		sr r0,[0x11]

		;clear bss segment
		mov r0,0
		mov r1, __bss_start
clear_loop:
		st  r0,[r1]
		add r1,r1,4
		cmp r1,_end
		bne clear_loop
		
    bl      main
    nop

; Jump to memory location where boot_loader is moved in
    b 	.
	nop
	
