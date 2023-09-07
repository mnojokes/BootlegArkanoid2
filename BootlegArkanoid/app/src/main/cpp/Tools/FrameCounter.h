#pragma once

#include <chrono>

class FrameCounter
{
public:
    void Start(void);
    void Stop(void);

    float GetDelta(void) const; // Get last delta in seconds
    void SetFPSLock(uint32_t fps); // Lock FPS to a specific amount

private:
    std::chrono::nanoseconds m_lockedFrameTime = {}; // frame time in seconds, set by SetFPSLock
    std::chrono::steady_clock::time_point m_frameStartTime = {};
    std::chrono::nanoseconds m_lastDelta = {}; // last frame's delta time
};
