#pragma once
#include <memory>

// Date: 2019.1.31
// Author: Nyarll

template <class T>
class Singleton
{
public:
	static T& GetInstanceRef()
	{
		static typename T::singleton_pointer_type s_singleton(T::createInstance());

		return getReference(s_singleton);
	}

private:
	typedef std::unique_ptr<T> singleton_pointer_type;

	inline static T *createInstance() { return new T(); }

	inline static T &getReference(const singleton_pointer_type &ptr) { return *ptr; }

protected:
	Singleton() {}

private:
	Singleton(const Singleton &) = delete;
	Singleton& operator=(const Singleton &) = delete;
	Singleton(Singleton &&) = delete;
	Singleton& operator=(Singleton &&) = delete;
};

