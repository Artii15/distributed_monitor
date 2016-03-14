#ifndef SYNCHRONIZATION_REQUEST_MPI_TYPE
#define SYNCHRONIZATION_REQUEST_MPI_TYPE

#include <mpi.h>

class synchronization_request_mpi_type {
	public:
		synchronization_request_mpi_type();
		~synchronization_request_mpi_type();
		const MPI_Datatype& getType();

		static synchronization_request_mpi_type* instance;
	private:
		MPI_Datatype type;
};

#endif