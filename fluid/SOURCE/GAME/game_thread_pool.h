#ifndef __GAME_THREAD_POOL__
#define __GAME_THREAD_POOL__

#include <functional>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>

class GAME_THREAD_POOL
{

public:

	GAME_THREAD_POOL()
	{
		NumOfThreads = std::thread::hardware_concurrency();

		ready_list.resize( NumOfThreads );
		processed_list.resize( NumOfThreads );

		for ( int t = 0; t < NumOfThreads; t++ )
		{
			workers.push_back( std::thread( &GAME_THREAD_POOL::worker_thread, this, t ) );
		}
	}

	~GAME_THREAD_POOL()
	{
		for ( auto& w : workers )
		{
			w.join();
		}
	}


	void worker_thread( unsigned int t )
	{
		while ( true )
		{
			MutexLock.lock();
			bool is_ready = ready_list[t];
			MutexLock.unlock();

			if ( is_ready )
			{
				tasks[t]();

				MutexLock.lock();
				processed_list[t] = true;
				ready_list[t] = false;
				MutexLock.unlock();
			}
		}
	}

	void push_task( std::function<void()> f )
	{
		tasks.push_back( f );
	}

	void run( void )
	{
		MutexLock.lock();
		for ( int t = 0; t < NumOfThreads; t++ )
		{
			ready_list[t] = true;
		}
		MutexLock.unlock();

		bool processed = false;

		while ( !processed )
		{
			bool done = true;

			MutexLock.lock();
			for ( int t = 0; t < NumOfThreads; t++ )
			{
				bool v;

				v = processed_list[t];

				if ( v == false )
				{
					done = false;
				}
			}
			MutexLock.unlock();

			if ( done )
			{
				processed = true;
			}
		}
		MutexLock.lock();
		for ( int t = 0; t < NumOfThreads; t++ )
		{
			processed_list[t] = false;
		}
		MutexLock.unlock();

		tasks.clear();
	}

private:

	int										NumOfThreads;
	std::mutex								MutexLock;
	std::deque<bool>						ready_list;
	std::deque<bool>						processed_list;
	std::vector<std::thread>				workers;
	std::vector< std::function<void()> >	tasks;
};

#endif