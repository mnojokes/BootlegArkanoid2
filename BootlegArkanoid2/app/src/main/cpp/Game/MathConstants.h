#pragma once

namespace Constants
{
    constexpr float Pi = 3.1415927f;
    constexpr float Nano = 1000000000.0f;
}

namespace Reciprocals
{
    constexpr float Pi = 1.0f / Constants::Pi;
    constexpr float r180 = 1.0f / 180.0f;
    constexpr float Nano = 1.0f / Constants::Nano;
}
