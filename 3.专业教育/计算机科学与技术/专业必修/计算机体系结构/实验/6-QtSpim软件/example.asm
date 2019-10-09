						.data
						.align 2
jumptable: 	.word main, case1, case2, case3
prompt: 		.asciiz "\n\n Input a value from 1 to 3:"
						.text
main:       li $s0, 32         #初始化$s0
            li $v0, 4          #显示提示字符串
						la $a0, prompt
						syscall
						li $v0, 5          #读入整数
						syscall						
						blez $v0, case1     #判断是否小于0
						/*
						#li $t3, 3
						#bgt $v0, $t3, main #判断是否大于3
						la $a1, jumptable  #装载查找表基地址
						sll $t0, $v0, 2    #计算偏移
						add $t1, $a1, $t0  #计算跳转指令地址存放地址
						lw $t2, 0($t1)     #获取跳转地址
						jr $t2             #跳转
case1:			sll $s0, $s0, 1    #左移1位
						b output
case2:			sll $s0, $s0, 2    #左移2位
						b output
case3:			sll $s0, $s0, 3    #左移3位
output:     li $v0, 1          #输出整数结果
						move $a0, $s0
						syscall
						li $v0, 10         #退出
						syscall
*/						
						