LIBRARY IEEE;
USE  IEEE.STD_LOGIC_1164.ALL;
USE  IEEE.STD_LOGIC_ARITH.ALL;
USE  IEEE.STD_LOGIC_UNSIGNED.ALL;
LIBRARY altera_mf;
USE altera_mf.altera_mf_components.all;

ENTITY nanoProc IS
	port(	reset	: IN STD_LOGIC;
			clock	: IN STD_LOGIC;
			ACout	: OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
			IRout	: OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
			PCout	: OUT STD_LOGIC_VECTOR(7 DOWNTO 0));
END nanoProc;

ARCHITECTURE exec OF nanoProc IS
TYPE MaquinadeEstados IS (inicia, le, decodifica, executa);

SIGNAL estado : MaquinadeEstados;

COMPONENT dmemory
	PORT(	read_data 	: OUT	STD_LOGIC_VECTOR( 15 DOWNTO 0 );
        	address 		: IN 	STD_LOGIC_VECTOR( 7 DOWNTO 0 );
        	write_data 	: IN 	STD_LOGIC_VECTOR( 15 DOWNTO 0 );
	   	memWrite 	: IN 	STD_LOGIC;
         clock,reset	: IN 	STD_LOGIC );
END COMPONENT;

SIGNAL AC, dataBus, IR	: STD_LOGIC_VECTOR(15 DOWNTO 0);
SIGNAL PC, addrBus		: STD_LOGIC_VECTOR(7 DOWNTO 0);
SIGNAL MW					: STD_LOGIC;

BEGIN
	-- Componente de memória definida no arquivo DMEMORY.vhd
	memoria : dmemory PORT MAP(	
							read_data	=> dataBus,
							address		=> addrBus,
							write_data	=> AC,
							memWrite		=> MW,
							clock			=> clock,
							reset			=> reset);
							
	PROCESS (clock, reset)
	BEGIN
		IF (reset = '1') THEN
			-- APÓS O PROJETO O ESTADO INICIAL DEVE ZERAR OS REGISTRADORES ABAIXO
			-- O reset DEVE SOMENTE DEFINIR O ESTADO INICIAL
			estado <= inicia;
			PC <= X"00";
			IR <= X"0000";
			AC <= X"0000";
		ELSIF clock'EVENT AND clock = '1' THEN
			CASE estado IS 
			
				WHEN le => 
					IR <= dataBus;
					PC <= PC + 1;
					estado <= decodifica;
					
				WHEN decodifica =>
					estado <= executa;
					
				WHEN executa =>
					PC <= IR(7 DOWNTO 0);
					estado <= le;
					
				WHEN OTHERS =>
					estado <= le;
				
			END CASE;	
		END IF;
	END PROCESS;
		
	WITH estado SELECT
		addrBus <= X"00" 				WHEN inicia, 
					  IR (7 DOWNTO 0) WHEN decodifica | executa,
					  PC 	  				WHEN OTHERS;
	 
	MW <= '0'; -- memória habilitada para leitura
	
	-- sinais a serem passados para a TLE para apresentação
	-- no display de LCD na placa
	PCout <= PC;
	IRout <= IR;
	ACout <= AC;
	
END exec;