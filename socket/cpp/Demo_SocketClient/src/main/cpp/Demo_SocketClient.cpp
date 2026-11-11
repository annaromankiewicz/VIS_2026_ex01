#include <iostream> // cout, cin
#include <sys/socket.h> // socket, bind, listen, accept
#include <netinet/in.h> // IPPROTO_TCP, sockaddr_in,
                        // htons/ntohs, INADDR_ANY
#include <unistd.h> // close
#include <arpa/inet.h> // inet_ntop/inet_atop
#include <string.h> // strerror
#include <semaphore.h> // sem_init
#include <pthread.h>

#define BUFFER_SIZE 1024

using namespace std;

int main(int _argc, char** _argv) {
	cout << "Starting Demo_SocketClient ..."  << endl;


	if (_argc != 3) {		// IP and port
		cout << "Usage: Demo_SocketClient <IP address> <port>" << endl;
		exit(EXIT_FAILURE);
	}

	int commSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (commSocket == -1) {
		perror("socket creation failed...");
		exit(EXIT_FAILURE);
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;		// adresse in apv4
	serverAddr.sin_port = htons(atoi(_argv[2]));		// irgendein freier port

	int res = inet_pton(AF_INET, _argv[1], &serverAddr.sin_addr);		// wir reden mit uns selbst
	if (res == -1) {
		perror("inet_pton failed...; IP could not be resolved");
	}

	res = connect(commSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (res == -1) {
		perror("connection  failed...");
	} else {
		cout << "Connected!" << endl;
	}

	cout << "Stopping Demo_SocketClient ..."  << endl;

	return 0;
}
