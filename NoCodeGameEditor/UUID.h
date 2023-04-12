#pragma once
#include <xhash>
class UUID
{
private:
	uint64_t m_UUID;

public:
	UUID();
	UUID(uint64_t t_uuid);
	operator uint64_t() const { return m_UUID; }
};

