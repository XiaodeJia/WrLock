
#ifndef __WRITE_FIRST_RW_LOCK_H
#define __WRITE_FIRST_RW_LOCK_H
class WfirstRWLock
{
public:
	WfirstRWLock();
	~WfirstRWLock();
	void LockRead();
	void LockWrite();
	void ReleaseRead();
	void ReleaseWrite();
private:
	volatile size_t m_readNum{ 0 };
	volatile size_t m_writeNum{ 0 };
	volatile bool m_inWriteFlag{ false };
	std::mutex m_counterMutex;
	std::condition_variable m_condW;
	std::condition_variable m_condR;
};
#endif

