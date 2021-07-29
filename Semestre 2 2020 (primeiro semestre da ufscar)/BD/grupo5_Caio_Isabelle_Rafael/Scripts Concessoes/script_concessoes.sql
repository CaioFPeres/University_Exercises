--SCRIPT DAS CONCESSÕES 

		-- Criamos o usuário chamado db_owner com o privilégio de criar outros usuários.
CREATE ROLE db_owner WITH CREATEROLE; 

-- Concedemos todos os privilégios de cada tabela do nosso projeto para o db_owner (a partir do usuário postgres)

GRANT ALL PRIVILEGES ON comprador TO db_owner WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON transacao TO db_owner WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON loja TO db_owner WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON categoria TO db_owner WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON produto TO db_owner WITH GRANT OPTION;

-- Então alteramos o dono do banco de dados para db_owner 

ALTER DATABASE <nome_bd> OWNER TO db_owner;

	-- Colocamos o db_owner para atuar como usuário atual 

	SET ROLE db_owner;

-- MODERADOR:

-- Criamos o usuário moderador 

CREATE ROLE moderador WITH NOINHERIT;

-- Concedemos os privilégios que o moderador possui de cada tabela  

GRANT SELECT, DELETE ON TABLE comprador TO moderador
GRANT SELECT, UPDATE, DELETE ON TABLE transacao TO moderador;
GRANT SELECT, DELETE ON TABLE loja TO moderador;
GRANT SELECT, INSERT, UPDATE, DELETE ON TABLE categoria TO moderador;
GRANT SELECT, DELETE ON TABLE produto TO moderador;




-- COMPRADOR:
	
-- Criamos o usuário comprador

CREATE ROLE comprador WITH NOINHERIT LOGIN PASSWORD ‘senha1’;

-- Concedemos os privilégios que o comprador possui de cada tabela  

GRANT SELECT, UPDATE, DELETE ON TABLE comprador TO comprador;
GRANT SELECT, INSERT ON TABLE transacao TO comprador;
GRANT SELECT ON TABLE loja TO comprador;
GRANT SELECT ON TABLE categoria TO comprador;
GRANT SELECT ON TABLE produto TO comprador;

	
-- SEM_CADASTRO:
	
		-- Criamos o usuário sem_cadastro

CREATE ROLE sem_cadastro WITH NOINHERIT;

-- Concedemos os privilégios que o usuário sem_cadastro possui de cada tabela  

GRANT INSERT ON comprador TO sem_cadastro;
GRANT SELECT, INSERT ON loja TO sem_cadastro;
GRANT SELECT ON categoria TO sem_cadastro;
GRANT SELECT ON produto TO sem_cadastro;

-- DONO_LOJA

-- Criamos o usuário dono_loja com o privilégio de criar outros usuários.

CREATE ROLE dono_loja WITH CREATEROLE

-- Concedemos os privilégios que o usuário dono_loja possui de cada tabela  

GRANT SELECT ON comprador TO dono_loja WITH GRANT OPTION;
GRANT SELECT, DELETE, UPDATE ON transacao TO dono_loja WITH GRANT OPTION;
GRANT SELECT, UPDATE, INSERT, DELETE ON loja TO dono_loja WITH GRANT OPTION;
GRANT SELECT ON categoria TO dono_loja WITH GRANT OPTION;
GRANT SELECT, UPDATE, INSERT, DELETE ON produto TO dono_loja WITH GRANT OPTION;

	-- Colocamos o dono_loja para atuar como usuário atual 

SET ROLE dono_loja;


-- FUNCIONARIO_LOJA

-- Criamos o usuário funcionario_loja

CREATE ROLE funcionario_loja WITH NOINHERIT;

-- Concedemos os privilégios que o usuário funcionario_loja possui de cada tabela  

GRANT SELECT ON comprador TO funcionario_loja;
GRANT SELECT, DELETE, UPDATE ON transacao TO  funcionario_loja;
GRANT SELECT, UPDATE ON loja TO funcionario_loja;
GRANT SELECT ON categoria TO funcionario_loja;
GRANT SELECT, UPDATE, INSERT, DELETE ON produto TO funcionario_loja;

