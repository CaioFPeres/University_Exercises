.data
	elemento: .space 84 #20 inteiros na array
	entrada: .asciiz "Entrada: "
	erro: .asciiz "Muitos valores de entrada!"
	erro2: .asciiz " Digito invalido"
	erro3: .asciiz "Divisao por 0."
	resultado: .asciiz " "
	printaPilha: .asciiz "Pilha: "
	pulaLinha: .asciiz "\n"
.text


	#MAX = 20
	addi $s0, $zero, 20 #s0 = MAX
	#int i=0
	addi $s1, $zero, 0

  	#Printa
	li $v0, 4
	la $a0, entrada
	syscall
	
	
   do_while:
   
   	jal pegachar
   	
   	bne $t0, 32 , semespaco
   	j do_while
   	
   semespaco:
   	addi $t2, $zero ,0 #t2 = 0
   	
   while:
   	blt $t0, 48, saidaWhile 
   	bgt $t0, 57, saidaWhile
   	
   	
   	mul $t2, $t2, 10
   	sub $t0, $t0, 48
   	add $t2, $t2, $t0
   	
  	jal pegachar
  	j while
  	
  	
   saidaWhile:
   	
   	beq $t0, 43, if # se char for '+') 
   	beq $t0, 45, if # se char for '-')
   	beq $t0, 42, if # se char for '*')
   	beq $t0, 47, if # se char for '/')
   	b else_if
   	
   if:
   	jal empilhar     # chama empilhar
   	move $t4, $v0    # move $v0 para $t4 "x2"
   	jal empilhar     # empilhar
   	move $t3, $v0    # move $v0 para $t3 "x1"
   	jal calculo      # calculo
   	move $t2, $v0
   	jal desempilhar
   	
   	j do_while
   	
   else_if:
   	#(char != '=')
   	bne $t0, 61, empilhando
   	b semempilhar
   empilhando:
   	jal desempilhar
   semempilhar:
   	beq $t0, 61, saida_doWhile
   	j do_while
   	

   
   	
   	
   saida_doWhile:
   	beq $s1, 1, print
   	
   	li $v0, 4
   	la $a0, printaPilha
   	syscall
   	
   	addi $t7, $zero, 0
   	b printaElemento
   
   saidaPrograma:
   	li $v0,10
   	syscall
   
   printaElemento:
   	bgt $s2, 19, saidaPrograma
   		
   	addi $s2, $s2, 1
   	
  
   	li $v0, 4
   	la $a0, pulaLinha
   	
   	
   	lw $t6, elemento($t7) 
		addi $t7, $t7, 4 

	li $v0, 1
   	addi $a0, $t6, 0
   	
	
	j printaElemento
	
	
   print:
   	#Printa saida
   	li $v0, 4
   	la $a0, resultado
   	syscall
   	
   	lw $t6, elemento($zero)   #pega primeiro elemento da pilha
   	#Printa resultado
   	li $v0, 1
   	addi $a0, $t6, 0
   	syscall
   	
	b printaElemento
    pegachar:
	#pega o char
	li $v0, 12
	syscall
	
	#coloca em t0
	move $t0, $v0
	
   	jr $ra	 	 	 	 	
   	 	 	 	 	 	
   	 	 	 	 	 	 	
   	 	 	 	 	 	 	
   	 	 	 	 	 	 	 	 	 	
   desempilhar:
   	beq $s1, $s0, erroOverflow
   	sw $t2 , elemento($t7)#p[i]
   	addi $t7, $t7, 4 
   	addi $s1, $s1, 1 # i++
   	
   	jr $ra
   	
   empilhar:
   	addi $t7, $t7, -4
   	
   	beq $s1, $zero, erroUnderflow
   	lw $v0, elemento($t7)
   		
   	addi $s1, $s1, -1 # i--
   
   	jr $ra
   	
   calculo:
   	addi $t5, $zero ,0
   	#Switch cases :
   	beq $t0 ,43, calc1
   	beq $t0, 45, calc2
   	beq $t0, 42, calc3
   	beq $t0, 47, calc4
   
   saida:		
   	addi $v0, $t5, 0
   	
   	jr $ra
   calc1:		
   	#total($t5) = x1+x2;
	add $t5, $t3, $t4 
	j saida
	
   calc2:
   	#total = x1-x2;
   	sub $t5, $t3, $t4
   	j saida
	
   calc3:
   	#total = x1 * x2
   	beq $t8, $t4, saida
   	addi $t8, $t8, 1
   	add $t5, $t5, $t3
   	j calc3
   	
   calc4:
	beq $t4 , $zero, erro_divisaoporzero
	beq $t9, $t3, saida
	
	add $t9, $t9, $t4
	addi $t5, $t5, 1
	j calc4
	
   	

   	
   erroOverflow:
   	#Printa erro
   	li $v0, 4
   	la $a0, erro
   	syscall
   	#fecha programa
   	li $v0,10
   	syscall
   		
   erroUnderflow:
   	#Printa erro
   	li $v0, 4
   	la $a0, erro2
   	syscall
   	#fecha programa
   	li $v0,10
   	syscall

   erro_divisaoporzero:
   	#Printa erro
   	li $v0, 4
   	la $a0, erro3
   	syscall
   	#fecha programa
   	li $v0,10
   	syscall
