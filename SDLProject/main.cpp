#include "AsteroidsGame.h"
#include "ClientInfo.h"
#include "Server.h"
#include <thread>

using namespace std;

void clientMode(char* host, int port) {
	ClientInfo::initInstance(host, port);
	AsteroidsGame g;
	g.start();
}
void severMode(int port) {
	Server s;
	thread serverThread([port, &s]() {
		s.start(port);
	});
	const char* x = "localhost";
	char* host = (char*)x;
	clientMode(host, port);
	s.stop();
	serverThread.join();
}

int main(int ac, char** av) {
	if (SDLNet_Init() < 0) {
		cout << "Error: " << SDLNet_GetError() << endl;
		cout << "Connected: " << ClientInfo::instance()->getClientId() << endl;
		exit(1);
	}
	if (ac == 3 && strcmp(av[1], "server") == 0) {
		severMode(atoi(av[2]));
	}
	else if (ac == 4 && strcmp(av[1], "client") == 0) {
		clientMode(av[2], atoi(av[3]));
	}
	else {
		cout << "Usage: " << endl;
		cout << " " << av[0] << " client host port " << endl;
		cout << " " << av[0] << " server port " << endl;
	}
}



