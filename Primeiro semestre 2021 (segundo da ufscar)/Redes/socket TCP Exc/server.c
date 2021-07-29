#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>


int main() {

    //inicialização windows
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);
    ////////////////


    //socket config
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(5000);

    //socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    SOCKET client_socket;

    //inicializa servidor
    bind(server_socket, (struct sockaddr*) &saddr, sizeof(saddr));
    listen(server_socket, 5);

    ////////////////////////

    //variaveis
    char op, c1 = '=', c2;
    int op1, op2, resul = 0;

    //aceita conexão
    client_socket = accept(server_socket, NULL, NULL);

    //recebe 9 bytes
    recv(client_socket, &op, sizeof(op), 0);
    recv(client_socket, &op1, sizeof(op1), 0);
    recv(client_socket, &op2, sizeof(op2), 0);


    if(op == '+')
        resul = op1 + op2;
    else if(op == '-')
        resul = op1 - op2;
    else if(op == '*')
        resul = op1 * op2;
    else if(op == '/')
        resul = op1/op2;


    //envia resposta 5 bytes, começando com o caractere '='
    send(client_socket, &c1, sizeof(char), 0 );
    send(client_socket, (char*) &resul, sizeof(resul), 0 );


    //recebe confirmacao
    recv(client_socket, &c2, sizeof(char), 0);
    if(c2 == 1){
        printf("%i", c2);
    }
    else{
        printf("Erro");
    }


    //free
    WSACleanup();
    closesocket(client_socket);
    closesocket(server_socket);


    printf("\n");
    system("pause");
    return 0;

}