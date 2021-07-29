.data
	space: .space 12

.text

	addi $t1, $zero, 0       #percorre(indice)
	addi $t0, $zero, 0	#percorre 2 (indice)
	addi $t2, $zero, 12
	addi $t3, $zero, 0
	addi $t4, $zero, 0
	
	
	
	Loop1: 
	beq $t1, $t2, Loop2	 #at 12 we go to Exit, defined below
        sw $t4, space($t1)
        addi $t4, $t4, 1
        addi $t1, $t1, 4 	#increment counter
        
        j Loop1 		#jumps back to the top of loop
	
	
	Loop2:
	beq $t0, $t2, Exit       #at 12 we go to Exit, defined below
	
	lw $s1, space($t0)      #CARREGA A FUCKING WORD PRO REG
	
        add $t3, $t3, $s1     #SOMA A CARALHUDA DA S1 COM O T3, E GUARDA EM T3
     
        addi $t0, $t0, 4         #increment counter
        
        j Loop2        #jumps back to the top of loop
	
	
	
	Exit:
	
	add $a0, $zero, $t3
	
	li $v0,1    	#prints
	syscall
	
	li $v0,10 	#loads the service that exits
	syscall
	
