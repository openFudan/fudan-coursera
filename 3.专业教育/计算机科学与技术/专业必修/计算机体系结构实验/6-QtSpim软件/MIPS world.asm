#welcome.asm
        .data 0x10000000
msg:    .asciiz "Welcome to MIPS world!" 
        .text
main:   addu $s0, $ra, $0
        li  $v0, 4
        la $a0, msg
        syscall
        addu $ra, $0, $s0
        jr $ra