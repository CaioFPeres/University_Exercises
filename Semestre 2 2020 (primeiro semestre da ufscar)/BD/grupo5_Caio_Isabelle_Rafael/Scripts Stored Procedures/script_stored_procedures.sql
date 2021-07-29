--STORED PROCEDURE DA CONSULTA ABSOLUTA:

CREATE FUNCTION produtos_em_um_periodo(varchar, int, int)
RETURNS TABLE (nome_produto varchar, nomecategoria varchar, preco double precision, quantidade_media numeric, quantidade_total bigint) AS $$
DECLARE
    nome_da_loja ALIAS FOR $1;
    qtd_inicial ALIAS FOR $2;
    qtd_final ALIAS FOR $3;
BEGIN
    RETURN QUERY SELECT produto.nome as nome_produto, categoria, preco, ROUND(AVG(quantidade), 2) AS media_por_lote, SUM(quantidade) AS quantidade_total FROM transacao, produto, loja 
WHERE produto_id = id AND cod = loja_cod AND loja.nome = nome_da_loja
GROUP BY id
HAVING SUM(quantidade) > qtd_inicial AND SUM(quantidade) <= qtd_final;
END;
$$ LANGUAGE plpgsql;

--Chamada da função:
	SELECT * from produtos_em_um_periodo(<NOME_LOJA>, <QUANTIDADE_INICIAL>, <QUANTIDADE_FINAL>);

--Devido ao tipo varchar do parâmetro, a entrada referente ao nome deve estar entre aspas simples, como tanto a quantidade final como a inicial são inteiros, isto não é necessário.



--STORED PROCEDURE DA CONSULTA RELATIVA:

CREATE FUNCTION vendas_por_categoria(character varying(50), date, date)
RETURNS TABLE (cod_loja int, nome_loja character varying(50), nome_categoria character varying(50), sum numeric) AS $$
DECLARE
    nome_da_loja ALIAS FOR $1;
    data_inicial ALIAS FOR $2;
    data_final ALIAS FOR $3;
BEGIN
    RETURN QUERY SELECT loja.cod, loja.nome, categoria, sum(vendas.total) FROM
    (SELECT produto_id  as id, sum(quantidade) as total FROM transacao WHERE 
     transacao.data_compra BETWEEN data_inicial AND data_final AND status = 'Entregue' GROUP BY produto_id) 
    as vendas, loja, produto
    WHERE vendas.id = produto.id AND loja.cod = loja_cod AND loja.nome LIKE nome_da_loja
    GROUP BY loja.cod, produto.categoria
    ORDER BY loja.cod, sum(vendas.total) DESC;
END;
$$ LANGUAGE plpgsql;

--Chamada da função:
SELECT * FROM vendas_por_categoria(<NOME_LOJA>, <DATA_INICIAL>, <DATA_FINAL>)


--Assim como na última consulta o parâmetro referente ao nome da loja também deve ser inserido entre aspas simples, em relação às datas iniciais e finais, ambas devem ser inseridas no formato ‘ano-mês-dia’.
