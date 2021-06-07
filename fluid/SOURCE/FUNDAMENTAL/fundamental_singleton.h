#ifndef __FUNDAMENTAL_SINGLETON__
#define __FUNDAMENTAL_SINGLETON__

template<typename T>
class FUNDAMENTAL_SINGLETON {

public:
	static T& instance()
	{
		static const std::unique_ptr<T> instance{ new T{} };
		return *instance;
	}

	FUNDAMENTAL_SINGLETON( const FUNDAMENTAL_SINGLETON& ) = delete;
	FUNDAMENTAL_SINGLETON& operator= ( const FUNDAMENTAL_SINGLETON ) = delete;

protected:
	FUNDAMENTAL_SINGLETON() {}
};
#endif