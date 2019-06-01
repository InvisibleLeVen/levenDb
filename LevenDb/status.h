#pragma once
#include <memory>
namespace LevenDB {
	class Status {
	public:
		Status() noexcept : status_(nullptr){}
		Status(const Status& rhs);
		Status& operator=(const Status& rhs);
		Status(Status&& rhs) noexcept { this->status_ = rhs.status_; }
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
		std::shared_ptr<char> status_;
	};

}