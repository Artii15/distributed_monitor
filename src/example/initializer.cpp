#include "../../inc/example/initializer.h"
#include "../../inc/example/buffer.hpp"
#include "../../inc/example/prod_cons_monitor.h"
#include "../../inc/example/producer.h"
#include "../../inc/example/consumer.h"
#include <stdexcept>
#include <pthread.h>

#define THREADING_NOT_SUPPORTED 1
#define BUFSIZE 10

void* initializer::listening_task(void *arg) {
	communicator* comm = (communicator*)arg;
	comm->listen();	

	pthread_exit(NULL);
}

initializer::initializer() {
	int provided_thread_support;
	MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided_thread_support);

	if(provided_thread_support != MPI_THREAD_MULTIPLE) {
		MPI_Abort(MPI_COMM_WORLD, THREADING_NOT_SUPPORTED);
	}

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	srand(time(NULL) + rank);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	env.process_id = (uint32_t)rank;
	env.number_of_processes = (uint32_t)world_size;

	MPI_Comm_dup(MPI_COMM_WORLD, &duplicated_world_comm);
}

void initializer::start() {
	mpi_communicator comm(&env, &duplicated_world_comm);

	synchronizer proc_synchronizer(&comm, &env);
	resources_synchronizer res_synchronizer(&comm);

	buffer buf(BUFSIZE);
	res_synchronizer.register_resources(&buf);

	prod_cons_monitor mon(&proc_synchronizer, &res_synchronizer, &buf, env.process_id);

	pthread_t listening_thread;
	pthread_create(&listening_thread, NULL, &initializer::listening_task, (void*)&comm);

	if(env.process_id == 0) {
		producer producer_task(&mon);
		producer_task.run();
	}
	else {
		consumer consumer_task(&mon);
		consumer_task.run();
	}

	pthread_join(listening_thread, NULL);
}

void initializer::finish() {
	MPI_Comm_free(&duplicated_world_comm);

	MPI_Finalize();
}
