#include <iostream> // cout, cin
#include <sys/socket.h> // socket, bind, listen, accept
#include <netinet/in.h> // IPPROTO_TCP, sockaddr_in,
                        // htons/ntohs, INADDR_ANY
#include <unistd.h> // close
#include <arpa/inet.h> // inet_ntop/inet_atop

#define BUFFER_SIZE 1024

using namespace std;

int main(int _argc, char** _argv) {
	cout << "Starting Demo_SocketServer ..."  << endl;

	if (_argc != 2) {				// first argument is running program, second is port
		cout << "Usage: ./Demo_SocketServer <port>"  << endl;
		exit(EXIT_FAILURE);
	}

	int port =  atoi(_argv[1]); // w/o check before we don´t know if its the right env variable

	int passiveSocket = socket(AF_INET, SOCK_STREAM, 0);		// erste socket
	if (passiveSocket == -1) {
		perror("socket construction failed..");
		exit(EXIT_FAILURE);
	}

	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;		// adresse in apv4
	serverAddr.sin_addr.s_addr = INADDR_ANY;			// 0.0.0.0 is equivalent
	serverAddr.sin_port = htons(port);		// irgendein freier port
	int res = ::bind(passiveSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if (res == -1) {
		perror("bind failed..");
		exit(EXIT_FAILURE);
	}


	res =listen(passiveSocket, 5);
	if (res == -1) {
		perror("listen failed..");
	}

	cout << "Server listening for clients ..." << endl;
	int commSocket = accept(passiveSocket, nullptr, nullptr);

	if (commSocket == -1) {
		perror("accept failed..");
	} else {
		sockaddr_in peerAddr;
		//int peerAddrLen = sizeof(peerAddr);
		socklen_t peerAddrLen = sizeof(peerAddr);

		getpeername(commSocket, (struct sockaddr*)&peerAddr, &peerAddrLen);

		int port = ntohs(peerAddr.sin_port);
		char ipPeer[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &peerAddr.sin_addr, ipPeer, sizeof(ipPeer));



		cout << "Connection established with peer.." << ipPeer << " on Port " << port << endl;
	}

	cout << "Stopping Demo_SocketServer ..."  << endl;

	cin.get();
    return 0;
}
