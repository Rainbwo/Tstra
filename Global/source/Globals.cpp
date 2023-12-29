#include "Globals.h"

namespace astra
{
	bool running_in_matlab = false;
	_TstraExport bool cudaAvailabe()
	{
#ifdef ASTRA_CUDA

#else
#endif
	}
}
