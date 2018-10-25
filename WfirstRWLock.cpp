#include <mutex>
#include <condition_variable>
#include "WfirstRWLock.h"



WfirstRWLock::WfirstRWLock()
{
}

WfirstRWLock::~WfirstRWLock()
{
}
inline void WfirstRWLock::LockRead()
{
	std::unique_lock<std::mutex> ulk(m_counterMutex);
	m_condR.wait(ulk, [=]()->bool {return m_writeNum == 0; });
	++m_readNum;
}
inline void WfirstRWLock::LockWrite()
{
	std::unique_lock<std::mutex> ulk(m_counterMutex);
	++m_writeNum;
	m_condW.wait(ulk, [=]()->bool {return m_readNum == 0 && !m_inWriteFlag; });
	m_inWriteFlag = true;
}
inline void WfirstRWLock::ReleaseRead()
{
	std::unique_lock<std::mutex> ulk(m_counterMutex);
	if (--m_readNum == 0 && m_writeNum > 0)
	{
		m_condW.notify_one();
	}
}
inline void WfirstRWLock::ReleaseWrite()
{
	std::unique_lock<std::mutex> ulk(m_counterMutex);
	if (--m_writeNum == 0)
	{
		m_condR.notify_all();
	}
	else
	{
		m_condW.notify_one();
	}
	m_inWriteFlag = false;
}
