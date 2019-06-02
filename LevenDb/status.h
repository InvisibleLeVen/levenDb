#pragma once
#include <memory>
#include <string>
namespace LevenDB {
	class Status {
	public:
		Status() noexcept : state_(nullptr) {}
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
	};

}