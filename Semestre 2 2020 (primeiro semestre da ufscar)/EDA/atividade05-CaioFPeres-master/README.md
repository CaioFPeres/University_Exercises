# Atividade 05

Para fazer esta atividade, você deve:
- implementar apenas os trechos faltantes de código, indicados por ```\\ implementar```;
- não alterar qualquer outra parte do código;
- algumas instruções foram definidas nos trechos faltantes;
- testar as entradas fornecidas e comparar com as saídas geradas.

## Problema

Neste problema, você deverá manipular uma árvore binária de busca (ABB ou BST), seguindo os comandos da entrada fornecida.
Serão fornecidos os seguintes comandos:
- ```P```: inserção, apenas se o elemento não estiver na ABB;
- ```G```: consulta;
- ```R```: remoção, apenas se o elemento estiver na ABB.


### Entrada

A entrada contém apenas um caso de teste. Cada linha contém um comando ```P```, ```G``` ou ```R```, que indica a operação a ser realizada. Em seguida, separado por um espaço, é a palavra simples a ser inserida, consultada ou removida da estrutura.

### Saída

Para cada comando ```G```, exibir uma linha com a palavra e a informação se esta foi encontrada ou não na estrutura, conforme exemplo de saída.

### Exemplo

| Entrada | Saída |
| :-- | :-- |
|<pre><br>P casa<br>G casa<br>R casa<br>P abra<br>P a<br>P abracadabra<br>G ab<br>G abracadabra<br>G abra<br>G casa<br>R casa<br>R a<br>G a<br>R a<br>R abracadabra<br>R abra<br>G abra<br>R abra<br>G abracadabra<br>G casa<br><pre>|<pre><br>casa encontrada<br>ab nao foi encontrada<br>abracadabra encontrada<br>abra encontrada<br>casa nao foi encontrada<br>a nao foi encontrada<br>abra nao foi encontrada<br>abracadabra nao foi encontrada<br>casa nao foi encontrada<br><pre>|




