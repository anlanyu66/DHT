//
// Created by Anlan Yu on 2/3/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <atomic>
#include <arpa/inet.h>
#include <string>
#include "messageType.h"

using namespace std;
#define KEY_RANGE 100000
#define PUT_PERCENT 0.4

atomic_int put_success;

atomic_int get_success;

atomic_int put_fail;

atomic_int get_fail;



void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int findnode(int key){
    return key%3;
}

template<typename T>
int sent_message()
{
    int sockfd, portno;
    struct sockaddr_in serv_addr;

    portno = 5000;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    int n;
    // Create message
    RequestInfo<T>* info;
    int hash_key = rand()%KEY_RANGE;
    info->hash_key = hash_key;
    int node = findnode(hash_key);

    //fulfill request->operation_type;
    if(rand()%100 < PUT_PERCENT*100) {
        OperationType operation_type = PUT;
        info->operation_type = operation_type;
    }else {
        OperationType operation_type = GET;
        info->operation_type = operation_type;
    }

    if(info->operation_type == PUT) {
        T value = (T) rand();
        info->hash_value = value;
    }else {
        info->hash_value = NULL;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("128.180.206.218");
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    n = send(sockfd,info,sizeof(*info),0);
    close(sockfd);
    return n;
}

template<typename T>
int receive_message(int sockfd)
{
    int n;
    ResponseInfo<T>* info;
    n = recv(sockfd, info, sizeof(*info), 0);
    if(info->operation_type == PUT) {
        //cout << "PUT " << info->hash_key;

        if(!info->status){
            //cout <<" SUCCESS, ";
            put_success += 1;
        }else{
            //cout << " FAIL, ";
            put_fail += 1;
        }
    }else {
        //cout << "GET " << info->hash_key;
        if(!info->status){
            //cout << " SUCCESS, ";
            get_success += 1;
        }else{
            //cout << " FAIL, ";
            get_fail += 1;
        }
    }

//    if (n < 0)
//        error("ERROR reading from socket");
//
    close(sockfd);
    return n;
}


int main()
{
    int sockfd, n_sent, n_recv;

    n_sent = sent_message<int>();
//    n_recv = receive_message<int>(sockfd);
    return 0;
}