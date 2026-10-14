#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>

// Platform-specific headers for memory usage
#if defined(_WIN32) || defined(_WIN64)
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #include <windows.h>
    #include <psapi.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <sys/resource.h>
    #include <unistd.h>
#endif

namespace Benchmark {

    // Retrieve peak memory consumed by the current process in Kilobytes (KB)
    inline size_t getPeakMemoryKB() {
#if defined(_WIN32) || defined(_WIN64)
        PROCESS_MEMORY_COUNTERS info;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info))) {
            return static_cast<size_t>(info.PeakWorkingSetSize / 1024);
        }
        return 0;
#elif defined(__linux__)
        struct rusage usage;
        if (getrusage(RUSAGE_SELF, &usage) == 0) {
            return static_cast<size_t>(usage.ru_maxrss); // ru_maxrss is in KB on Linux
        }
        return 0;
#elif defined(__APPLE__)
        struct rusage usage;
        if (getrusage(RUSAGE_SELF, &usage) == 0) {
            return static_cast<size_t>(usage.ru_maxrss / 1024); // ru_maxrss is in bytes on macOS
        }
        return 0;
#else
        return 0;
#endif
    }

    // RAII Profiler Class: starts timer on creation, prints report on destruction
    class Profiler {
    private:
        std::string label;
        std::chrono::high_resolution_clock::time_point startTime;
        bool active;

    public:
        explicit Profiler(std::string name = "Benchmark") 
            : label(std::move(name)), active(true) {
            startTime = std::chrono::high_resolution_clock::now();
        }

        ~Profiler() {
            if (active) {
                stopAndPrint();
            }
        }

        void stopAndPrint() {
            auto endTime = std::chrono::high_resolution_clock::now();
            active = false;

            double timeMs = std::chrono::duration<double, std::milli>(endTime - startTime).count();
            double timeUs = std::chrono::duration<double, std::micro>(endTime - startTime).count();
            size_t peakMemKB = getPeakMemoryKB();
            double peakMemMB = static_cast<double>(peakMemKB) / 1024.0;

            std::cout << "\n+------------------ [" << label << "] ------------------+\n";
            std::cout << "| Execution Time : " << std::fixed << std::setprecision(3) << timeMs 
                      << " ms (" << std::fixed << std::setprecision(1) << timeUs << " us)\n";
            std::cout << "| Peak Memory    : " << peakMemKB << " KB (" 
                      << std::fixed << std::setprecision(2) << peakMemMB << " MB)\n";
            std::cout << "+---------------------------------------------------+\n";
        }
    };

} // namespace Benchmark

// Convenient macro for profiling a scope
#ifndef ONLINE_JUDGE
    #define PROFILE_SCOPE(name) Benchmark::Profiler _profiler_instance(name)
    #define PROFILE_FUNCTION()  PROFILE_SCOPE(__FUNCTION__)
#else
    #define PROFILE_SCOPE(name)
    #define PROFILE_FUNCTION()
#endif

