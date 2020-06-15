#ifndef PLOT_TOOL_POSE_H
#define PLOT_TOOL_POSE_H

#include <cmath>
#include <vector>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T>
PoseSE3<T>::PoseSE3(const Matrix<T>& rotation_matrix, const Vec3D<T>& translation_vector)
    : rotation_matrix(rotation_matrix), translation_vector(translation_vector)
{
}

template <typename T> PoseSE3<T>::PoseSE3(const Matrix<T>& pose_matrix)
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            rotation_matrix(r, c) = pose_matrix(r, c);
        }
    }
    translation_vector.x = pose_matrix(0, 3);
    translation_vector.y = pose_matrix(1, 3);
    translation_vector.z = pose_matrix(2, 3);
}

template <typename T> PoseSE3<T>::PoseSE3() {}

template <typename T> Matrix<T> PoseSE3<T>::getRotationMatrix() const
{
    return rotation_matrix;
}

template <typename T> Vec3D<T> PoseSE3<T>::getTranslationVector() const
{
    return translation_vector;
}

template <typename T> Matrix<T> PoseSE3<T>::getPoseMatrix() const
{
    return poseMatrixFromMatrixAndVector(rotation_matrix, translation_vector);
}

template <typename T> PoseSE3<T> operator*(const PoseSE3<T>& p0, const PoseSE3<T>& p1)
{
    return PoseSE3<T>(p0.getPoseMatrix() * p1.getPoseMatrix());
}

template <typename T> Matrix<T> PoseSE3<T>::getInversePoseMatrix() const
{
    Matrix<T> inverse_rotation_matrix = transpose(rotation_matrix);
    Vec3D<T> inverse_translation_vector = inverse_rotation_matrix * translation_vector;
    inverse_translation_vector.x = -inverse_translation_vector.x;
    inverse_translation_vector.y = -inverse_translation_vector.y;
    inverse_translation_vector.z = -inverse_translation_vector.z;

    return poseMatrixFromMatrixAndVector(inverse_rotation_matrix, inverse_translation_vector);
}

template <typename T> void PoseSE3<T>::invert() {}

// Non class functions
template <typename T>
Matrix<T> poseMatrixFromMatrixAndVector(const Matrix<T>& rotation_matrix,
                                        const Vec3D<T>& translation_vector)
{
    Matrix<T> pose_matrix(4, 4);
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            pose_matrix(r, c) = rotation_matrix(r, c);
        }
    }

    pose_matrix(0, 3) = translation_vector.x;
    pose_matrix(1, 3) = translation_vector.y;
    pose_matrix(2, 3) = translation_vector.z;

    pose_matrix(3, 0) = 0.0;
    pose_matrix(3, 1) = 0.0;
    pose_matrix(3, 2) = 0.0;
    pose_matrix(3, 3) = 1.0;
    return pose_matrix;
}

}  // namespace plot_tool

#endif
