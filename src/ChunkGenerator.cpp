#include "ChunkGenerator.h"
#include "Chunk.h"
#include "FastMath.h"
#include "Vector.h" // ifloor

// adapted from : http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf

static int grad3[][3] = {{1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
						 {1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
						 {0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1}};

static int p[] = {151,160,137,91,90,15,
				  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
				  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
				  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
				  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
				  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
				  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
				  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
				  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
				  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
				  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
				  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
				  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

static double dot(const int g[], const double x, const double y, const double z)
{
	return g[0]*x + g[1]*y + g[2]*z;
}

static int* perm = NULL;

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
	double f = (1 - FastMath::cos10d(ft)) * 0.5;
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

ChunkGenerator::ChunkGenerator(const int seed) : QThread(), i_seed(seed)
{
	if(perm == NULL) {
		// To remove the need for index wrapping, double the permutation table length
		perm = new int[512];
		for(int i = 0; i < 512; i++) perm[i] = p[i & 255];
	}
}

ChunkGenerator::ChunkGenerator(const ChunkGenerator&) : QThread()
{

}

void ChunkGenerator::run()
{
//#define USE_3D_NOISE // Enable 3d noise (very very experimental)
#ifdef USE_3D_NOISE
	for(int i = 0; i < CHUNK_X_SIZE; i++)
	{
		for(int k = 0; k < CHUNK_Z_SIZE; k++)
		{
			for(int j = 0; j < CHUNK_HEIGHT; j++)
			{
				int wi, wj, wk; // Coordinates in the world
				m_chunkToGenerate->mapToWorld(i, j, k, wi, wj, wk);
				double noised = (noise(wi*0.01, wj*0.01, wk*0.01));
				if(noised > (j)/(CHUNK_HEIGHT/0.9))
				{
					if(noised > 0.5) {
						m_chunkToGenerate->block(i, j, k)->setId(2);
					}
					else {
						m_chunkToGenerate->block(i, j, k)->setId(1);
					}
				}
				else {
					m_chunkToGenerate->block(i, j, k)->setId(0);
				}
			}
		}
	}
#else
	for(int i = 0; i < CHUNK_X_SIZE; i++)
	{
		for(int k = 0; k < CHUNK_Z_SIZE; k++)
		{
			int wi, wj, wk; // Coordinates in the world
			m_chunkToGenerate->mapToWorld(i, 0, k, wi, wj, wk);
			double rockAltitude = (PerlinNoise_2D(wi*0.017, wk*0.017) + 1)*CHUNK_HEIGHT/3;
			double dirtAltitude = (PerlinNoise_2D(-wi*0.017, -wk*0.017)/3);
			for(int j = 0; j < rockAltitude; j++)
			{
				m_chunkToGenerate->block(i, j, k)->setId(1);
			}
			for(int j = rockAltitude; j < rockAltitude + dirtAltitude; j++)
			{
				m_chunkToGenerate->block(i, j, k)->setId(2);
			}
			// Full light on the top void block :
			m_chunkToGenerate->block(i, rockAltitude + dirtAltitude, k)->setLightLevel(15);
		}
	}
#endif
}

// 3D simplex noise
double ChunkGenerator::noise(const double xin, const double yin, const double zin) {
	double n0, n1, n2, n3; // Noise contributions from the four corners
	// Skew the input space to determine which simplex cell we're in
	const double F3 = 1.0/3.0;
	double s = (xin+yin+zin)*F3; // Very nice and simple skew factor for 3D
	int i = ifloor(xin+s);
	int j = ifloor(yin+s);
	int k = ifloor(zin+s);
	const double G3 = 1.0/6.0; // Very nice and simple unskew factor, too
	double t = (i+j+k)*G3;
	double X0 = i-t; // Unskew the cell origin back to (x,y,z) space
	double Y0 = j-t;
	double Z0 = k-t;
	double x0 = xin-X0; // The x,y,z distances from the cell origin
	double y0 = yin-Y0;
	double z0 = zin-Z0;
	// For the 3D case, the simplex shape is a slightly irregular tetrahedron.
	// Determine which simplex we are in.
	int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
	int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords
	if(x0>=y0) {
		if(y0>=z0)
		{ i1=1; j1=0; k1=0; i2=1; j2=1; k2=0; } // X Y Z order
		else if(x0>=z0) { i1=1; j1=0; k1=0; i2=1; j2=0; k2=1; } // X Z Y order
		else { i1=0; j1=0; k1=1; i2=1; j2=0; k2=1; } // Z X Y order
	}
	else { // x0<y0
		if(y0<z0) { i1=0; j1=0; k1=1; i2=0; j2=1; k2=1; } // Z Y X order
		else if(x0<z0) { i1=0; j1=1; k1=0; i2=0; j2=1; k2=1; } // Y Z X order
		else { i1=0; j1=1; k1=0; i2=1; j2=1; k2=0; } // Y X Z order
	}
	// A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
	// a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
	// a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
	// c = 1/6.
	double x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
	double y1 = y0 - j1 + G3;
	double z1 = z0 - k1 + G3;
	double x2 = x0 - i2 + 2.0*G3; // Offsets for third corner in (x,y,z) coords
	double y2 = y0 - j2 + 2.0*G3;
	double z2 = z0 - k2 + 2.0*G3;
	double x3 = x0 - 1.0 + 3.0*G3; // Offsets for last corner in (x,y,z) coords
	double y3 = y0 - 1.0 + 3.0*G3;
	double z3 = z0 - 1.0 + 3.0*G3;
	// Work out the hashed gradient indices of the four simplex corners
	int ii = i & 255;
	int jj = j & 255;
	int kk = k & 255;
	int gi0 = perm[ii+perm[jj+perm[kk]]] % 12;
	int gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1]]] % 12;
	int gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2]]] % 12;
	int gi3 = perm[ii+1+perm[jj+1+perm[kk+1]]] % 12;
	// Calculate the contribution from the four corners
	double t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
	if(t0<0) n0 = 0.0;
	else {
		t0 *= t0;
		n0 = t0 * t0 * dot(grad3[gi0], x0, y0, z0);
	}
	double t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;
	if(t1<0) n1 = 0.0;
	else {
		t1 *= t1;
		n1 = t1 * t1 * dot(grad3[gi1], x1, y1, z1);
	}
	double t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;
	if(t2<0) n2 = 0.0;
	else {
		t2 *= t2;
		n2 = t2 * t2 * dot(grad3[gi2], x2, y2, z2);
	}
	double t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
	if(t3<0) n3 = 0.0;
	else {
		t3 *= t3;
		n3 = t3 * t3 * dot(grad3[gi3], x3, y3, z3);
	}
	// Add contributions from each corner to get the final noise value.
	// The result is scaled to stay just inside [-1,1]
	return 32.0*(n0 + n1 + n2 + n3);
}
