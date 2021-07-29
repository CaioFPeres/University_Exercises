# Atividade 01

Esta é a nossa primeira atividade :tada: vocês já fizeram este exercício na disciplina anterior. O algoritmo principal já está aqui, o que está faltando é a estrutura pilha. A API já foi definida, e alguns casos de teste estão nos arquivos ```input``` e ```output ```.

Os objetivos desta atividade são:
- relembrar alguns conceitos estudados na disciplina anterior;
- se familiarizar com o [GitHub](https://github.com/).

Para fazer esta atividade, você deve:
- assistir as instruções em vídeo na página da disciplina;
- implementar os trechos faltantes de código no arquivo ```pilha.c```, este arquivo é a implementação das definições que estão no arquivo ```pilha.h```. Faça uma ***pilha com alocação dinâmica e encadeamento simples***.


## Expressões (OBI2011)

Pedrinho e Zezinho estão precisando estudar resolução de expressões matemáticas para uma prova que irão fazer. Para isso, eles querem resolver muitos exercícios antes da prova. Como sabem programar, então decidiram fazer um gerador de expressões matemáticas.

O gerador de expressões que eles criaram funciona em duas fases. Na primeira fase é gerada uma cadeia de caracteres que contém apenas os caracteres "{", "[", "(", "}", "]" e ")". Na segunda fase, o gerador adiciona os números e operadores na estrutura criada na primeira fase. Uma cadeia de caracteres é dita bem definida (ou válida) se atende as seguintes propriedades:

1. Ela é uma cadeia de caracteres vazia (não contém nenhum caractere).
2. Ela é formada por uma cadeia bem definida envolvida por parênteses, colchetes ou chaves. Portanto, se a cadeia S é bem definida, então as cadeias (S), [S] e {S} também são bem definidas.
3. Ela é formada pela concatenação de duas cadeias bem definidas. Logo, se as cadeias X e Y são bem definidas, a cadeia XY é bem definida.

Depois que Pedrinho e Zezinho geraram algumas expressões matemáticas, eles perceberam que havia algum erro na primeira fase do gerador. Algumas cadeias não eram bem definidas. Eles querem começar a resolver as expressões o mais rápido possível, e sabendo que você é um ótimo programador (e participa da OBI) resolveram pedir que escreva um programa que dadas várias cadeias geradas na primeira fase, determine quais delas são bem definidas e quais não são.


### Entrada

A entrada é composta por diversas instâncias. A primeira linha da entrada contém um inteiro T indicando o número de instâncias. Em seguida temos T (1 ≤ T ≤ 20) linhas, cada uma com uma cadeia A. A cadeia de caracteres A tem entre 1 e 100000 caracteres e contém apenas caracteres "{", "[", "(", "}", "]" e ")".

### Saída

Para cada instância imprima uma linha contendo a letra “S” se a cadeia é bem definida, ou a letra “N” caso contrário.


### Exemplo

| Entrada | Saída |
| :-- | :-- |
|<pre><br>12<br>()<br>[]<br>{}<br>(]<br>}{<br>([{}])<br>{}()[]<br>()]<br>{[]<br>(<br>(([{}{}()[]])(){}){}<br>(((((((((({([])}])))))))))<br><pre>|<pre><br>S<br>S<br>S<br>N<br>N<br>S<br>S<br>N<br>N<br>N<br>S<br>N<br><pre>|

### Restrições

- Documente adequadamente o seu código;
- Não utilize variáveis globais;
- Mantenha o encapsulamento da pilha;
- Altere apenas os blocos marcado com  ```\\ implementar```, no arquivo ```pilha.c```.
