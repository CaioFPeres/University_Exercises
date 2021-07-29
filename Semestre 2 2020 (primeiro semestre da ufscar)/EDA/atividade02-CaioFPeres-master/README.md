# Atividade 02

Esta é a nossa segunda atividade :tada: e de novo vocês já fizeram este exercício na disciplina anterior. O algoritmo principal já está aqui, o que está faltando é a estrutura lista encadeada ordenada. A API já foi definida, e um caso de teste está nos arquivos ```input``` e ```output ```.

Os objetivos desta atividade são:
- relembrar alguns conceitos estudados na disciplina anterior;
- se familiarizar com o [GitHub](https://github.com/).

Para fazer esta atividade, você deve:
- assistir as instruções em vídeo na página da disciplina;
- implementar os trechos faltantes de código no arquivo ```lista.c```, este arquivo é a implementação das definições que estão no arquivo ```lista.h```. Faça uma ***lista ordenada com alocação dinâmica, encadeamento duplo, sentinela e circular***.

## Problema

Implemente uma lista ordenada, com alocação dinâmica, duplamente encadeada, com sentinela e circular. O programa principal irá utilizar esta lista. Este programa irá ler uma entrada de comandos, conforme especificação abaixo, e gerar a saída correspondente.

### Entrada

Cada linha é iniciada por um dos comandos abaixo, seguida ou não por um caractere. 
- ```insere```: comando para inserir na lista um elemento. O elemento a ser inserido é fornecido logo em seguida.
- ```remove```: comando para remover da lista um elemento. O elemento a ser removido é fornecido logo em seguida. Remova todos os elementos iguais encontrados. Se não o encontrar, não imprima nada.
- ```imprime```: comando para imprimir toda a lista na saída padrão, separados por um espaço. Se a lista estiver vazia, imprima a palavra ```vazia```.

### Saída

Imprima uma linha para cada operação ```imprime```. Separe cada elemento por um espaço. Não imprima o último espaço. Se a lista estiver vazia, imprima a palavra ```vazia```.

### Exemplo

| Entrada | Saída |
| :-- | :-- |
|<pre><br>imprime<br>insere A<br>insere A<br>insere B<br>imprime<br>remove A<br>insere A<br>insere A<br>insere B<br>insere B<br>remove C<br>imprime<br><pre>|<pre><br>vazia<br>A A B<br>A A B B B<br><pre>|

### Restrições
- Documente adequadamente o código;
- Não utilize variáveis globais;
- Não viole o encapsulamento da lista;
- Utilize um iterador para imprimir os elementos da lista;
- Utilize um ponteiro para a função de comparar os elementos;
- Utilize a API especificada neste exercício, sem alterá-la;
- Implemente a lista utilizando alocação dinâmica, encadeamento duplo, sentinela e circular.
