#ifndef SYNCHRONIZATION_REQUEST_H
#define SYNCHRONIZATION_REQUEST_H

#include <stdint.h>

struct synchronization_request {
	uint32_t time;
	uint32_t pid;
	uint8_t tag;

	synchronization_request();
	synchronization_request(uint32_t time, uint32_t pid, uint32_t tag);

	bool operator>(const synchronization_request& request) const;

	bool operator==(const synchronization_request& request) const;

	bool operator<(const synchronization_request& request) const;
};

#endif
