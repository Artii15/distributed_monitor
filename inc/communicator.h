#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "synchronization_request.h"
#include "monitor.h"
#include "guarded_section_descriptor.h"
#include "pending_request.h"
#include <map>
#include <queue>

typedef struct REQUEST_TAG {
	const static uint16_t LOCK_REQUEST = 1;
} REQUEST_TAG;

class communicator {
	public:
		bool enabled;
		communicator(uint32_t process_id, unsigned int number_of_processes);
		void send_lock_request(guarded_section_descriptor);
		virtual void listen();

	protected:
		virtual void broadcast_sync_request(synchronization_request* request) = 0;
		virtual synchronization_request* receive_message() = 0;

		uint32_t time;
		uint32_t process_id;
		unsigned int number_of_processes;

	private:
		std::map<uint16_t, std::priority_queue<pending_request, std::vector<pending_request>, std::greater<pending_request> > > lock_requests;
		std::map<uint16_t, std::priority_queue<pending_request, std::vector<pending_request>, std::greater<pending_request> > > pending_requests;

		void handle_message(synchronization_request* message);
		void handle_lock_request(synchronization_request* request);
};

#endif
