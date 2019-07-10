#pragma once
#include <string>
#include <assert.h>
namespace LevenDB {
	class Slice {
	public:
		Slice():data_(""),size_(0){}
		Slice(const char* d,size_t n):data_(d),size_(n){}
		Slice(const std::string &s):data_(s.data()),size_(s.size()){}
		Slice(const char*s):data_(s),size_(strlen(s)){}
		Slice(const Slice&) = default;

		Slice& operator=(const Slice&) = default;
		const char * data() const { return data_; }
		size_t size() const { return size_; }
		bool empty() const { return size_ == 0; }
		char operator[](size_t n) const {
			assert(n < size_);
			return data_[n];
		}
		void clear() {
			data_ = "", size_ = 0;
		}
		void remove_prefix(size_t n) {
			assert(n <= size_);
			data_ += n;
			size_ -= n;
		}
		//RVO
		std::string ToString() const {
			return std::string(data_, size_);
		}
		// Three-way comparison.  Returns value:
		//   <  0 iff "*this" <  "b",
		//   == 0 iff "*this" == "b",
		//   >  0 iff "*this" >  "b"
		//	the first byte that does not match compare
		int compare(const Slice&b) const;

		bool starts_with(const Slice&x) const {

		}
	private:
		const char* data_;
		size_t size_;
	};
	inline bool operator==(const Slice& x, const Slice& y) {
		return ((x.size() == y.size()) &&
			(memcmp(x.data(), y.data(), x.size()) == 0));
	}
	inline bool operator!=(const Slice& x, const Slice& y) {
		return !(x == y);
	}
	inline int Slice::compare(const Slice& b) const {
		const size_t minSlice = (this->size_ < b.size_) ? size_ : b.size_;
		bool result = memcmp(this->data_, b.data_, minSlice);
		if (result != 0) {
			return this->size_ > b.size_, size_ ? 1 : -1;
		}
		return result;
	}
}