#ifndef __GAME_THREAD_POOL__
#define __GAME_THREAD_POOL__

#include <functional>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>
#include <queue>

class GAME_THREAD_POOL
{

public:

	GAME_THREAD_POOL()
	{
		NumOfThreads = std::thread::hardware_concurrency();

		ReadyList.resize( NumOfThreads );
		ProcessedList.resize( NumOfThreads );

		for ( int t = 0; t < NumOfThreads; t++ )
		{
			Workers.push_back( std::thread( &GAME_THREAD_POOL::worker_thread, this, t ) );
		}
	}

	~GAME_THREAD_POOL()
	{
		for ( auto& w : Workers )
		{
			w.join();
		}
	}


	void worker_thread( unsigned int t )
	{
		while ( true )
		{
			MutexLock.lock();
			bool is_ready = ReadyList[t];
			MutexLock.unlock();

			if ( is_ready )
			{
				Tasks[t]();

				MutexLock.lock();
				ProcessedList[t] = true;
				ReadyList[t] = false;
				MutexLock.unlock();
			}
		}
	}

	void add_job( std::function<void()> f )
	{
		Jobs.push( f );
	}

	void run( void )
	{
		while ( !Jobs.empty() )
		{
			for ( size_t i = 0; i < NumOfThreads; i++ )
			{
				if ( !Jobs.empty() )
				{
					Tasks.push_back( Jobs.front() );
					Jobs.pop();
				}
			}
			const size_t num_of_tasks = Tasks.size();

			MutexLock.lock();
			for ( size_t t = 0; t < num_of_tasks; t++ )
			{
				ReadyList[t] = true;
			}
			MutexLock.unlock();

			bool processed = false;

			while ( !processed )
			{
				bool done = true;

				MutexLock.lock();
				for ( size_t t = 0; t < num_of_tasks; t++ )
				{
					bool v;

					v = ProcessedList[t];

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
			for ( size_t t = 0; t < num_of_tasks; t++ )
			{
				ProcessedList[t] = false;
			}
			MutexLock.unlock();

			Tasks.clear();
		}
	}

private:

	int										NumOfThreads;
	std::mutex								MutexLock;
	std::deque<bool>						ReadyList;
	std::deque<bool>						ProcessedList;
	std::vector<std::thread>				Workers;
	std::vector<std::function<void()>>		Tasks;
	std::queue<std::function<void()>>		Jobs;
};

#endif