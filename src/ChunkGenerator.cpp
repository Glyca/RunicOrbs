#include "ChunkGenerator.h"

double Noise(int x, int y)
{
	int n = x + y * 57;
	n = pow((n<<13), n);
	return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) /*& 0x7fffffff*/) / 1073741824.0);
}

double SmoothNoise_1(double x, double y)
{
	double corners = ( Noise(x-1, y-1)+Noise(x+1, y-1)+Noise(x-1, y+1)+Noise(x+1, y+1) ) / 16;
	double sides   = ( Noise(x-1, y)  +Noise(x+1, y)  +Noise(x, y-1)  +Noise(x, y+1) ) /  8;
	double center  =  Noise(x, y) / 4;
	return corners + sides + center;
}

double Cosine_Interpolate(double a, double b, double x)
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5;
	return  a*(1-f) + b*f;
}

double InterpolatedNoise_1(double x, double y)
{
	int int_X = int(x);
	double fractional_X = x - int_X;

	int int_Y = int(y);
	double fractional_Y = y - int_Y;

	double v1 = SmoothNoise_1(int_X,     int_Y);
	double v2 = SmoothNoise_1(int_X + 1, int_Y);
	double v3 = SmoothNoise_1(int_X,     int_Y + 1);
	double v4 = SmoothNoise_1(int_X + 1, int_Y + 1);

	double i1 = Cosine_Interpolate(v1 , v2 , fractional_X);
	double i2 = Cosine_Interpolate(v3 , v4 , fractional_X);

	return Cosine_Interpolate(i1 , i2 , fractional_Y);
}


double PerlinNoise_2D(double x, double y)
{
	double total = 0;
	double p = 1.9; // persistence
	int Number_Of_Octaves = 3;
	int n = Number_Of_Octaves - 1;

	for(int i = 0; i < n; i++)
	{
		int frequency = pow(2, i);
		int amplitude = pow(p, i);

		total += InterpolatedNoise_1(x * frequency, y * frequency) * amplitude;

	}
	return total;
}

ChunkGenerator::ChunkGenerator(Chunk* chunkToGenerate, int seed) : m_chunkToGenerate(chunkToGenerate), i_seed(seed)
{

}

void ChunkGenerator::generateChunk()
{
	for(int i = 0; i < CHUNK_X_SIZE; i++)
	{
		for(int k = 0; k < CHUNK_Z_SIZE; k++)
		{
			int wi, wj, wk; // Coordinates in the world
			m_chunkToGenerate->mapToWorld(i, 0, k, wi, wj, wk);
			double altitude = (PerlinNoise_2D(wi*0.05, wk*0.05) + 1)*CHUNK_HEIGHT/4;
			for(int j = 0; j < altitude; j++)
			{
				m_chunkToGenerate->block(i, j, k)->setId(1);
			}
		}
	}
}
