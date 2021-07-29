Para começar, abra o octave e selecione a pasta onde estão os arquivos ( fotos e o programa). É importante que estejam na mesma pasta.

Para rodar o programa, basta digitar "main" no campo de comando do octave ou abrir o arquivo main.m.

Os arquivos main1 até main5 são para uso com o poupaTempo.bat.

O programa chama as funcoes definidas passando o nome dos arquivos e um limiar para binarização.
Depois disso, compara com um valor definido de porcentagem de cor (branco ou preto), baseado na ausencia do elemento, para que se possa identificar.

Caso queira executar mais rapidamente, utilize o bat poupaTempo.bat. É preciso executá-lo na pasta do executavel do octave, juntamente com as imagens. 
Se for necessário, mudar o nome do executavel no arquivo (está como octave.vbs)
Esse arquivo bat abrirá 5 instancias do octave e irá separar 2 funções para cada instancia, portanto é importante ter um CPU bom (6 nucleos ou mais).
Essa solução força o octave a executar as funções em paralelo, utilizando o desempenho máximo do computador.