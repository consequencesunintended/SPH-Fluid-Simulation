#ifndef __GAME_THREAD_MANAGER__
#define __GAME_THREAD_MANAGER__

#include "fundamental_singleton.h"
#include "game_thread_pool.h"
#include <functional>

class GAME_THREAD_MANAGER : public FUNDAMENTAL_SINGLETON< GAME_THREAD_MANAGER >
{
public:

	void add_job( std::function<void()> f )
	{
		thread_pool.add_job( f );
	}

	void run( void )
	{
		thread_pool.run();
	}

	int get_num_avaialable_threads( void )
	{
#ifndef DISABLE_THREADING
		return thread_pool.get_num_avaialable_threads();
#else
		return 1;
#endif
	}

private:

	GAME_THREAD_POOL thread_pool;
};
#endif