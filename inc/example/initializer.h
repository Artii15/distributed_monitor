#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <mpi.h>
#include "../monitor.h"
#include "../communicators/mpi_communicator.h"
#include "../synchronizer/synchronizer.h"

class initializer {
	public:
		initializer();

		void start();
		void finish();

		static void* listening_task(void* arg);
	private:
		environment_descriptor env;
		MPI_Comm duplicated_world_comm;

		mpi_communicator* comm;
		synchronizer* proc_synchronizer;
		resources_synchronizer* res_synchronizer;
};

#endif
