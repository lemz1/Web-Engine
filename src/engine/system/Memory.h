#pragma once

#include <stdint.h>

struct MemoryMetrics
{
public:
	size_t GetMemoryUsageBytes() const { return totalAllocatedBytes - totalFreedBytes; }
public:
	size_t totalAllocatedBytes = 0;
	size_t totalFreedBytes = 0;
};

class Memory
{
public:
	static size_t GetMemoryUsageBytes();
	static double GetMemoryUsageKilobytes();
	static double GetMemoryUsageMegabytes();
	static double GetMemoryUsageGigabytes();
};
