//-------------------------------------------------------------------------
//
// PNoise.h: interface for the PNoise class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(PNOISE_H_INCLUDED)
#define PNOISE_H_INCLUDED

class PNoise
{
public:
   PNoise();           ///<seeds itself with the time
   PNoise(int seed);   ///<you choose the seed
   virtual ~PNoise();

   void seed();      ///<seed rand with the time
   void seed(int s); ///<specify seed

   /**
   In what follows "alpha" is the weight when the sum is formed.
   Typically it is 2, As this approaches 1 the function is noisier.
   "beta" is the harmonic scaling/spacing, typically 2. "n" is the
   number of harmonics to sum.

   Notice: n, alpha, and beta have default values set.
   These match Ken's original calls
   */
   /// range is -1 -> 1
   double PerlinNoise1D(double x,int n =1, double amplitude =2,double beta =2);
   double PerlinNoise2D(double x,double y,int n =1,double amplitude =2,double beta =2);
   double PerlinNoise3D(double x, double y, double z, int octaves = 1, double amplitude = 2, double beta = 2);

   /// range is 0 -> 1
   double PerlinNoise3DABS(double x, double y, double z, int octaves = 1, double amplitude =2,double beta =2);

   // This next set is to simplify calls with aliases
   void   setParams(int n, double alpha =2, double beta =2);

   double PN1D(double x);
   double PN2D(double x, double y);
   double PN3D(double x, double y, double z);
   double PN3DA(double x, double y, double z);

   double PN3D_dx(double x, double y, double z, double dx = .001);
   double PN3D_dy(double x, double y, double z, double dy = .001);
   double PN3D_dz(double x, double y, double z, double dz = .001);


   // TO DO: fast 2D & 3D field generation, Vector noise

private:
   void init(void);
   double noise1(double);
   double noise2(double *);
   double noise3(double *);
   void normalize3(double *);
   void normalize2(double *);

   int    *p;
   double **g3;
   double **g2;
   double *g1;
   int    start;

   inline int random();

   double _alpha;
   double _beta;
   int    _n;

};

class CurlyPNoise {
 public:
 CurlyPNoise()
   {}


 void   setParams(int n, double alpha =2, double beta =2)
 {
   _px.setParams(n,alpha,beta);
   _py.setParams(n,alpha,beta);
   _pz.setParams(n,alpha,beta);
 }

 protected:

  PNoise _px;
  PNoise _py;
  PNoise _pz;

};


///////////////////////////////////////////////////////////////////////
/// generate a texture with perlin noise
///   allocates space for you, new
///    range is always [0-1]
void gen2DPerlinTexture(float *&data, unsigned int sx, unsigned int sy,
						unsigned int   components,      /// greyscale, RGBA, how many??
						int   octaves = 4,
						float frequencyScale = 2,
						float amplitudeScale = 2,
						bool  absNoise = false);        /// absolute value noise

void gen3DPerlinTexture(float *&data, unsigned int sx, unsigned int sy, unsigned int sz,
						unsigned int   components,      /// greyscale, RGBA, how many??
						int   octaves = 4,
						float frequencyScale = 2,
						float amplitudeScale = 2,
						bool  absNoise = false);        /// absolute value noise




#endif // !defined(PNOISE_H_INCLUDED)
