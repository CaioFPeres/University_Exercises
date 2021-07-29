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

    //socket
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);

    //conecta
    int connection_status = connect(client_socket, (struct sockaddr*) &saddr, sizeof(saddr));

    //verifica se tem erro de conexão
    if (connection_status == SOCKET_ERROR) {
        wprintf(L"Erro: %ld\n", WSAGetLastError());
        connection_status = closesocket(client_socket);
        if (connection_status == SOCKET_ERROR)
            wprintf(L"Erro: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }


    //variaveis
    char op, c1, c2 = 1, c3 = '?', c4 = 'n';
    int op1, op2, resul = 0;

    scanf("%c %i %i", &op, &op1, &op2);

    //envia 9 bytes
    send(client_socket, &op, sizeof(op), 0 );
    send(client_socket, (char*) &op1, sizeof(op1), 0 );
    send(client_socket, (char*) &op2, sizeof(op2), 0 );


    //recebe 1 byte
    recv(client_socket, &c1, sizeof(char), 0);
    if(c1 == '='){
        
        //recebe 4 bytes
        if(recv(client_socket, &resul, sizeof(resul), 0) == 4){

            //envia confirmação
            send(client_socket, &c2, sizeof(char), 0 );
            printf("%c ", c1);
            printf("%i", resul);

        }
        else{
            //envia 'n'
            send(client_socket, &c4, sizeof(char), 0 );
        }

    }
    else{
        //envia '?'
        send(client_socket, &c3, sizeof(char), 0 );
    }


    //free
    WSACleanup();
    closesocket(client_socket);

    
    printf("\n");
    system("pause");
    return 0;

}