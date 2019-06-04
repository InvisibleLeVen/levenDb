#include "status.hpp"
namespace LevenDB {
	std::string Status::ToString() const
	{
		if (c == kOk) return "OK";
		std::string result;
		switch (code())
		{
		case kNotFound:
			result = "NotFound :";
			break;
		case kCorruption:
			result = "Corruption: ";
			break;
		case kNotSupported:
			result = "Not Supported: ";
			break;
		case kInvalidArgument:
			result = "Invalid Argument: ";
			break;
		case kIOError:
			result = "IO Error: ";
			break;
		default:
			char tmp[30];
			snprintf(tmp, sizeof(tmp),
				"Unknown code(%d): ", static_cast<int>(code()));
			result = tmp;
			break;
		}
		return result.append(*state_);
	}
	Status::Status(Code code, const Slice& msg, const Slice& msg2) {
		assert(code != kOk);
		c = code;
		if (msg2.size() != 0)
			state_ = std::make_shared<std::string>((msg.ToString()));
		else
			state_ = std::make_shared<std::string>((msg.ToString().append(msg2.ToString())));
		
	}
}