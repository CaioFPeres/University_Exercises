# Atividade 04

Esta já é a nossa quarta atividade :tada: :tada: :tada: :tada:

Os objetivos desta atividade são:
- relembrar alguns conceitos estudados na disciplina anterior, principalmente fila e recursão;
- trabalhar com árvores binárias de busca;
- implementar percursos nestas árvores.

Para fazer esta atividade, você deve:
- implementar apenas os trechos faltantes de código, indicados por ```\\ implementar```;
- não alterar qualquer outra parte do código;
- implementar a fila com alocação dinâmica e encadeamento simples, encapsulada e com dado como ponteiro para void;
- testar as entradas fornecidas e comparar com as saídas geradas.

## Problema

Neste problema, você deverá construir uma árvore binária de busca (ABB ou BST) com a sequência de números fornecida. Esta sequência não possui números repetidos. Por exemplo, a sequência de valores: 8 3 10 14 6 4 13 7 1 resulta na seguinte árvore binária de busca:

![Exemplo de ABB](exemplo.png)

Em seguida, você deve imprimir os percursos pré-ordem, em-ordem, pós-ordem e em-nível, conforme a especificação abaixo.

### Entrada

A entrada contém apenas um caso de teste. A primeira linha contém um inteiro ```N``` (1 ≤ ```N``` ≤ 500) que indica a quantidade de números que devem compor cada árvore e a segunda linha contém ```N``` inteiros distintos, separados por um espaço em branco.

### Saída

Após construir a árvore binária de busca com os elementos da entrada, você deverá imprimir cada percurso em uma linha, conforme o exemplo abaixo. Separe cada um dos elementos por um espaço em branco e termine cada linha com um ```\n```.

### Exemplo

| Entrada | Saída |
| :-- | :-- |
|<pre><br>9<br>8 3 10 14 6 4 13 7 1<br><pre>|<pre><br>Pr.: 8 3 1 6 4 7 10 14 13<br>In.: 1 3 4 6 7 8 10 13 14<br>Po.: 1 4 7 6 3 13 14 10 8<br>Ni.: 8 3 10 1 6 14 4 7 13<br><pre>|




