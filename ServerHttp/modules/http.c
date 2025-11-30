#include "http.h"
#include <stdio.h>
#include <string.h>

const char* http_status_text(int code) {
	switch(code) {
		case 200: return "OK";
		case 404: return "Not Found";
		case 500: return "Internal Server Error";
		default: return "Unknown";
	}
}


int http_parse_request(const char *buffer, ssize_t bytes, HttpRequest *req) {

	if (bytes <= 0 || !buffer || !req){
		return -1;
	}

	//copying raw data
	strncpy(req->raw, buffer, sizeof(req->raw) -1);
	req->raw[sizeof(req->raw) - 1] = '\0';

	// parsing first line: GET /path HTTP/1.1
	if (sscanf(buffer, "%15s %255s %15s", req->method, req->path, req->version) != 3) {
		return -1;
	}

	return 0;
}

int http_build_response(char *buffer, size_t buffer_size, int status_code, const char *body) {
	if (!buffer || !body) {
		return -1;
	}

	size_t body_len = strlen(body);

        int len = snprintf(buffer, buffer_size,
            "HTTP/1.1 %d %s\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Content-Length: %zu\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s",
            status_code, http_status_text(status_code),
            body_len, body
        );
        
        return (len > 0 && (size_t)len < buffer_size) ? len : -1;
}
