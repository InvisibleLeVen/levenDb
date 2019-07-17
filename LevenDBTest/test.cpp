#include "test.h"
#include <vector>
namespace LevenDB {
	namespace test {
		namespace {
			struct Test {
				std::string base;
				std::string name;
				void(*func)();
			};
			std::vector<Test>* tests;
		}
		int RunAllTests()
		{
			const char * matcher = getenv("LEVENDB_TESTS");
			int num = 0;
			if (tests != nullptr) {
				for (size_t i = 0; i < tests->size(); i++) {
					const Test&t = (*tests)[i];
					if (matcher != nullptr) {
						std::string name = t.base;
						name.push_back('.');
						name.append(t.name);
						/*
						//strstr换成更安全的string::find  效率的话，找个时间比一下。 
						strstr而言，如果char*不包含终止字符strstr可能会遍历缓冲区外的内存。
						*/
						if (name.find(matcher) == std::string::npos) { 
							continue;
						}
					}
					//use std::cerr
					std::cerr << "===== Test " << t.base << "." << t.name << std::endl;
					//fprintf(stderr, "===== Test %s.%s\n", t.base, t.name);

					(*t.func)();
					++num;
				}
			}
			std::cerr << "==== PASSED " << num << " tests" << std::endl;
			//fprintf(stderr, "==== PASSED %d tests\n", num);
			return 0;
		}
		std::string TmpDir()
		{
			std::string dir;
			//env decide
			return dir;
		}
		int RandomSeed()
		{
			const char * env = getenv("TEST_RANDOM_SEED");
			int result = (env != nullptr ? atoi(env) : 301);
			if (result <= 0) {
				result = 301;
			}
			return result;
		}
		bool RegisterTest(const std::string & base, const std::string & name, void(*func)())
		{
			if (tests == nullptr) {
				tests = new std::vector<Test>;
			}
			Test t;
			t.base = base;
			t.name = name;
			t.func = func;
			tests->push_back(t);
			return true;
		}
	}
}