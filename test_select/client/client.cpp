// client.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for bzero
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>


int main(int argc, char**argv)
{
	if (argc < 2) {
		return -1;
	}

	int conn_port = atoi(argv[1]);
	printf("client port is %d\n", conn_port);
	int sockfd, n;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in serv_addr;

	bzero((char*)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(conn_port);

	int ret = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (ret != 0) {
		printf("connect to server failed\n");
		return -1;
	}

	char buff[32];
	snprintf(buff, sizeof(buff), "client message with port [%d]\n", conn_port);
	write(sockfd, buff, sizeof(buff));

	close(sockfd);
	return 0;
}
