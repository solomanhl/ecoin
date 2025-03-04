﻿#include <iostream>
#include <chrono>
#include <vector>
#include <mutex>

#include "speed.hpp"


Speed::Speed(int interval)
	: m_interval(interval)
	, m_buffer_hashes(interval * 10000)
	, m_buffer_solutions(interval * 10000)
	, m_buffer_shares(interval * 10000)
	, m_buffer_shares_ok(interval * 10000)
{
}

Speed::~Speed()
{
}

void Speed::Add(boost::circular_buffer<time_point>& buffer, std::mutex& mutex)
{
	mutex.lock();
	buffer.push_back(std::chrono::high_resolution_clock::now());
	mutex.unlock();
}

double Speed::Get(boost::circular_buffer<time_point>& buffer, std::mutex& mutex)
{
	time_point now = std::chrono::high_resolution_clock::now();
	time_point past = now - std::chrono::seconds(m_interval);
	double interval = (double)m_interval;

	size_t total = 0;

	if (buffer.size() > 1)
	{
		for (int i =0; i < buffer.size(); i++)
		{
			if (buffer[i] >= past)
			{
				total = buffer.size() - i;

				if (i == 0)
				{
					if (total > 25)
					{
						interval = std::chrono::duration_cast<std::chrono::milliseconds>(now - buffer[i]).count() / 1000.0;
					}

					return (total - 1.0) / interval;

				}else
				{
					return (double)total / interval;
				}
			}
		}
	}
	return 0.0;
}

void Speed::AddHash()
{
	Add(m_buffer_hashes, m_mutex_hashes);
}

double Speed::GetHashSpeed()
{
	return Get(m_buffer_hashes, m_mutex_hashes);
}

void Speed::AddSolution()
{
	Add(m_buffer_solutions, m_mutex_solutions);
}

double Speed::GetSolutionSpeed()
{
	return Get(m_buffer_solutions, m_mutex_solutions);
}

void Speed::AddShare()
{
	Add(m_buffer_shares, m_mutex_shares);
}

double Speed::GetShareSpeed()
{
	return Get(m_buffer_shares, m_mutex_shares);
}

void Speed::AddShareOK()
{
	Add(m_buffer_shares_ok, m_mutex_shares_ok);
}


double Speed::GetShareOKSpeed()
{
	return Get(m_buffer_shares_ok, m_mutex_shares_ok);
}

void Speed::Reset()
{
	m_mutex_hashes.lock();
	m_buffer_hashes.clear();
	m_mutex_hashes.unlock();

	m_mutex_solutions.lock();
	m_buffer_solutions.clear();
	m_mutex_solutions.unlock();

	m_mutex_shares.lock();
	m_buffer_shares.clear();
	m_mutex_shares.unlock();

	m_mutex_shares_ok.lock();
	m_buffer_shares_ok.clear();
	m_mutex_shares_ok.unlock();
}


Speed speed(5);
