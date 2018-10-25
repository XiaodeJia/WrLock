#ifndef _RAII_TEMPLATE_
#define _RAII_TEMPLATE_

template <typename _RWLockable>
class UniqueWriteGuard
{
public:
	explicit UniqueWriteGuard(_RWLockable &rwLockable)
		: m_rwLockable(rwLockable)
	{
		m_rwLockable.lock_write();
	}
	~unique_writeguard()
	{
		m_rwLockable.release_write();
	}
private:
	UniqueWriteGuard() = delete;
	UniqueWriteGuard(const UniqueWriteGuard&) = delete;
	UniqueWriteGuard& operator=(const UniqueWriteGuard&) = delete;
private:
	_RWLockable & m_rwLockable;
};

template <typename _RWLockable>
class UniqueReadGuard
{
public:
	explicit UniqueReadGuard(_RWLockable &rwLockable)
		: m_rwLockable(rwLockable)
	{
		m_rwLockable.lock_read();
	}
	~unique_readguard()
	{
		m_rwLockable.release_read();
	}
private:
	UniqueReadGuard() = delete;
	UniqueReadGuard(const UniqueReadGuard&) = delete;
	UniqueReadGuard& operator=(const UniqueReadGuard&) = delete;
private:
	_RWLockable & m_rwLockable;
};
#endif // !_RAII_TEMPLATE_
