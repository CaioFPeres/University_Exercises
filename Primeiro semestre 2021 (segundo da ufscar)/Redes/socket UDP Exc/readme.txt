Feito utilizando a API de sockets do windows.

Para compilar, deve-se executar o seguinte comando, utilizando um compilador como o mingw no windows, ou importando a DLL do windows ws2_32 no visual studio:


gcc server.c -o server.exe -l ws2_32

e

gcc client.c -o client.exe -l ws2_32