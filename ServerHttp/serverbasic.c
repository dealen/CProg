#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
	// tworzenie socketu
	int server = socket(AF_INET, SOCK_STREAM, 0);

	// konfiguracja aresu (port 8080)
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	// bindowanie socketu do portu
	bind(server, (struct sockaddr*)&addr, sizeof(addr));

	// nasłuchiwanie
	listen(server, 1);

	printf("Server działa na http://localhost:8080\n");

	// akceptowanie jednego połączenia
	int client = accept(server, NULL, NULL);

	// wysyłanie odpowiedzi
	char *response = "HTTP/1.1 200 OK\r\n\r\nHello WOrld from c!";
	write(client, response, strlen(response));

	// sprzatanie
	close(client);
	close(server);

	return 0;
}
