#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>


int main() {

    //inicialização WSA windows
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);
    //////////////////////


    //socket config
    struct sockaddr_in saddr;
    
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(5000);

    int server_struct_length = sizeof(saddr);

    //socket descriptor
    SOCKET client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    //variaveis
    char op, c1, c2 = 1, c3 = '?', c4 = 'n';
    int op1, op2, resul = 0;

    scanf("%c %i %i", &op, &op1, &op2);

    //envia 9 bytes
    sendto(client_socket, &op, sizeof(op), 0, (struct sockaddr*) &saddr, server_struct_length);
    sendto(client_socket, (char*) &op1, sizeof(op1), 0, (struct sockaddr*) &saddr, server_struct_length);
    sendto(client_socket, (char*) &op2, sizeof(op2), 0, (struct sockaddr*) &saddr, server_struct_length);

    //recebe 1 byte
    recvfrom(client_socket, &c1, sizeof(c1), 0, (struct sockaddr*) &saddr, &server_struct_length);
    if(c1 == '='){

        //recebe 4 bytes
        if(recvfrom(client_socket, &resul, sizeof(resul), 0, (struct sockaddr*) &saddr, &server_struct_length) == 4){

            //envia confirmação
            sendto(client_socket, &c2, sizeof(char), 0, (struct sockaddr*) &saddr, server_struct_length);
            printf("%c ", c1);
            printf("%i", resul);

        }
        else{
            //envia 'n'
            sendto(client_socket, &c4, sizeof(char), 0, (struct sockaddr*) &saddr, server_struct_length);
        }

    }
    else{
        //envia '?'
        sendto(client_socket, &c3, sizeof(char), 0, (struct sockaddr*) &saddr, server_struct_length);
    }


    //free
    WSACleanup();
    closesocket(client_socket);

    
    printf("\n");
    system("pause");
    return 0;

}