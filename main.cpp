#include "inc/monitor.h"
#include "inc/action_stub.h"

int main() {
	monitor m;
	action_stub a;

	m.register_process(1);

	m.call(&a);

	return 0;	
}
