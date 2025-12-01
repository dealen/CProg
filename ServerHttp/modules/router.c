#include "router.h"
#include <string.h>
#include <stdio.h>

static Route routes[] = {
	{"GET", "/", "Home Page", 200},
	{"GET", "/about", "About Page", 200},
	{"GET", "/contact", "Contact Page", 200},
	{"*", "*", "404 Not Found", 404}
};

static int routes_count = sizeof(routes) / sizeof(routes[0]);

static int path_matches(const char *pattern, const char *path) {
	return strcmp(pattern, path) == 0 || strcmp(pattern, "*") == 0;
}

static int method_matches(const char *pattern, const char *method) {
	return strcmp(pattern, method) == 0 || strcmp(pattern, "*") == 0;
}

int route_handle(const HttpRequest *req, char *response_body, size_t body_size) {
	if (!req || !response_body) {
		return 500;
	}

	for (int i = 0; i < routes_count; i++) {
		Route *route = &routes[i];

		if (method_matches(route->method, req->method) && path_matches(route->path, req->path)) {
			
			strncpy(response_body, route->response, body_size - 1);
			response_body[body_size - 1] = '\0';
			return route->status_code;
		}
	}

	strncpy(response_body, "500 Internal Server Error", body_size - 1);
	return 500;
}
