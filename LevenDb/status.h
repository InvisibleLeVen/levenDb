#pragma once
#include <memory>
#include <string>
class Slice;
namespace LevenDB {
	class Status {
	public:
		static Status OK() { return Status(); }

		static Status NotFound(const Slice& msg, const Slice& msg2);
		static Status Corruption(const Slice& msg, const Slice& msg2);
		static Status NotSupported(const Slice& msg, const Slice& msg2);
		static Status InvalidArgument(const Slice& msg, const Slice& msg2);
		static Status IOError(const Slice& msg, const Slice& msg2);

		Status() noexcept : state_(nullptr) {}
		bool ok() const { return (state_ == nullptr); }
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
		//    state_[0..3] == length of message
		//    state_[4]    == code
		//    state_[5..]  == message
		std::shared_ptr<std::string> state_;
		Code code() const {
			return (state_ == nullptr) ? kOk : static_cast<Code>((*state_)[4]);
		}
		Status(Code code, const Slice& msg, const Slice& msg2);
	};

}