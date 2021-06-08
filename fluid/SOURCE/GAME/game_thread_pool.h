#ifndef __GAME_THREAD_POOL__
#define __GAME_THREAD_POOL__

#include <functional>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>
#include <queue>
#include <memory>
#include <iostream>

class GAME_THREAD_POOL
{

public:

	GAME_THREAD_POOL()
	{
		NumOfThreads = std::thread::hardware_concurrency();

		ReadyList.resize( NumOfThreads, false );
		ProcessedList.resize( NumOfThreads, false );
		ConditionVariables.resize( NumOfThreads);

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
			std::unique_lock<std::mutex> lk( MutexLock );
			ConditionVariables[t].wait( lk, [&] {return ReadyList[t]; } );
			lk.unlock();

			Tasks[t]();

			lk.lock();
			ProcessedList[t] = true;
			ReadyList[t] = false;
			lk.unlock();
			ConditionVariables[t].notify_one();
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

			{
				std::unique_lock<std::mutex> lk( MutexLock );

				for ( size_t i = 0; i < num_of_tasks; i++ )
				{

					ReadyList[i] = true;
				}
			}

			for ( size_t i = 0; i < num_of_tasks; i++ )
			{
				ConditionVariables[i].notify_one();

			}

			{
				std::unique_lock<std::mutex> lk( MutexLock );
				for ( size_t i = 0; i < num_of_tasks; i++ )
				{
					ConditionVariables[i].wait( lk, [&] {return ProcessedList[i]; } );
				}
			}

			{
				std::unique_lock<std::mutex> lk( MutexLock );
				for ( size_t i = 0; i < num_of_tasks; i++ )
				{
					ProcessedList[i] = false;
				}
			}

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
	std::deque<std::condition_variable>	    ConditionVariables;
};
#endif