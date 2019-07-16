#pragma once
#include <memory>
#include <string>
#include "slice.h"
namespace LevenDB {
	class Status {
	public:
		static Status OK() { return Status(); }

		static Status NotFound(const Slice& msg, const Slice& msg2 = Slice()) {
			return Status(kNotFound, msg, msg2);
		}
		static Status Corruption(const Slice& msg, const Slice& msg2 = Slice()) {
			return Status(kCorruption, msg, msg2);
		}
		static Status NotSupported(const Slice& msg, const Slice& msg2 = Slice()) {
			return Status(kNotSupported, msg, msg2);
		}
		static Status InvalidArgument(const Slice& msg, const Slice& msg2 = Slice()) {
			return Status(kInvalidArgument, msg, msg2);
		}
		static Status IOError(const Slice& msg, const Slice& msg2 = Slice()) {
			return Status(kIOError, msg, msg2);
		}

		Status() noexcept : state_(nullptr),c(kOk){}
		bool IsOk() const { return (code() == kOk); }
		bool IsNotFound() const { return code() == kNotFound; }
		bool IsCorruption() const { return code() == kCorruption; }
		bool IsIOError() const { return code() == kIOError; }
		bool IsNotSupportedError() const { return code() == kNotSupported; }
		bool IsInvalidArgument() const { return code() == kInvalidArgument; }
		std::string ToString() const;
	private:
		enum Code {
			kOk = 0,
			kNotFound = 1,
			kCorruption = 2,
			kNotSupported = 3,
			kInvalidArgument = 4,
			kIOError = 5
		};
		//这里把code和message分开了，不在一个字符串中表示。
		//message储存在state_，一个智能指针保管
		//也不需要自定义拷贝构造函数，使用编译器生成的拷贝构造函数就可以了，msg拷贝会对state_增加一次引用次数
		//复制赋值运算符和移动赋值运算符也是使用编译器生成的
		//这是the rule of zero设计原则
		std::shared_ptr<std::string> state_;
		Code c;
		Code code() const {return c;}
		Status(Code code, const Slice& msg, const Slice& msg2);
	};

}