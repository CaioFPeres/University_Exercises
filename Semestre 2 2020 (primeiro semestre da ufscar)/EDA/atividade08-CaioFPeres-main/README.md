# Atividade 08


Em um sistema de execução sequencial de tarefas, definir a ordem de execução das tarefas é um problema interessante.

Neste exercício, cada tarefa poderá depender da conclusão de outras tarefas para poder começar. Ainda, cada tarefa terá uma prioridade de execução.

Por exemplo, se uma tarefa ```A``` depende de uma tarefa ```B```, a tarefa ```B``` deve terminar antes que a tarefa ```A``` inicie sua execução.
Com relação a prioridade, é sempre mais vantajoso para o sistema começar executando uma tarefa de mais alta prioridade, depois continuar executando uma tarefa de mais alta prioridade dentre as que sobraram e assim por diante.

Neste problema, será dado um inteiro ```N```, que irá representar o número de tarefas no sistema. As tarefas serão
numeradas de ```0``` até ```N − 1```. Tarefas com índice menor possuem prioridade maior, de forma que a tarefa ```0``` é a
tarefa de mais alta prioridade, a tarefa ```1``` é a tarefa com a segunda maior prioridade e assim por diante, até a
tarefa ```N − 1```, que é a tarefa com a menor prioridade. Além disso, serão dadas M relações de dependência entre
as tarefas.

Seu objetivo será decidir se é possível executar as tarefas em alguma ordem. Caso seja possível, você deverá
produzir uma ordem de execução ótima para as tarefas, isto é, desempate as ordens possíveis pela prioridade da
primeira tarefa. Se o empate ainda persistir, desempate pela prioridade da segunda tarefa, e assim por diante.

Teste sua solução com as entradas e saídas fornecidas no diretório ```tests```.


### Entrada

A primeira linha da entrada contém os inteiros ```N``` (0 <= ```N``` <= 50000) e ```M``` (0 <= ```M``` <= 200000). As próximas ```M``` linhas descrevem, cada uma, uma
dependência entre as tarefas da entrada. Cada uma dessas linhas irá conter dois inteiros A e B que indicam
que a tarefa ```B``` depende da tarefa ```A```, isto é, que a tarefa ```A``` deve terminar antes que a tarefa ```B``` inicie.

### Saída

Se não for possível ordenar as tarefas de forma que as dependências sejam satisfeitas, imprima uma única linha
contendo o caracter ```*```. Caso contrário, imprima ```N``` linhas contendo cada uma um número inteiro. O inteiro
na ```i```-ésima linha deve ser o índice da ```i```-ésima tarefa a ser executada na ordem ótima de execução das tarefas.

### Exemplo

| Entrada | Saída |
| :-- | :-- |
|<pre><br>3 1<br>2 0<br><pre>|<pre><br>1<br>2<br>0<br><pre>|

| Entrada | Saída |
| :-- | :-- |
|<pre><br>2 2<br>0 1<br>1 0<br><pre>|<pre><br>*<br><pre>|

### Restrições
- Documente adequadamente o código;
- Utilize uma fila de prioridades encapsulada, separada da sua implementação principal (você pode reaproveitar implementações anteriores);

