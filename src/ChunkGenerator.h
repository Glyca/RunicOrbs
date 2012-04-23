#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include <QThread>
#include "Vector.h" // ifloor

class Chunk;

/*! The ChnkGenerator class can generate the blocks of the given Chunk.
  All members are static since and so you can ue only one seed at once
 */
class ChunkGenerator : public QThread
{
public:
	ChunkGenerator(Chunk* chunkToGenerate, const int seed);
	ChunkGenerator(const ChunkGenerator&);

	/*! Called to generate the chunk in fact */
	void run();

private:
	/*! Dot product */
	inline static double dot3d(const int g[], const double x, const double y, const double z) {return g[0]*x + g[1]*y + g[2]*z;}

	inline double noise2d(const int x, const int y) {
		int n = (ifloor(x) + ifloor(y) * 57) * i_seed;
		n = (n << 13) ^ n;
		int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
		return 1.0 - ((double) nn / 1073741824.0);
	}

	inline double smoothNoise2d(const double x, const double y) {
		double corners = ( noise2d(x-1, y-1) + noise2d(x+1, y-1) + noise2d(x-1, y+1) + noise2d(x+1, y+1) ) / 16.0;
		double sides   = ( noise2d(x-1, y  ) + noise2d(x+1, y  ) + noise2d(x  , y-1) + noise2d(x  , y+1) ) /  8.0;
		double center  =  noise2d(x, y) / 4.0;
		return corners + sides + center;
	}

	double cosineInterpolate2d(const double a, const double b, const double x);

	double interpolatedNoise2d(const double x, const double y);

	/*! 2D Perlin noise */
	double perlinNoise2d(const double x, const double y);
	/*! 3D Perlin noise (simplex noise in reality) */
	static double perlinNoise3d(const double xin, const double yin, const double zin);

	int i_seed;
	Chunk* m_chunkToGenerate;
};

#endif // CHUNKGENERATOR_H
