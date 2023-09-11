#include "FrameCounter.h"
#include "MathConstants.h"

void FrameCounter::Start()
{
    m_frameStartTime = std::chrono::steady_clock::now();
}

void FrameCounter::Stop()
{
    m_lastDelta = std::chrono::steady_clock::now() - m_frameStartTime;
    while (m_lastDelta < m_lockedFrameTime)
    {
        m_lastDelta = std::chrono::steady_clock::now() - m_frameStartTime;
    }
}

float FrameCounter::GetDelta() const
{
    return static_cast<float>(m_lastDelta.count()) * Reciprocals::Nano;
}

void FrameCounter::SetFPSLock(uint32_t fps)
{
    float timeNanoFL = fps > 0 ? Constants::Nano / static_cast<float>(fps) : 0.0f;
    auto timeNanoUINT = static_cast<uint64_t>(timeNanoFL);
    m_lockedFrameTime = std::chrono::nanoseconds(timeNanoUINT);
}
