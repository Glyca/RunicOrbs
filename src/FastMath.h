#ifndef FASTMATH_H
#define FASTMATH_H

#define C_PI 3.14159265358979323846

/*! Templates for fast math on floats
	\sa FastMath
*/
namespace FastMathTemplatesFloat {
const static float C_PI_OVER_2 = C_PI/2.0f;

template <int I> inline float Factorial() { return I * Factorial<I - 1>(); }
template <> inline float Factorial<0>() { return 1.0f; }

template <int N> inline float Power(float x) { return x * Power<N - 1>(x); }
template <> inline float Power<0>(float x) { return 1.0f; }

template <int I> inline float Exp_(float x) { return Exp_<I - 1>(x) + Power<I>(x) / Factorial<I>(); }
template <> inline float Exp_<0>(float x) { return 0.0f; }

template <int N> inline float Exponential(float x) { return x < 0.0f ? 1.0f / Exp_<N>(-x) : Exp_<N>(x); }

template <int N> inline float Cosinus(float x) { return Cosinus<N - 1>(x) + (N % 2 ? -1 : 1) * Power<2 * N>(x) / Factorial<2 * N>(); }
template <> inline float Cosinus<0>(float x) { return 1.0f; }

template <int N> inline float Sinus(float x) { return Cosinus<N>(C_PI_OVER_2 - x); }

template <int I> inline float Atanh(float x) { return Atanh<I - 1>(x) + Power<2 * I + 1>(x) / (2 * I + 1); }
template <> inline float Atanh<1>(float x) { return x; }
template <> inline float Atanh<0>(float x) { return 0.0f; }
}

/*! Templates for fast math on doubles
	\sa FastMath
*/
namespace FastMathTemplatesDouble {
const static double C_PI_OVER_2 = C_PI/2.0;

template <int I> inline double Factorial() { return I * Factorial<I - 1>(); }
template <> inline double Factorial<0>() { return 1.0; }

template <int N> inline double Power(double x) { return x * Power<N - 1>(x); }
template <> inline double Power<0>(double x) { return 1.0; }

template <int I> inline double Exp_(double x) { return Exp_<I - 1>(x) + Power<I>(x) / Factorial<I>(); }
template <> inline double Exp_<0>(double x) { return 0.0; }

template <int N> inline double Exponential(double x) { return x < 0.0 ? 1.0 / Exp_<N>(-x) : Exp_<N>(x); }

template <int N> inline double Cosinus(double x) { return Cosinus<N - 1>(x) + (N % 2 ? -1 : 1) * Power<2 * N>(x) / Factorial<2 * N>(); }
template <> inline double Cosinus<0>(double x) { return 1.0; }

template <int N> inline double Sinus(double x) { return Cosinus<N>(C_PI_OVER_2 - x); }

template <int I> inline double Atanh(double x) { return Atanh<I - 1>(x) + Power<2 * I + 1>(x) / (2 * I + 1); }
template <> inline double Atanh<1>(double x) { return x; }
template <> inline double Atanh<0>(double x) { return 0.0; }
}

/*! Provide fast inlined math functions */
namespace FastMath
{

/*! Float cosinus of order 10 of Taylor expansion */
inline float cos10f(float x) {
	return FastMathTemplatesFloat::Cosinus<10>(x);
}
/*! Double cosinus of order 10 of Taylor expansion */
inline double cos10d(double x) {
	return FastMathTemplatesDouble::Cosinus<10>(x);
}
/*! Float sinus of order 10 of Taylor expansion */
inline float sin10f(float x) {
	return FastMathTemplatesFloat::Sinus<10>(x);
}

}

#endif // FASTMATH_H
