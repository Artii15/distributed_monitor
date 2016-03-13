#include "../inc/monitor.h"
#include <iostream>

using namespace std;

monitor::monitor(process_id id, communicator* comm) {
	this->comm = comm;
	this->id = id;
	register_process(id);
	time = 0;
}

void monitor::call(action *action) {
	lock();
	action->perform(this);
	unlock();
}


void monitor::lock() {
	synchronization_request lock_request(time, id);
	comm->send(&lock_request, &processes_ids);
}

void monitor::unlock() {

}

void monitor::wait() {
		
}

void monitor::signal() {

}

void monitor::register_process(process_id id) {
	processes_ids.insert(id);
}
