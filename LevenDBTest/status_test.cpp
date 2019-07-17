#include "test.h"
#define MACRO_STRING(x)     #x
#define MACRO_EXPAND(x)     MACRO_STRING(x)
namespace LevenDB {
	TEST(Status, MoveConstructor) {
		{
			Status ok = Status::OK();
			Status ok2 = std::move(ok);

			ASSERT_TRUE(ok2.IsOk());
		}
		{
			Status status = Status::NotFound("custom NotFound status message");
			Status status2 = std::move(status);
			ASSERT_TRUE(status2.IsNotFound());
			ASSERT_EQ("NotFound: custom NotFound status message", status2.ToString());
		}
		{
			Status self_moved = Status::IOError("custom IOError status message");
			Status& self_moved_reference = self_moved;
			self_moved_reference = std::move(self_moved);
		}
	}
	
}

int main() {
	return LevenDB::test::RunAllTests();
}