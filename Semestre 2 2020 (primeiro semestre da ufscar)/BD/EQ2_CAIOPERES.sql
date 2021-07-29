1)

a)

SELECT * FROM empregado WHERE nome_empregado ILIKE 'MIGUEL%';

b)

SELECT * FROM empregado WHERE nome_empregado ILIKE '%MIGUEL';

c)

SELECT * FROM empregado WHERE nome_empregado ILIKE '%MIGUEL%' AND nome_empregado NOT ILIKE 'MIGUEL';

d)

SELECT * FROM empregado WHERE nome_empregado LIKE '%Miguel%';

e)

SELECT * FROM empregado WHERE nome_empregado ILIKE '%Miguel%';


2)

SELECT nome_empregado, salario, depto FROM empregado ORDER BY depto, salario DESC;


3)

a)

SELECT cod FROM tipo_empregado EXCEPT SELECT cod FROM tipo_empregado, empregado WHERE empregado.tipo_empregado = tipo_empregado.cod;

b)

SELECT cod FROM tipo_empregado WHERE cod NOT IN (SELECT cod FROM tipo_empregado, empregado WHERE empregado.tipo_empregado = tipo_empregado.cod);

c)

SELECT cod FROM tipo_empregado FULL OUTER JOIN empregado ON empregado.tipo_empregado = tipo_empregado.cod WHERE cod NOT IN (SELECT cod FROM tipo_empregado, empregado WHERE empregado.tipo_empregado = tipo_empregado.cod);


4)

SELECT cod from departamento WHERE cod NOT IN (SELECT cod FROM departamento, empregado WHERE empregado.depto = departamento.cod) UNION (SELECT cod FROM empregado, departamento WHERE empregado.depto = departamento.cod GROUP BY cod HAVING COUNT(*) > 100);


5)

a)


SELECT nome_empregado, salario from empregado WHERE NOT empregado.salario < 100 AND empregado.salario > 5000 AND empregado.tipo_empregado = 1 INTERSECT (SELECT nome_empregado, salario from empregado WHERE NOT empregado.salario < 10000 AND empregado.tipo_empregado = 1);


b)


SELECT nome_empregado, salario from empregado WHERE empregado.salario >= 100 AND empregado.salario <= 5000 AND empregado.tipo_empregado = 1 UNION (SELECT nome_empregado, salario from empregado WHERE empregado.salario >= 10000 AND empregado.tipo_empregado = 1);


c)

SELECT empregado.nome_empregado, empregado.salario FROM empregado JOIN (SELECT nome_empregado, salario FROM empregado WHERE empregado.salario >= 10000 AND empregado.tipo_empregado = 1) AS x ON empregado.salario >= 100 AND empregado.salario <= 5000 AND empregado.tipo_empregado = 1; 


6)

SELECT cpf, COUNT(*) FROM projeto GROUP BY cpf HAVING COUNT(*) = (SELECT COUNT(*) as numP FROM tipo_projeto);


7)

--Na tabela projeto constam todos os empregados que possuem um projeto, portanto é impossivel resgatar um projeto sem empregado, pois a consulta é feita a partir dos empregados com um projeto e não do tipo_projeto onde constam todos os tipos de projetos.

SELECT cpf, COUNT(*) FROM projeto GROUP BY cpf HAVING COUNT(*) = (SELECT COUNT(*) as numP FROM tipo_projeto);


8)


CREATE VIEW empregados AS
SELECT nome_empregado, salario, descricao, nome_depto FROM empregado e, departamento d, tipo_empregado t WHERE e.depto = d.cod AND e.tipo_empregado = t.cod;


a)

UPDATE empregados
Set nome_empregado = 'nome' WHERE nome_empregado = 'Mary';

DETAIL:  Views that do not select from a single table or view are not automatically updatable.

A View não é atualizavel.


b)

SELECT nome_depto FROM empregados WHERE salario > 500;


9)


CREATE OR REPLACE FUNCTION att() RETURNS TRIGGER AS $triggeratt$
BEGIN

	IF (TG_OP = 'UPDATE') THEN
	
		IF (OLD.tipo_empregado != NEW.tipo_empregado) THEN
			UPDATE empregado SET salario = salario*0.1 + salario WHERE empregado.cpf = NEW.cpf;
		END IF;
		
	END IF;
	
	RETURN NEW;
	
END;
$triggeratt$ LANGUAGE plpgsql;

CREATE TRIGGER triggeratt
AFTER UPDATE ON empregado
EXECUTE PROCEDURE att();


10)


CREATE TABLE log (
    id_acao SERIAL,
    acao varchar,
    usuario varchar,
	data date,
   PRIMARY KEY (id_acao)
);



CREATE OR REPLACE FUNCTION att() RETURNS TRIGGER AS $triggeratt$
BEGIN

	IF (TG_TABLE_NAME = 'empregado') THEN

		IF (TG_OP = 'INSERT') THEN
			INSERT INTO log (acao, usuario, data) VALUES ('INSERT', CURRENT_USER, CURRENT_TIMESTAMP);
		END IF;

		IF (TG_OP = 'UPDATE') THEN
			INSERT INTO log (acao, usuario, data) VALUES ('UPDATE', CURRENT_USER, CURRENT_TIMESTAMP);
		END IF;

		IF (TG_OP = 'DELETE') THEN
			INSERT INTO log (acao, usuario, data) VALUES ('DELETE', CURRENT_USER, CURRENT_TIMESTAMP);
		END IF;
	
	END IF;
	
	RETURN NEW;
	
END;
$triggeratt$ LANGUAGE plpgsql;

CREATE TRIGGER triggeratt
AFTER UPDATE ON empregado
EXECUTE PROCEDURE att();




