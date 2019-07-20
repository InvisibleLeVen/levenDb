#include "env.h"
namespace LevenDB {
	Env::~Env() = default;
	
	Status Env::NewAppendableFile(const std::string& fname, WritableFile** result) {
		return Status::NotSupported("NewAppendableFile", fname);
	}
	
	SequentialFile::~SequentialFile() = default;

	RandomAccessFile::~RandomAccessFile() = default;

	WritableFile::~WritableFile() = default;

	Logger::~Logger() = default;

	FileLock::~FileLock() = default;

	void Log(Logger* info_log, const char* format, ...) {
		if (info_log != nullptr) {
			va_list ap;
			__crt_va_start(ap, format);
			info_log->Logv(format, ap);
			__crt_va_end(ap);
		}
	}

	static Status DoWriteStringToFile(Env* env, const Slice& data, const std::string& fname, bool should_sync) {
		WritableFile* file;
		Status s = env->NewWritableFile(fname, &file);
		if (!s.IsOk()) {
			return s;
		}
		s = file->Append(data);
		if (s.IsOk() && should_sync) {
			s = file->Sync();
		}
		if (s.IsOk()) {
			s = file->Close();
		}
		delete file;
		if (!s.IsOk()) {
			env->DeleteFile(fname);
		}
		return s;
	}


	Status WriteStringToFile(Env * env, const Slice & data, const std::string & fname)
	{
		return DoWriteStringToFile(env,data,fname,false);
	}
	Status WriteStringToFileSync(Env * env, const Slice & data, const std::string & fname)
	{
		return DoWriteStringToFile(env, data, fname, true);
	}

	Status ReadFileToString(Env * env, const std::string & fname, std::string & data)
	{
		data.clear();
		SequentialFile* file;
		Status s = env->NewSequentialFile(fname, &file);
		if (!s.IsOk()) {
			return s;
		}
		static const int kBufferSize = 8192;
		char* space = new char[kBufferSize];
		while (true) {
			Slice fragment;
			s = file->Read(kBufferSize, fragment, space);
			if (!s.IsOk()) {
				break;
			}
			data.append(fragment.data(), fragment.size());
			if (fragment.empty()) {
				break;
			}
		}
		delete[] space;
		delete file;
		return s;
	}

	EnvWrapper::~EnvWrapper(){}

}