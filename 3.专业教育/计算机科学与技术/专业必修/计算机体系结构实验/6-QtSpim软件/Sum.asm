.data
prompt: .asciiz "\n Please Input a value for N = "
result: .asciiz " The sum of the integers from 1 to N is "
bye: .asciiz "\n **** Adios Amigo - Have a good day ****"
.globl main
.text
main:
li $v0, 4 # system call code for Print String
la $a0, prompt # load address of prompt into $a0
syscall # print the prompt message
li $v0, 5 # system call code for Read Integer
syscall # reads the value of N into $v0
blez $v0, end # branch to end if $v0 < = 0
li $t0, 0 # clear register $t0 to zero
loop:
add $t0, $t0, $v0 # sum of integers in register $t0
addi $v0, $v0, -1 # summing integers in reverse order
bnez $v0, loop # branch to loop if $v0 is != zero
li $v0, 4 # system call code for Print String
la $a0, result # load address of message into $a0
syscall # print the string
li $v0, 1 # system call code for Print Integer
move $a0, $t0 # move value to be printed to $a0
syscall # print sum of integers
b main # branch to main
end: li $v0, 4 # system call code for Print String
la $a0, bye # load address of msg. into $a0
syscall # print the string
li $v0, 10 # terminate program run and
syscall # return control to system
