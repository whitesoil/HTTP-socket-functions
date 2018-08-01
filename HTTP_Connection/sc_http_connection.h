#ifndef WEBSERVER_HTTP_SOCKET_H

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <apr_pools.h> 
#include <apr_thread_pool.h>

#include "../HTTP_Request/src/sc_request_parser.h"
#include "../HTTP_Response/sc_http_response_constructor.h"

#define BUF_SIZE 10000

void
error_handling(std::string message)
{
    std::cerr << message << "\n";
    exit(1);
}

void
exit_proc(int sig){
    std::cout << "\nExiting\n";
    exit(1);
}

void
sc_signal_setup(){

    struct sigaction    sig_int_handler;

    //exiting with Ctrl-C
    sig_int_handler.sa_handler = exit_proc;
    sigemptyset(&sig_int_handler.sa_mask);
    sig_int_handler.sa_flags = 0;
    sigaction(SIGINT, &sig_int_handler, NULL);
}

void *
sc_http_proc(apr_thread_t * thd, void * data){
    apr_pool_t * pool = NULL;
     apr_pool_create(&pool, apr_thread_pool_get(thd));  

    int clnt_sock = *(int *)data; 
    char buf[BUF_SIZE];
     sc_http_request_t request; 
    sc_http_response_t response;
     sc_url_t url;
      if(read(clnt_sock, buf, BUF_SIZE) != -1){ 
        int status = sc_request_reader(buf,&request, &url);
         sc_res_version_set(&response, 1.1); 
        sc_res_status_code_set(&response, status); 
        sc_response_send(&response,url.path,clnt_sock); 
    }  

    close(clnt_sock); 
    apr_pool_destroy(pool);
}

int
sc_connection_setup(int argc, char *argv[]) {

    apr_initialize(); 
    apr_pool_t * pool = NULL; 
    apr_pool_create(&pool, NULL);  
    apr_thread_pool_t * tp = NULL; 
    apr_thread_pool_create(&tp, 10, 10, pool);  

    int serv_sock, clnt_sock; 
    socklen_t   adr_sz; 
    struct sockaddr_in serv_adr, clnt_adr; 
    pid_t pid;  

    if (argc != 2) { 
        std::cout << "Usage : " << argv[0] << " <port>\n";
        exit(1); 
    }  

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); 
    int enable = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)); 
    memset(&serv_adr, 0, sizeof(serv_adr)); 
    serv_adr.sin_family = AF_INET; 
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv_adr.sin_port = htons(atoi(argv[1]));  

    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1) 
        error_handling("bind() error"); 
    if(listen(serv_sock, 10)==-1) 
        error_handling("listen() error");  

    std::cout << "server is running... \n"
              << "Use Ctrl-C to stop\n";

    while(1) {
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &adr_sz);
        apr_thread_pool_push (tp, sc_http_proc, &clnt_sock, 0, NULL); 
    }

    close(serv_sock); 
    apr_thread_pool_destroy(tp); 
    apr_pool_destroy(pool); 
    apr_terminate();  

    return 0;
}

#endif //WEBSERVER_HTTP_SOCKET_H
