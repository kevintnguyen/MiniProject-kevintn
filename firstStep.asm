        .text
        .globl main
main:   
		lui $t1, 4097
		ori $t0,$t1, 0 
		lw $t2, 0($t0)			#load value of first index to $t2
		lui $t1, 4097
		ori $t0,$t1, 4
		lw $t3, 0($t0)			#load value of second index to $t3
		add $s0,$t2,$t3			#$t2 + $t3 = $s0
		sw $s0, 4105			#store $s0 to location 4105
		ori $v0, $zero, 10		# syscall exit
		syscall
		

 .data
Number1: .word 5
Number2: .word 7