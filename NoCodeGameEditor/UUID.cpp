#include "UUID.h"
#include <random>

/// <summary>
/// Generate random UUIDs
/// </summary>
static std::random_device  s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

/// <summary>
/// Default Constructor
/// </summary>
UUID::UUID()
	: m_UUID(s_UniformDistribution(s_Engine))
{
}

/// <summary>
/// overloaded Constructor
/// </summary>
UUID::UUID(uint64_t t_uuid)
	: m_UUID(t_uuid)
{
}
