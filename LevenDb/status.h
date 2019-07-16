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
		//�����code��message�ֿ��ˣ�����һ���ַ����б�ʾ��
		//message������state_��һ������ָ�뱣��
		//Ҳ����Ҫ�Զ��忽�����캯����ʹ�ñ��������ɵĿ������캯���Ϳ����ˣ�msg�������state_����һ�����ô���
		//���Ƹ�ֵ��������ƶ���ֵ�����Ҳ��ʹ�ñ��������ɵ�
		//����the rule of zero���ԭ��
		std::shared_ptr<std::string> state_;
		Code c;
		Code code() const {return c;}
		Status(Code code, const Slice& msg, const Slice& msg2);
	};

}