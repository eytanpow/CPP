
#include <thread>			   // std::thread
#include <chrono>			   // std::chrono::milliseconds, sleep_for
#include "FixedSizeBuffer.hpp" // ←-- put the queue header’s real name here

using namespace hrdxxx;

template <typename T, size_t Size>
T FixedSizeBuffer<T, Size>::QueueRead()
{
	m_fill.acquire();
	T a;
	{
		std::unique_lock<std::mutex> lock(rLock);
		a = arr[r];
		std::cout << "read " << arr[r] << std::endl;
		r = (r + 1) % Size;
	}
	m_free.release();
	return a;
}

template <typename T, size_t Size>
bool FixedSizeBuffer<T, Size>::QueueWrite(T toWrite)
{
	m_free.acquire();

	std::unique_lock<std::mutex> lock(wLock);

	arr[w] = toWrite;
	w = (w + 1) % Size;
	std::cout << "write " << toWrite << std::endl;

	m_fill.release();
	return true;
}

/******************************  Test Implementation  ******************************/
const int bufferSize = 3;
// ----------------  helper tasks  -------------------------------------
void WriterTask(hrdxxx::FixedSizeBuffer<char, bufferSize> &q, int id)
{
	/* Each writer starts with a different letter so the output is easy to tell
	   apart.  The letter is advanced every loop to give the readers variety. */
	char current = static_cast<char>('A' + id);

	while (true)
	{
		if (q.QueueWrite(current)) // push a character
		{
			//	std::cout << "wrote " << current << std::endl;
		}

		current = (current == 'Z') ? 'A' : static_cast<char>(current + 3);

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void ReaderTask(hrdxxx::FixedSizeBuffer<char, bufferSize> &q)
{
	while (true)
	{
		q.QueueRead();
		// std::cout << "read " << q.QueueRead() << std::endl; // pops & prints inside QueueRead
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

// ----------------  main  ---------------------------------------------
int main()
{
	using namespace hrdxxx;

	/* Shared, bounded queue.  Capacity is fixed at 6 because the class
	   template parameter is 6.                                             */
	FixedSizeBuffer<char, bufferSize> queue;

	// launch three writers & three readers
	std::thread w0(WriterTask, std::ref(queue), 0);
	std::thread w1(WriterTask, std::ref(queue), 1);
	std::thread w2(WriterTask, std::ref(queue), 2);

	std::thread r0(ReaderTask, std::ref(queue));
	std::thread r1(ReaderTask, std::ref(queue));
	std::thread r2(ReaderTask, std::ref(queue));

	/* These joins never return because the tasks run forever.
	   Press Ctrl-C to terminate the program.                               */
	w0.join();
	w1.join();
	w2.join();
	r0.join();
	r1.join();
	r2.join();

	return 0; // never reached
}
