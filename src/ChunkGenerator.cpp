#include "ChunkGenerator.h"
#include "Vector.h" // ifloor

/*
 These functions are not in the class for performance reason. (a pointer to the object not to pass)
 Written with a superb tutorial [http://freespace.virgin.net/hugo.elias/models/m_perlin.htm]
 by Glyca
*/

inline static double Noise(const int x, const int y)
{
	int n = ifloor(x) + ifloor(y) * 57;
	n = (n << 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double) nn / 1073741824.0);
}

inline static double SmoothNoise_1(const double x, const double y)
{
	double corners = ( Noise(x-1, y-1) + Noise(x+1, y-1) + Noise(x-1, y+1) + Noise(x+1, y+1) ) / 16.0;
	double sides   = ( Noise(x-1, y  ) + Noise(x+1, y  ) + Noise(x  , y-1) + Noise(x  , y+1) ) /  8.0;
	double center  =  Noise(x, y) / 4.0;
	return corners + sides + center;
}

inline static double Cosine_Interpolate(const double a, const double b, const double x)
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5;
	return a * (1 - f) + b * f;
}

static double InterpolatedNoise_1(const double x, const double y)
{
	int int_X = ifloor(x);
	double fractional_X = x - int_X;

	int int_Y = ifloor(y);
	double fractional_Y = y - int_Y;

	double v1 = SmoothNoise_1(int_X,     int_Y    );
	double v2 = SmoothNoise_1(int_X + 1, int_Y    );
	double v3 = SmoothNoise_1(int_X,     int_Y + 1);
	double v4 = SmoothNoise_1(int_X + 1, int_Y + 1);

	double i1 = Cosine_Interpolate(v1, v2, fractional_X);
	double i2 = Cosine_Interpolate(v3, v4, fractional_X);

	return Cosine_Interpolate(i1 , i2 , fractional_Y);
}


static double PerlinNoise_2D(const double x, const double y)
{
	const double persistence = 0.1;
	const int octaves = 2; // Number of octaves
	const int n = octaves - 1;
	double total = 0.0;

	for(int i = 0; i < n; i++)
	{
		int frequency = 2 ^ i;
		int amplitude = pow(persistence, i); // pow is ^ for doubles

		total += InterpolatedNoise_1(x * frequency, y * frequency) * amplitude;
	}
	return total;
}

ChunkGenerator::ChunkGenerator(const int seed) : i_seed(seed)
{

}

ChunkGenerator::ChunkGenerator(const ChunkGenerator&) : QThread()
{

}

void ChunkGenerator::run()
{
	generateChunk();
}

void ChunkGenerator::generateChunk() const
{
	for(int i = 0; i < CHUNK_X_SIZE; i++)
	{
		for(int k = 0; k < CHUNK_Z_SIZE; k++)
		{
			int wi, wj, wk; // Coordinates in the world
			m_chunkToGenerate->mapToWorld(i, 0, k, wi, wj, wk);
			double rockAltitude = (PerlinNoise_2D(wi*0.018, wk*0.018) + 1)*CHUNK_HEIGHT/4;
			double dirtAltitude = (PerlinNoise_2D(-wi*0.018, -wk*0.018)/3);
			for(int j = 0; j < rockAltitude; j++)
			{
				m_chunkToGenerate->block(i, j, k)->setId(1);
			}
			for(int j = rockAltitude; j < rockAltitude + dirtAltitude; j++)
			{
				m_chunkToGenerate->block(i, j, k)->setId(2);
			}
		}
	}
}
