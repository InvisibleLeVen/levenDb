#include "status.h"
#include "slice.h"
namespace LevenDB {
	Status Status::NotFound(const Slice & msg, const Slice & msg2 = Slice())
	{
		return Status();
	}
}