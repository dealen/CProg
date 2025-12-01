#ifndef ROUTER_H
#define ROUTER_H

#include "http.h"

typedef struct {
	char method[16];
	char path[256];
	char response[1024];
	int status_code;
} Route;

int route_handle(const HttpRequest *req, char *response_body, size_t body_size);

#endif
