#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>


int main() {

    //inicialização windows
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);
    ////////////////


    //socket config
    struct sockaddr_in saddr, caddr;

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(5000);

    int client_struct_length = sizeof(caddr);

    //socket descriptor
    SOCKET server_socket = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);

    //inicializa servidor
    bind(server_socket, (struct sockaddr*) &saddr, sizeof(saddr));
    listen(server_socket, 5);

    ////////////////////////

    //variaveis
    char op, c1 = '=', c2 = 0;
    int op1, op2, resul = 0;

    //recebe 9 bytes
    recvfrom(server_socket, &op, sizeof(op), 0, (struct sockaddr*) &caddr, &client_struct_length);
    recvfrom(server_socket, &op1, sizeof(op1), 0, (struct sockaddr*) &caddr, &client_struct_length);
    recvfrom(server_socket, &op2, sizeof(op2), 0, (struct sockaddr*) &caddr, &client_struct_length);


    if(op == '+')
        resul = op1 + op2;
    else if(op == '-')
        resul = op1 - op2;
    else if(op == '*')
        resul = op1 * op2;
    else if(op == '/')
        resul = op1/op2;


    //envia resposta 5 bytes, começando com o caractere '='
    sendto(server_socket, &c1, sizeof(c1), 0, (struct sockaddr*) &caddr, client_struct_length);
    sendto(server_socket, (char*) &resul, sizeof(resul), 0, (struct sockaddr*) &caddr, client_struct_length);

    //recebe confirmacao
    recvfrom(server_socket, &c2, sizeof(c2), 0, (struct sockaddr*) &caddr, &client_struct_length);
    if(c2 == 1){
        printf("%i", c2);
    }
    else{
        printf("Erro");
    }

    //free
    WSACleanup();
    closesocket(server_socket);


    printf("\n");
    system("pause");
    return 0;

}