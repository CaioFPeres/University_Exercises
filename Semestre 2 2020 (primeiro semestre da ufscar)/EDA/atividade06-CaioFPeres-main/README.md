# Atividade 06

Para fazer esta atividade, você deve:
- implementar apenas os trechos faltantes de código, indicados por ```\\ implementar```, algumas instruções foram definidas nos trechos faltantes;
- não alterar qualquer outra parte do código;
- testar as entradas fornecidas e comparar com as saídas geradas.
- compare com a árvore binária de busca sem balanceamento

## Problema

Você foi escalado para minimizar os custos de empacotamento (garrafa e embalagem) de uma fábrica de poções mágicas.

Encontre, para cada tamanho de garrafa fornecida:
1. a maior poção mágica possível de se armazenar na garrafa; e,
1. a menor embalagem possível de se armazenar a garrafa.

A implementação que você irá alterar utiliza uma árvore AVL para armazenar as poções e as embalagens.

### Entrada

A entrada contém diversos casos de testes. A primeira linha contém um inteiro P (1 ≤ P ≤ 100.000) que indica a quantidade de poções existentes. Na segunda linha são fornecidos os tamanhos das P poções, separados por um espaço. A terceira linha contém um inteiro E (1 ≤ E ≤ 100.000) que indica a quantidade de embalagens existentes. Na quarta linha são fornecidos os tamanhos das E embalagens, separados por um espaço. Por fim, nas duas últimas linhas, são fornecidos o número de garrafas G (1 ≤ G ≤ 100.000) e o tamanho de cada uma, também separados por um espaço. Todos os tamanhos são números inteiros positivos e menores que 1.000.000.

### Saída

Você deverá imprimir uma linha para cada garrafa fornecida. Nesta linha exiba o tamanho da maior poção possível de se armazenar na garrafa e o tamanho da menor embalagem que pode ser utilizada para armazena a garrafa. Separe estes dois valores por um espaço. Quando não for possível armazenar qualquer uma das poções, ou não existir caixa suficientemente grande, imprima a palavra “descartar”.

### Exemplo

| Entrada | Saída |
| :-- | :-- |
|<pre><br>3<br>2 5 3<br>5<br>6 3 4 1 7<br>6<br>2 3 1 8 7 6<br><pre>|<pre><br>2 3<br>3 3<br>descartar<br>descartar<br>5 7<br>5 6<br><pre>|




