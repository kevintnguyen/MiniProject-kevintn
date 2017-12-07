lui $t1, 4097
ori $t0,$t1, 0 
lw $t2, 0($t0)			
lui $t1, 4097
ori $t0,$t1, 4
lw $t3, 0($t0)		
add $s0,$t2,$t3		
sw $s0, 0($t1)
ori $v0, $zero, 10
syscall