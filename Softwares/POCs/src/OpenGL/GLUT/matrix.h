#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>
#include <array>

// Petite classe pour nous faciliter la creation des matrices
class Matrix4
{
	public:
		// Constructeur qui initialise à l'identite
		Matrix4 ()
		{
			data[0] = data[5] = data[10] = data[15] = 1.0f;
			data[1] = data[2] = data[3] = data[4] = data[6] = data[7] = data[8] = data[9] = data[11] = data[12] = data[13] = data[14] = 0.0f;
		}

		// Construit à partir d'un tableau
		Matrix4 (const std::array<float, 16> data_)
			: data (data_)
		{
		}

		// Construit une matrice de projection
		void SetProjectionMatrix (const float fov_, const float aspect_, const float nearPlane_, const float farPlane_)
		{
			float maxY = nearPlane_ * tan (fov_ * 3.14159256f / 360.0f);
   		float minY = -maxY;
   		float minX = minY * aspect_;
   		float maxX = maxY * aspect_;

			std::fill (data.begin(), data.end(), 0.0f);

			data[0] = 2.0f * nearPlane_ / (maxX - minX);
			data[5] = 2.0f * nearPlane_ / (maxY - minY);
			data[8] = (maxX + minX) / (maxX - minX);
			data[9] = (maxY + minY) / (maxY - minY);
			data[10] = -(farPlane_ + nearPlane_) / (farPlane_ - nearPlane_);
			data[11] = -1.0f;
			data[14] = -(2.0f * farPlane_ * nearPlane_) / (farPlane_ - nearPlane_);
		}

		// Construit une matrice de transformation toute simple (uniquement translation)
		void SetTransformationMatrix (const float x_, const float y_, const float z_)
		{
			data[12] += x_;
			data[13] += y_;
			data[14] += z_;
		}

		// Retourne la matrice sous la forme d'un pointeur (près pour être envoye à OpenGL)
		const float * GetMatrixForOpenGL () const
		{
			return &data[0];
		}


	public:
		std::array<float, 16> data;
};


// Multiplie deux matrices
Matrix4 operator* (const Matrix4 & mat1_, const Matrix4 & mat2_)
{
	std::array<float, 16> data = {		
			  mat1_.data[0] * mat2_.data[0] + mat1_.data[4] * mat2_.data[1] + mat1_.data[8] * mat2_.data[2] + mat1_.data[12] * mat2_.data[3],
			  mat1_.data[1] * mat2_.data[0] + mat1_.data[5] * mat2_.data[1] + mat1_.data[9] * mat2_.data[2] + mat1_.data[13] * mat2_.data[3],
			  mat1_.data[2] * mat2_.data[0] + mat1_.data[6] * mat2_.data[1] + mat1_.data[10] * mat2_.data[2] + mat1_.data[14] * mat2_.data[3],
			  mat1_.data[3] * mat2_.data[0] + mat1_.data[7] * mat2_.data[1] + mat1_.data[11] * mat2_.data[2] + mat1_.data[15] * mat2_.data[3],

			  mat1_.data[0] * mat2_.data[4] + mat1_.data[4] * mat2_.data[5] + mat1_.data[8] * mat2_.data[6] + mat1_.data[12] * mat2_.data[7],
			  mat1_.data[1] * mat2_.data[4] + mat1_.data[5] * mat2_.data[5] + mat1_.data[9] * mat2_.data[6] + mat1_.data[13] * mat2_.data[7],
			  mat1_.data[2] * mat2_.data[4] + mat1_.data[6] * mat2_.data[5] + mat1_.data[10] * mat2_.data[6] + mat1_.data[14] * mat2_.data[7],
			  mat1_.data[3] * mat2_.data[4] + mat1_.data[7] * mat2_.data[5] + mat1_.data[11] * mat2_.data[6] + mat1_.data[15] * mat2_.data[7],

			  mat1_.data[0] * mat2_.data[8] + mat1_.data[4] * mat2_.data[9] + mat1_.data[8] * mat2_.data[10] + mat1_.data[12] * mat2_.data[11],
			  mat1_.data[1] * mat2_.data[8] + mat1_.data[5] * mat2_.data[9] + mat1_.data[9] * mat2_.data[10] + mat1_.data[13] * mat2_.data[11],
			  mat1_.data[2] * mat2_.data[8] + mat1_.data[6] * mat2_.data[9] + mat1_.data[10] * mat2_.data[10] + mat1_.data[14] * mat2_.data[11],
			  mat1_.data[3] * mat2_.data[8] + mat1_.data[7] * mat2_.data[9] + mat1_.data[11] * mat2_.data[10] + mat1_.data[15] * mat2_.data[11],

			  mat1_.data[0] * mat2_.data[12] + mat1_.data[4] * mat2_.data[13] + mat1_.data[8] * mat2_.data[14] + mat1_.data[12] * mat2_.data[15],
			  mat1_.data[1] * mat2_.data[12] + mat1_.data[5] * mat2_.data[13] + mat1_.data[9] * mat2_.data[14] + mat1_.data[13] * mat2_.data[15],
			  mat1_.data[2] * mat2_.data[12] + mat1_.data[6] * mat2_.data[13] + mat1_.data[10] * mat2_.data[14] + mat1_.data[14] * mat2_.data[15],
			  mat1_.data[3] * mat2_.data[12] + mat1_.data[7] * mat2_.data[13] + mat1_.data[11] * mat2_.data[14] + mat1_.data[15] * mat2_.data[15]};

	return Matrix4 (data);
}

#endif // MATRIX_HPP
