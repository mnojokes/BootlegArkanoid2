#ifndef ANDROIDGLINVESTIGATIONS_UTILITY_H
#define ANDROIDGLINVESTIGATIONS_UTILITY_H

#include <cassert>
#include "Vector.h"

class Utility {
public:
    static bool checkAndLogGlError(bool alwaysLog = false);

    static inline void assertGlError() { assert(checkAndLogGlError()); }

    /**
     * Generates an orthographic projection matrix given the half height, aspect ratio, near, and far
     * planes
     *
     * @param outMatrix the matrix to write into
     * @param halfHeight half of the height of the screen
     * @param aspect the width of the screen divided by the height
     * @param near the distance of the near plane
     * @param far the distance of the far plane
     * @return the generated matrix, this will be the same as @a outMatrix so you can chain calls
     *     together if needed
     */
    static float *buildOrthographicMatrix(float *outMatrix, float width, float height);

    static float *buildIdentityMatrix(float *outMatrix);
    static float *buildTransformMatrix(float *outMatrix, const Vector2& position, const Vector2& scale);

    static bool IsPointInQuad(const Vector2& point, const Vector2& quadCenter, const Vector2& halfExtents);
};

#endif //ANDROIDGLINVESTIGATIONS_UTILITY_H