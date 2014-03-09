// select被用来监听多个fd的IO状况。
// 这里测试select的server代码
// 2014-3-8 21:37
// bless malaysia MH370, hope every member of this flight safe

#include <sys/select.h>
#include <sys/time.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

// try to build 1000 port for select
const unsigned int MAX_PORT_NUM = 2000;
const unsigned int START_PORT_NUM = 7777;// start port num

int build_listen(unsigned int port)
{
	//check port
	if (port <= 0) {
		return -1;
	}

	int listenfd1;
	struct sockaddr_in serv_addr1;
	listenfd1 = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero((char*)&serv_addr1, sizeof(serv_addr1));
	serv_addr1.sin_family = AF_INET;
	serv_addr1.sin_port = htons(port);
	serv_addr1.sin_addr.s_addr = INADDR_ANY;
	
	bind(listenfd1, (struct sockaddr*) &serv_addr1, sizeof(serv_addr1));
	listen(listenfd1, 5);
	
	return listenfd1;
}


void build_multiple_ports(int* listenfd_arr)
{
	// from 7777 to 8777,
	// we build listen socket
	for (int i = 0;i < MAX_PORT_NUM; i++) {
		listenfd_arr[i] = build_listen(START_PORT_NUM + i);
	}
}

void print_multiple_ports(int* listenfd_arr, int size)
{
	for (int i = 0; i < size; i++) {
		printf("%d ", listenfd_arr[i]);
	}
	printf("\n");
}

int main(int argc, char** argv)
{

	int listenfd_arr[MAX_PORT_NUM];
	build_multiple_ports(listenfd_arr);
	
	print_multiple_ports(listenfd_arr, MAX_PORT_NUM);

	int maxfd = listenfd_arr[MAX_PORT_NUM - 1];
	fd_set allset, rset;
	
	// fullfill FD_SET with listenfd_arr;
	FD_ZERO(&allset);
	for (int i = 0;i < MAX_PORT_NUM; i++) {
		FD_SET(listenfd_arr[i], &allset);
	}
	
	
	int clifd, clilen;
	struct sockaddr_in cli_addr;
	char buff[256];

	for (;;) {
		rset = allset;
		select(maxfd + 1, &rset, NULL, NULL, NULL);
		
		//printf("start to test\n");
		for (int i = 0; i < MAX_PORT_NUM; i++) {

			if (FD_ISSET(listenfd_arr[i], &rset)) {
				clilen = sizeof(cli_addr);
				clifd = accept(listenfd_arr[i], (struct sockaddr*)&cli_addr, 
						(socklen_t*)&clilen);
				bzero(buff, 256);

				read(clifd, buff, 256);
				printf("listenfd[%d] message is: %s\n", listenfd_arr[i], buff);
			}
		} //

		close(clifd);
	}
	
	for (int i = 0; i < MAX_PORT_NUM; i++) {
		close(listenfd_arr[i]);
	}

	return 0;
}
