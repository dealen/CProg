#ifndef HTTP_H
#define HTTP_H

#include <sys/types.h>

// struct representing http request
typedef struct {
	char method[16]; // get, post etc
	char path[256]; // api/user123
	char version[16]; // http/1.1
	char raw[4096]; // raw data for debugging
} HttpRequest;

// parsing http request
int http_parse_request(const char *buffer, ssize_t bytes, HttpRequest *req);

// creating http response 
int http_build_response(char *buffer, size_t buffer_size, int status_code, const char *body);

// helper: zwraca tekst statusu (200 -> "OK", 404 -> "Not found")
const char* http_status_text(int code);

#endif
