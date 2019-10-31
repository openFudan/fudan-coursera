# Hello world
      .data
str:  .asciiz "Hello world.\n"
      .text       
      .globl main
main:              # execution starts here
      la $a0,str   # put string address into a0
      li $v0,4     # system call to print
      syscall      # print the string
      li $v0,10    # system call to exit
      syscall      # exit
      