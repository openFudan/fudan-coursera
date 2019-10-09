# function: use mips input 
       .data
  # variable declarations here
  msg:     .space 40           #allocate 40 consecutive bytes,
  msg1:     .asciiz          "\ninput a integer: "  # declared for string
  msg2:     .asciiz          "\ninput a string: "   # declared for string
  msg3:     .asciiz          "\nyou input: "             # declared for string
       .text
  main:                      # indicates start of code
     # input integer
       li     $v0, 4
       la     $a0, msg1
       syscall
       li     $v0, 5                    #read integer
       syscall
       move     $a1, $v0
       li     $v0, 4
       la     $a0, msg3
       syscall
       li     $v0, 1
       move     $a0, $a1
       syscall
       
       li     $v0, 4
       la     $a0, msg2
       syscall
       li     $v0, 8
       la     $a0, msg
       li     $a1, 40
       syscall
       
       li     $v0, 4
       la     $a0, msg
       syscall
       
       li     $v0, 10                    #system call code for exit = 10
       syscall                         #call operating system to exit