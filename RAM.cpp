#include "RAM.h"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <psapi.h>
#undef Rectangle
#undef CloseWindow
#undef ShowCursor

size_t RAM::obtenerUsoDeMemoria() {
    PROCESS_MEMORY_COUNTERS memCounters;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounters, sizeof(memCounters))) {
        return memCounters.WorkingSetSize;
    }
    return 0;
}
