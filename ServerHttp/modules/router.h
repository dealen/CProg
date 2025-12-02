#ifndef ROUTER_H
#define ROUTER_H

#include "http.h"

typedef struct {
	char method[16];      // HTTP method (GET, POST, etc.) or "*" for wildcard
	char path[256];       // URL path or "*" for wildcard
	char response[1024];  // Response body content
	int status_code;      // HTTP status code to return
} Route;

int route_handle(const HttpRequest *req, char *response_body, size_t body_size);

#endif
