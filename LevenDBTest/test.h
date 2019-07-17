#pragma once
#include "../LevenDb/status.h"
#include <iostream>
#include <sstream>
namespace LevenDB {
	namespace test {
		int RunAllTests();
		std::string TmpDir();
		int RandomSeed();
		class Tester {
		private:
			bool ok_;
			std::string fname_;
			int line_;
			std::stringstream ss_;
		public:
			Tester(const std::string & f,int l): ok_(true),fname_(f),line_(l){}
			~Tester() {
				if (!ok_) {
					std::cerr << fname_ << ":" << line_ << ":" << ss_.str() << std::endl;
					//fprintf(stderr, "%s:%d:%s\n", fname_, line_, ss_);
					exit(1);
				}
			}
			Tester&& Set(bool b,const std::string &msg) {
				if (!b) {
					ss_ << "Assertion failure" << msg;
					ok_ = false;
				}
				return std::move(*this);
			}
			Tester&& IsOk(const Status &s) {
				if (!s.IsOk()) {
					ss_ << " " << s.ToString();
					ok_ = false;
				}
				return std::move(*this);
			}
#define BINARY_OP(name,op)											\
			template <class X,class Y>								\
			Tester&& name(const X &x, const Y& y) {					\
				if (!(x op y)) {									\
					ss_ << "failed: " << x << (" " #op " ") << y;	\
					ok_ = false;									\
				}													\
				return std::move(*this);							\
			}
			BINARY_OP(IsEq,==)
			BINARY_OP(IsNe,!=)
			BINARY_OP(IsGe,>=)
			BINARY_OP(IsGt,>)
			BINARY_OP(IsLe,<=)
			BINARY_OP(IsLt,<) //学习元编程以后改成模板生成
#undef BINARY_OP
			template <class V>
			Tester && operator<<(const V& value) {
				if (!ok_) {
					ss_ << " " << value;
				}
				return std::move(*this);
			}
		};
#define ASSERT_TRUE(c) ::LevenDB::test::Tester(__FILE__,__LINE__).Set((c),#c)
#define	ASSERT_OK(s) ::LevenDB::test::Tester(__FILE__,__LINE__).IsOk(s)
#define ASSERT_EQ(a,b) ::LevenDB::test::Tester(__FILE__,__LINE__).IsEq((a),(b))
#define ASSERT_NE(a,b)::LevenDB::test::Tester(__FILE__,__LINE__).IsNe((a),(b))
#define ASSERT_GE(a,b)::LevenDB::test::Tester(__FILE__,__LINE__).IsGe((a),(b))
#define ASSERT_GT(a,b)::LevenDB::test::Tester(__FILE__,__LINE__).IsGt((a),(b))
#define ASSERT_LE(a,b)::LevenDB::test::Tester(__FILE__,__LINE__).IsLe((a),(b))
#define ASSERT_LT(a,b)::LevenDB::test::Tester(__FILE__,__LINE__).IsLt((a),(b))

#define TCONCAT(a,b) TCONCAT1(a,b)
#define TCONCAT1(a,b) a##b

#define TEST(base,name)															\
		class TCONCAT(_Test_, name) :public base {								\
		public:																	\
			void _Run();														\
			static void _RunIt() {												\
				TCONCAT(_Test_, name) t;										\
				t._Run();														\
			}																	\
		};																		\
		bool TCONCAT(_Test_ignored_, name) = ::LevenDB::test::RegisterTest(		\
			#base, #name, &TCONCAT(_Test_, name)::_RunIt);						\
		void TCONCAT(_Test_, name)::_Run()

		bool RegisterTest(const std::string& base, const std::string& name, void(*func)());
	}
}