# mipstest.asm
# David_Harris@hmc.edu 9 November 2005
#
# Test the MIPS processor.
# add, sub, and, or, slt, addi, lw, sw, beq, j
# If successful, it should write the value 7 to address 84
# Assembly Description Address Machine
main: 		addi $2, $0, 5 				
		addi $3, $0, 12 			
		addi $7, $3, -9 
		andi $8, $3, 0
		ori $8, $3, 15 			
		or $4, $7, $2 				
		and $5, $3, $4 				
		add $5, $5, $4 				
		bne $5, $7, end				
		slt $4, $3, $4 				
		beq $4, $0, around 			
		addi $5, $0, 0 				
around: 	slt $4, $7, $2 				
		add $7, $4, $5 				
		sub $7, $7, $2 				
		sw $7, 68($3) 				
		lw $2, 80($0) 				
		j end 					
		addi $2, $0, 1 				
end: 		sw $2, 84($0) 				
