// This class is to simplify creating and executing all thread concurrenty
// Particulary useful for, FOR loops. The simplest form of creating a job
// for the pool is to wrap the desired function around a lambda function:
// 
// auto job1 = []() { your function(parameters needed) };
// auto job2 = []() { your function(parameters needed) };
// game_thread_pool.add_job( job1 );
// game_thread_pool.add_job( job2 );
// game_thread_pool.run();
//
//

#ifndef __GAME_THREAD_POOL__
#define __GAME_THREAD_POOL__

// -- LOCAL

// .. REFERENCES

#include <functional>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>
#include <queue>

// -- GLOBAL

// .. CONSTANTS

// .. TYPES

class GAME_THREAD_POOL
{
	// -- PUBLIC
public:

	// .. CONSTRUCTORS

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

	// .. DESTRUCTORS

	~GAME_THREAD_POOL()
	{
		for ( auto& w : Workers )
		{
			w.join();
		}
	}

	// ~~

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

	// ~~

	void add_job( std::function<void()> f )
	{
		//nested threads not supported
		assert( !ThreadRunning );
		
		Jobs.push( f );
	}

	// ~~

	void run( void )
	{
		ThreadRunning = true;

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

			ThreadRunning = false;
		}
	}

	// -- PRIVATE

private:

	// .. ATTRIBUTES

	int										NumOfThreads;
	std::mutex								MutexLock;
	std::deque<bool>						ReadyList;
	std::deque<bool>						ProcessedList;
	std::vector<std::thread>				Workers;
	std::vector<std::function<void()>>		Tasks;
	std::queue<std::function<void()>>		Jobs;
	std::deque<std::condition_variable>	    ConditionVariables;
	bool									ThreadRunning{ false };
};
#endif