#include "Memory.h"

#include <corecrt_malloc.h>

static MemoryMetrics MemoryMetricsInfo = {};

void* operator new(size_t size)
{
    MemoryMetricsInfo.totalAllocatedBytes += size;

    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    MemoryMetricsInfo.totalFreedBytes += size;

    free(memory);
}

size_t Memory::GetMemoryUsageBytes()
{
    return MemoryMetricsInfo.GetMemoryUsageBytes();
}

double Memory::GetMemoryUsageKilobytes()
{
    return MemoryMetricsInfo.GetMemoryUsageBytes() * 0.001;
}

double Memory::GetMemoryUsageMegabytes()
{
    return MemoryMetricsInfo.GetMemoryUsageBytes() * 0.000001;
}

double Memory::GetMemoryUsageGigabytes()
{
    return MemoryMetricsInfo.GetMemoryUsageBytes() * 0.000000001;
}
