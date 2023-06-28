#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../headers/commit_list.h"


/* Define a porta do servidor */
#define PORT 4242


/* Tamanho dos buffers dos sockets */
#define LEN 4096


/* Endereço do servidor */
#define SERVER_ADDR "127.0.0.1"


/*
 * Execução principal do programa cliente do nosso protocolo simples
 */
int send_data_to_server(char * data_buffer){
    /* Socket do servidor */
    struct sockaddr_in server;
    /* Descritor de arquivo do cliente para o socket local */
    int sockfd;

    int len = sizeof(server);
    int slen;

    /* Buffer de recebimento */
    char buffer_in[LEN];
    /* Buffer de envio */
    char buffer_out[LEN];


    fprintf(stdout, "Iniciando Cliente ...\n");


    /*
     * Cria um socket para o cliente
     */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Erro na criação do socket do cliente:");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Socket do cliente criado com fd: %d\n", sockfd);


    /* Define as propriedades da conexão */
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    memset(server.sin_zero, 0x0, 8);


    /* Tenta se conectar ao servidor */
    if (connect(sockfd, (struct sockaddr*) &server, len) == -1) {
        perror("Não é possível conectar ao servidor");
        return EXIT_FAILURE;
    }



    /*
     * Comunica com o servidor até que a mensagem de saída seja recebida
     */

        /* Limpa os buffers */
        memset(buffer_in, 0x0, LEN);
        memset(buffer_out, 0x0, LEN);

        /* Envia a mensagem lida para o servidor através do socket */
        send(sockfd, data_buffer, strlen(data_buffer), 0);

        /* Recebe uma resposta do servidor */
        slen = recv(sockfd, buffer_in, LEN, 0);
        printf("Resposta do servidor: %s\n", buffer_in);


    /* Fecha a conexão com o servidor */
    close(sockfd);

    fprintf(stdout, "\nConexão fechada\n\n");

    return EXIT_SUCCESS;
}


