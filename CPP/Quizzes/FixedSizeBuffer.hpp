/*
	fixed size buffer allow reader and writer work in parallel
	only one reader and writer each time
*/
#pragma once

#include <mutex> //std::mutex
#include <iostream>
#include <atomic>
#include <condition_variable>
#include <semaphore>

namespace hrdxxx
{
	template <typename T, size_t Size>
	class FixedSizeBuffer
	{
	public:
		FixedSizeBuffer() : r(0), w(0) {}

		FixedSizeBuffer(const FixedSizeBuffer &other) = delete;
		FixedSizeBuffer &operator=(const FixedSizeBuffer &other) = delete;

		T QueueRead();

		bool QueueWrite(T toWrite);

	private:
		std::mutex rLock;
		std::mutex wLock;

		std::counting_semaphore<Size> m_free{Size};
		std::counting_semaphore<Size> m_fill{0};
		int r;
		int w;
		T arr[Size];
	};

}