#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include "utils/utils.h"
#include "modules/http.h"

int main() {
    // tworzenie socketu
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // konfiguracja adres
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    // bindowanie do portu
    if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    // nasłuchiwanie
    if (listen(server, 10) < 0) {
        perror("listen");
        return 1;
    }

    print_time();
    printf("Server dziala na http://localhost:8080\n");
    printf("Nacisnij Ctrl+C aby zatrzymać\n\n");
    fflush(stdout);

    int request_num = 0;

    while(1) {
        request_num++;

	print_time();
        printf("[%d] Czekam na polaczenie...\n", request_num);
        fflush(stdout);

        // blokowanie programu az ktoś się połaczy
        int client = accept(server, NULL, NULL);
        if (client < 0) {
            perror("accept");
            continue;
        }
        
	print_time();
        printf("[%d] Ktoś się połaczył! Socket clienta: %d\n", request_num, client);

        // czekanie na informacje od clienta
        char buffer[4096] = {0};
        size_t bytes = read(client, buffer, sizeof(buffer) -1);

	print_time();
	printf("[%d] === Otrzymałem %ld bajtów ---\n", request_num, bytes);

	// parsing request
	HttpRequest req;
	if (http_parse_request(buffer, bytes, &req) < 0){
		print_time();
		printf("[%d] Błąd parsowania żądania\n", request_num);
		close(client);
		continue;
	}

	print_time();
	printf("[%d] %s %s %s\n", request_num, req.method, req.path, req.version);

	// creating response
	const char *body = "Hello World";
	char response[1024];
	int len = http_build_response(response, sizeof(response), 200, body);

	if (len < 0) {
		print_time();
		printf("[%d] Błąd tworzenia odpowiedzi\n", request_num);
		close(client);
		continue;
	}

	print_time();
        printf("[%d] Wysylanie odpowiedzi (%d bajtów)...\n", request_num, len);
        ssize_t sent = write(client, response, len);
        if (sent < 0) {
            perror("write");
        } else {
            printf("[%d] Wysłano %ld bajtów\n", request_num, sent);
        }

        // zamykanie socketu clienta!!!
        close(client);
	print_time();
        printf("[%d] Zamknięcie socketu clienta\n\n", request_num);
	fflush(stdout);
    }

    close(server);
    return 0;
}
