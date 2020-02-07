//
// Created by Anlan Yu on 2/5/20.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <map>
#include <shared_mutex>
#include <mutex>
#include <arpa/inet.h>
#include "messageType.h"

#define size 100000
#define NOVAL 0XFFFFFFFF
#define LOCK_NUM 100

template <typename T>
std::map<int,T> hash_table;
std::shared_mutex lock[LOCK_NUM];

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

template <typename T>
void get(int k, T* value, int* get_status){
    *get_status = 1;
    lock[k%LOCK_NUM].lock_shared();
    auto it = hash_table<T>.find(k);
    if(it == hash_table<T>.end()) {
        *get_status = 0;
    }
    else {
        memcpy(value, &(hash_table<T>[k]), sizeof(T));
    }
    lock[k%LOCK_NUM].unlock_shared();
}

template <typename T>
void put(int k, T* value, int* put_status){
    *put_status = 1;
    lock[k%LOCK_NUM].lock_shared();
    auto it = hash_table<T>.find(k);
    if(it == hash_table<T>.end()){
        memcpy(&(hash_table<T>[k]), value, sizeof(T));
    }else {
        *put_status = 0;
    }
    lock[k%LOCK_NUM].unlock_shared();
}

template <typename T>
void Server_SendRespond(int sock, RequestInfo<T>* message){
    int n_s;
    T value;
    int get_status;
    int put_status;
    ResponseInfo<T>* response;

    int k = message->hash_key;
    response->operation_type = message->operation_type;
    response->hash_key = message->hash_key;
    if(lock[k%LOCK_NUM].try_lock_shared()){
        if(message->operation_type == PUT){

            put(k, &message->hash_value, &put_status);
            response->status = put_status;

            // put_status = 1 success
            if(put_status){
                memcpy(&response->hash_value, &message->hash_value, sizeof(T));
            }
        }else{
            get(k, &value, &get_status);
            response->status = get_status;

            // get_status = 1 success
            if(get_status){
                memcpy(& response->hash_value, &value, sizeof(T));
            }
        }
    }else{
        response->status = 2; // if didn't get lock, then status is 2, resend
    }
    n_s = send(sock, response, sizeof(*response), 0);
    if (n_s < 0) error("ERROR writing to socket");
}



int main()
{
    int opt = 1, max_clients = 3;
    int sockfd, newsockfd, client_socket[3], portno, pid, i, addrlen, max_sd, sd, activity;
    fd_set readfds;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char *message = "Greeting from \r\n";
    RequestInfo<int>* request;

    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
        error("setsockopt");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5000;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
        error("ERROR on binding");

    if(listen(sockfd,3) < 0)
        error("ERROR on listening");

    addrlen = sizeof(serv_addr);
    puts("Waiting for connections ...");

    clilen = sizeof(cli_addr);

    while(1){
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(sockfd, &readfds);
        max_sd = sockfd;

        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;

        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(sockfd, &readfds))
        {
            if ((newsockfd = accept(sockfd, (struct sockaddr *)&serv_addr, (socklen_t*)&addrlen))<0)
                error("ERROR on accepting");

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , newsockfd , inet_ntoa(serv_addr.sin_addr) , ntohs
                    (serv_addr.sin_port));

            //send new connection greeting message
            if(send(newsockfd, message, strlen(message), 0) != strlen(message))
                error("ERROR on sending greeting");

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = newsockfd;
                    printf("Adding to list of sockets as %d\n" , i);
                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++){
            sd = client_socket[i];

            if (FD_ISSET( sd , &readfds)){
                //Check if it was for closing , and also read the
                //incoming message
                if (recv(sd, request, sizeof(*request), 0) < 0)
                    error("ERROR reading from socket");

                if (recv(sd, request, sizeof(*request), 0) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&serv_addr , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" ,
                           inet_ntoa(serv_addr.sin_addr) , ntohs(serv_addr.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }else{
                    Server_SendRespond<int>(sd, request);
                }
            }
        }

    }

    return 0;
}


