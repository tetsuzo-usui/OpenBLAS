#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <complex.h>
#ifdef complex
#undef complex
#endif
#ifdef I
#undef I
#endif

#if defined(_WIN64)
typedef long long BLASLONG;
typedef unsigned long long BLASULONG;
#else
typedef long BLASLONG;
typedef unsigned long BLASULONG;
#endif

#ifdef LAPACK_ILP64
typedef BLASLONG blasint;
#if defined(_WIN64)
#define blasabs(x) llabs(x)
#else
#define blasabs(x) labs(x)
#endif
#else
typedef int blasint;
#define blasabs(x) abs(x)
#endif

typedef blasint integer;

typedef unsigned int uinteger;
typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
#ifdef _MSC_VER
static inline _Fcomplex Cf(complex *z) {_Fcomplex zz={z->r , z->i}; return zz;}
static inline _Dcomplex Cd(doublecomplex *z) {_Dcomplex zz={z->r , z->i};return zz;}
static inline _Fcomplex * _pCf(complex *z) {return (_Fcomplex*)z;}
static inline _Dcomplex * _pCd(doublecomplex *z) {return (_Dcomplex*)z;}
#else
static inline _Complex float Cf(complex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex double Cd(doublecomplex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex float * _pCf(complex *z) {return (_Complex float*)z;}
static inline _Complex double * _pCd(doublecomplex *z) {return (_Complex double*)z;}
#endif
#define pCf(z) (*_pCf(z))
#define pCd(z) (*_pCd(z))
typedef blasint logical;

typedef char logical1;
typedef char integer1;

#define TRUE_ (1)
#define FALSE_ (0)

/* Extern is for use with -E */
#ifndef Extern
#define Extern extern
#endif

/* I/O stuff */

typedef int flag;
typedef int ftnlen;
typedef int ftnint;

/*external read, write*/
typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	char *cifmt;
	ftnint cirec;
} cilist;

/*internal read, write*/
typedef struct
{	flag icierr;
	char *iciunit;
	flag iciend;
	char *icifmt;
	ftnint icirlen;
	ftnint icirnum;
} icilist;

/*open*/
typedef struct
{	flag oerr;
	ftnint ounit;
	char *ofnm;
	ftnlen ofnmlen;
	char *osta;
	char *oacc;
	char *ofm;
	ftnint orl;
	char *oblnk;
} olist;

/*close*/
typedef struct
{	flag cerr;
	ftnint cunit;
	char *csta;
} cllist;

/*rewind, backspace, endfile*/
typedef struct
{	flag aerr;
	ftnint aunit;
} alist;

/* inquire */
typedef struct
{	flag inerr;
	ftnint inunit;
	char *infile;
	ftnlen infilen;
	ftnint	*inex;	/*parameters in standard's order*/
	ftnint	*inopen;
	ftnint	*innum;
	ftnint	*innamed;
	char	*inname;
	ftnlen	innamlen;
	char	*inacc;
	ftnlen	inacclen;
	char	*inseq;
	ftnlen	inseqlen;
	char 	*indir;
	ftnlen	indirlen;
	char	*infmt;
	ftnlen	infmtlen;
	char	*inform;
	ftnint	informlen;
	char	*inunf;
	ftnlen	inunflen;
	ftnint	*inrecl;
	ftnint	*innrec;
	char	*inblank;
	ftnlen	inblanklen;
} inlist;

#define VOID void

union Multitype {	/* for multiple entry points */
	integer1 g;
	shortint h;
	integer i;
	/* longint j; */
	real r;
	doublereal d;
	complex c;
	doublecomplex z;
	};

typedef union Multitype Multitype;

struct Vardesc {	/* for Namelist */
	char *name;
	char *addr;
	ftnlen *dims;
	int  type;
	};
typedef struct Vardesc Vardesc;

struct Namelist {
	char *name;
	Vardesc **vars;
	int nvars;
	};
typedef struct Namelist Namelist;

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define dabs(x) (fabs(x))
#define f2cmin(a,b) ((a) <= (b) ? (a) : (b))
#define f2cmax(a,b) ((a) >= (b) ? (a) : (b))
#define dmin(a,b) (f2cmin(a,b))
#define dmax(a,b) (f2cmax(a,b))
#define bit_test(a,b)	((a) >> (b) & 1)
#define bit_clear(a,b)	((a) & ~((uinteger)1 << (b)))
#define bit_set(a,b)	((a) |  ((uinteger)1 << (b)))

#define abort_() { sig_die("Fortran abort routine called", 1); }
#define c_abs(z) (cabsf(Cf(z)))
#define c_cos(R,Z) { pCf(R)=ccos(Cf(Z)); }
#ifdef _MSC_VER
#define c_div(c, a, b) {Cf(c)._Val[0] = (Cf(a)._Val[0]/Cf(b)._Val[0]); Cf(c)._Val[1]=(Cf(a)._Val[1]/Cf(b)._Val[1]);}
#define z_div(c, a, b) {Cd(c)._Val[0] = (Cd(a)._Val[0]/Cd(b)._Val[0]); Cd(c)._Val[1]=(Cd(a)._Val[1]/Cd(b)._Val[1]);}
#else
#define c_div(c, a, b) {pCf(c) = Cf(a)/Cf(b);}
#define z_div(c, a, b) {pCd(c) = Cd(a)/Cd(b);}
#endif
#define c_exp(R, Z) {pCf(R) = cexpf(Cf(Z));}
#define c_log(R, Z) {pCf(R) = clogf(Cf(Z));}
#define c_sin(R, Z) {pCf(R) = csinf(Cf(Z));}
//#define c_sqrt(R, Z) {*(R) = csqrtf(Cf(Z));}
#define c_sqrt(R, Z) {pCf(R) = csqrtf(Cf(Z));}
#define d_abs(x) (fabs(*(x)))
#define d_acos(x) (acos(*(x)))
#define d_asin(x) (asin(*(x)))
#define d_atan(x) (atan(*(x)))
#define d_atn2(x, y) (atan2(*(x),*(y)))
#define d_cnjg(R, Z) { pCd(R) = conj(Cd(Z)); }
#define r_cnjg(R, Z) { pCf(R) = conjf(Cf(Z)); }
#define d_cos(x) (cos(*(x)))
#define d_cosh(x) (cosh(*(x)))
#define d_dim(__a, __b) ( *(__a) > *(__b) ? *(__a) - *(__b) : 0.0 )
#define d_exp(x) (exp(*(x)))
#define d_imag(z) (cimag(Cd(z)))
#define r_imag(z) (cimagf(Cf(z)))
#define d_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define r_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define d_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define r_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define d_log(x) (log(*(x)))
#define d_mod(x, y) (fmod(*(x), *(y)))
#define u_nint(__x) ((__x)>=0 ? floor((__x) + .5) : -floor(.5 - (__x)))
#define d_nint(x) u_nint(*(x))
#define u_sign(__a,__b) ((__b) >= 0 ? ((__a) >= 0 ? (__a) : -(__a)) : -((__a) >= 0 ? (__a) : -(__a)))
#define d_sign(a,b) u_sign(*(a),*(b))
#define r_sign(a,b) u_sign(*(a),*(b))
#define d_sin(x) (sin(*(x)))
#define d_sinh(x) (sinh(*(x)))
#define d_sqrt(x) (sqrt(*(x)))
#define d_tan(x) (tan(*(x)))
#define d_tanh(x) (tanh(*(x)))
#define i_abs(x) abs(*(x))
#define i_dnnt(x) ((integer)u_nint(*(x)))
#define i_len(s, n) (n)
#define i_nint(x) ((integer)u_nint(*(x)))
#define i_sign(a,b) ((integer)u_sign((integer)*(a),(integer)*(b)))
#define pow_dd(ap, bp) ( pow(*(ap), *(bp)))
#define pow_si(B,E) spow_ui(*(B),*(E))
#define pow_ri(B,E) spow_ui(*(B),*(E))
#define pow_di(B,E) dpow_ui(*(B),*(E))
#define pow_zi(p, a, b) {pCd(p) = zpow_ui(Cd(a), *(b));}
#define pow_ci(p, a, b) {pCf(p) = cpow_ui(Cf(a), *(b));}
#define pow_zz(R,A,B) {pCd(R) = cpow(Cd(A),*(B));}
#define s_cat(lpp, rpp, rnp, np, llp) { 	ftnlen i, nc, ll; char *f__rp, *lp; 	ll = (llp); lp = (lpp); 	for(i=0; i < (int)*(np); ++i) {         	nc = ll; 	        if((rnp)[i] < nc) nc = (rnp)[i]; 	        ll -= nc;         	f__rp = (rpp)[i]; 	        while(--nc >= 0) *lp++ = *(f__rp)++;         } 	while(--ll >= 0) *lp++ = ' '; }
#define s_cmp(a,b,c,d) ((integer)strncmp((a),(b),f2cmin((c),(d))))
#define s_copy(A,B,C,D) { int __i,__m; for (__i=0, __m=f2cmin((C),(D)); __i<__m && (B)[__i] != 0; ++__i) (A)[__i] = (B)[__i]; }
#define sig_die(s, kill) { exit(1); }
#define s_stop(s, n) {exit(0);}
static char junk[] = "\n@(#)LIBF77 VERSION 19990503\n";
#define z_abs(z) (cabs(Cd(z)))
#define z_exp(R, Z) {pCd(R) = cexp(Cd(Z));}
#define z_sqrt(R, Z) {pCd(R) = csqrt(Cd(Z));}
#define myexit_() break;
#define mycycle_() continue;
#define myceiling_(w) {ceil(w)}
#define myhuge_(w) {HUGE_VAL}
//#define mymaxloc_(w,s,e,n) {if (sizeof(*(w)) == sizeof(double)) dmaxloc_((w),*(s),*(e),n); else dmaxloc_((w),*(s),*(e),n);}
#define mymaxloc_(w,s,e,n) dmaxloc_(w,*(s),*(e),n)

/* procedure parameter types for -A and -C++ */


#ifdef __cplusplus
typedef logical (*L_fp)(...);
#else
typedef logical (*L_fp)();
#endif

static float spow_ui(float x, integer n) {
	float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static double dpow_ui(double x, integer n) {
	double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#ifdef _MSC_VER
static _Fcomplex cpow_ui(complex x, integer n) {
	complex pow={1.0,0.0}; unsigned long int u;
		if(n != 0) {
		if(n < 0) n = -n, x.r = 1/x.r, x.i=1/x.i;
		for(u = n; ; ) {
			if(u & 01) pow.r *= x.r, pow.i *= x.i;
			if(u >>= 1) x.r *= x.r, x.i *= x.i;
			else break;
		}
	}
	_Fcomplex p={pow.r, pow.i};
	return p;
}
#else
static _Complex float cpow_ui(_Complex float x, integer n) {
	_Complex float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#endif
#ifdef _MSC_VER
static _Dcomplex zpow_ui(_Dcomplex x, integer n) {
	_Dcomplex pow={1.0,0.0}; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x._Val[0] = 1/x._Val[0], x._Val[1] =1/x._Val[1];
		for(u = n; ; ) {
			if(u & 01) pow._Val[0] *= x._Val[0], pow._Val[1] *= x._Val[1];
			if(u >>= 1) x._Val[0] *= x._Val[0], x._Val[1] *= x._Val[1];
			else break;
		}
	}
	_Dcomplex p = {pow._Val[0], pow._Val[1]};
	return p;
}
#else
static _Complex double zpow_ui(_Complex double x, integer n) {
	_Complex double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#endif
static integer pow_ii(integer x, integer n) {
	integer pow; unsigned long int u;
	if (n <= 0) {
		if (n == 0 || x == 1) pow = 1;
		else if (x != -1) pow = x == 0 ? 1/x : 0;
		else n = -n;
	}
	if ((n > 0) || !(n == 0 || x == 1 || x != -1)) {
		u = n;
		for(pow = 1; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static integer dmaxloc_(double *w, integer s, integer e, integer *n)
{
	double m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static integer smaxloc_(float *w, integer s, integer e, integer *n)
{
	float m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static inline void cdotc_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Fcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conjf(Cf(&x[i]))._Val[0] * Cf(&y[i])._Val[0];
			zdotc._Val[1] += conjf(Cf(&x[i]))._Val[1] * Cf(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conjf(Cf(&x[i*incx]))._Val[0] * Cf(&y[i*incy])._Val[0];
			zdotc._Val[1] += conjf(Cf(&x[i*incx]))._Val[1] * Cf(&y[i*incy])._Val[1];
		}
	}
	pCf(z) = zdotc;
}
#else
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i])) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i*incx])) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
#endif
static inline void zdotc_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Dcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conj(Cd(&x[i]))._Val[0] * Cd(&y[i])._Val[0];
			zdotc._Val[1] += conj(Cd(&x[i]))._Val[1] * Cd(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conj(Cd(&x[i*incx]))._Val[0] * Cd(&y[i*incy])._Val[0];
			zdotc._Val[1] += conj(Cd(&x[i*incx]))._Val[1] * Cd(&y[i*incy])._Val[1];
		}
	}
	pCd(z) = zdotc;
}
#else
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i])) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i*incx])) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}
#endif	
static inline void cdotu_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Fcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cf(&x[i])._Val[0] * Cf(&y[i])._Val[0];
			zdotc._Val[1] += Cf(&x[i])._Val[1] * Cf(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cf(&x[i*incx])._Val[0] * Cf(&y[i*incy])._Val[0];
			zdotc._Val[1] += Cf(&x[i*incx])._Val[1] * Cf(&y[i*incy])._Val[1];
		}
	}
	pCf(z) = zdotc;
}
#else
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i]) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i*incx]) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
#endif
static inline void zdotu_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Dcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cd(&x[i])._Val[0] * Cd(&y[i])._Val[0];
			zdotc._Val[1] += Cd(&x[i])._Val[1] * Cd(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cd(&x[i*incx])._Val[0] * Cd(&y[i*incy])._Val[0];
			zdotc._Val[1] += Cd(&x[i*incx])._Val[1] * Cd(&y[i*incy])._Val[1];
		}
	}
	pCd(z) = zdotc;
}
#else
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i]) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i*incx]) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}
#endif
/*  -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/



/*  -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/



/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static integer c__3 = 3;
static integer c__2 = 2;

/* Subroutine */ int dgeqp3rk_(integer *m, integer *n, integer *nrhs, integer 
	*kmax, doublereal *abstol, doublereal *reltol, doublereal *a, integer 
	*lda, integer *k, doublereal *maxc2nrmk, doublereal *relmaxc2nrmk, 
	integer *jpiv, doublereal *tau, doublereal *work, integer *lwork, 
	integer *iwork, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    doublereal d__1, d__2;

    /* Local variables */
    extern /* Subroutine */ int dlaqp2rk_(integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *), dlaqp3rk_(integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, logical *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    doublereal maxc2nrm;
    logical done;
    integer jmax;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    integer j, jmaxc2nrm, jmaxb, nbmin, iinfo, n_sub__, minmn;
    doublereal myhugeval;
    integer jb, nb, kf;
    extern doublereal dlamch_(char *);
    extern integer idamax_(integer *, doublereal *, integer *);
    integer nx;
    doublereal safmin;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern logical disnan_(doublereal *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    integer kp1, lwkopt;
    logical lquery;
    integer jbf;
    doublereal eps;
    integer iws, ioffset;


/*  -- LAPACK computational routine -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */


/*  ===================================================================== */


/*     Test input arguments */
/*     ==================== */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --jpiv;
    --tau;
    --work;
    --iwork;

    /* Function Body */
    *info = 0;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*kmax < 0) {
	*info = -4;
    } else if (disnan_(abstol)) {
	*info = -5;
    } else if (disnan_(reltol)) {
	*info = -6;
    } else if (*lda < f2cmax(1,*m)) {
	*info = -8;
    }

/*     If the input parameters M, N, NRHS, KMAX, LDA are valid: */
/*       a) Test the input workspace size LWORK for the minimum */
/*          size requirement IWS. */
/*       b) Determine the optimal block size NB and optimal */
/*          workspace size LWKOPT to be returned in WORK(1) */
/*          in case of (1) LWORK < IWS, (2) LQUERY = .TRUE., */
/*          (3) when routine exits. */
/*     Here, IWS is the miminum workspace required for unblocked */
/*     code. */

    if (*info == 0) {
	minmn = f2cmin(*m,*n);
	if (minmn == 0) {
	    iws = 1;
	    lwkopt = 1;
	} else {

/*           Minimal workspace size in case of using only unblocked */
/*           BLAS 2 code in DLAQP2RK. */
/*           1) DGEQP3RK and DLAQP2RK: 2*N to store full and partial */
/*              column 2-norms. */
/*           2) DLAQP2RK: N+NRHS-1 to use in WORK array that is used */
/*              in DLARF subroutine inside DLAQP2RK to apply an */
/*              elementary reflector from the left. */
/*           TOTAL_WORK_SIZE = 3*N + NRHS - 1 */

	    iws = *n * 3 + *nrhs - 1;

/*           Assign to NB optimal block size. */

	    nb = ilaenv_(&c__1, "DGEQP3RK", " ", m, n, &c_n1, &c_n1, (ftnlen)
		    8, (ftnlen)1);

/*           A formula for the optimal workspace size in case of using */
/*           both unblocked BLAS 2 in DLAQP2RK and blocked BLAS 3 code */
/*           in DLAQP3RK. */
/*           1) DGEQP3RK, DLAQP2RK, DLAQP3RK: 2*N to store full and */
/*              partial column 2-norms. */
/*           2) DLAQP2RK: N+NRHS-1 to use in WORK array that is used */
/*              in DLARF subroutine to apply an elementary reflector */
/*              from the left. */
/*           3) DLAQP3RK: NB*(N+NRHS) to use in the work array F that */
/*              is used to apply a block reflector from */
/*              the left. */
/*           4) DLAQP3RK: NB to use in the auxilixary array AUX. */
/*           Sizes (2) and ((3) + (4)) should intersect, therefore */
/*           TOTAL_WORK_SIZE = 2*N + NB*( N+NRHS+1 ), given NBMIN=2. */

	    lwkopt = (*n << 1) + nb * (*n + *nrhs + 1);
	}
	work[1] = (doublereal) lwkopt;

	if (*lwork < iws && ! lquery) {
	    *info = -15;
	}
    }

/*      NOTE: The optimal workspace size is returned in WORK(1), if */
/*            the input parameters M, N, NRHS, KMAX, LDA are valid. */

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGEQP3RK", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible for M=0 or N=0. */

    if (minmn == 0) {
	*k = 0;
	*maxc2nrmk = 0.;
	*relmaxc2nrmk = 0.;
	work[1] = (doublereal) lwkopt;
	return 0;
    }

/*     ================================================================== */

/*     Initialize column pivot array JPIV. */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	jpiv[j] = j;
    }

/*     ================================================================== */

/*     Initialize storage for partial and exact column 2-norms. */
/*     a) The elements WORK(1:N) are used to store partial column */
/*        2-norms of the matrix A, and may decrease in each computation */
/*        step; initialize to the values of complete columns 2-norms. */
/*     b) The elements WORK(N+1:2*N) are used to store complete column */
/*        2-norms of the matrix A, they are not changed during the */
/*        computation; initialize the values of complete columns 2-norms. */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	work[j] = dnrm2_(m, &a[j * a_dim1 + 1], &c__1);
	work[*n + j] = work[j];
    }

/*     ================================================================== */

/*     Compute the pivot column index and the maximum column 2-norm */
/*     for the whole original matrix stored in A(1:M,1:N). */

    kp1 = idamax_(n, &work[1], &c__1);
    maxc2nrm = work[kp1];

/*     ==================================================================. */

    if (disnan_(&maxc2nrm)) {

/*        Check if the matrix A contains NaN, set INFO parameter */
/*        to the column number where the first NaN is found and return */
/*        from the routine. */

	*k = 0;
	*info = kp1;

/*        Set MAXC2NRMK and  RELMAXC2NRMK to NaN. */

	*maxc2nrmk = maxc2nrm;
	*relmaxc2nrmk = maxc2nrm;

/*        Array TAU is not set and contains undefined elements. */

	work[1] = (doublereal) lwkopt;
	return 0;
    }

/*     =================================================================== */

    if (maxc2nrm == 0.) {

/*        Check is the matrix A is a zero matrix, set array TAU and */
/*        return from the routine. */

	*k = 0;
	*maxc2nrmk = 0.;
	*relmaxc2nrmk = 0.;

	i__1 = minmn;
	for (j = 1; j <= i__1; ++j) {
	    tau[j] = 0.;
	}

	work[1] = (doublereal) lwkopt;
	return 0;

    }

/*     =================================================================== */

    myhugeval = dlamch_("Overflow");

    if (maxc2nrm > myhugeval) {

/*        Check if the matrix A contains +Inf or -Inf, set INFO parameter */
/*        to the column number, where the first +/-Inf  is found plus N, */
/*        and continue the computation. */

	*info = *n + kp1;

    }

/*     ================================================================== */

/*     Quick return if possible for the case when the first */
/*     stopping criterion is satisfied, i.e. KMAX = 0. */

    if (*kmax == 0) {
	*k = 0;
	*maxc2nrmk = maxc2nrm;
	*relmaxc2nrmk = 1.;
	i__1 = minmn;
	for (j = 1; j <= i__1; ++j) {
	    tau[j] = 0.;
	}
	work[1] = (doublereal) lwkopt;
	return 0;
    }

/*     ================================================================== */

    eps = dlamch_("Epsilon");

/*     Adjust ABSTOL */

    if (*abstol >= 0.) {
	safmin = dlamch_("Safe minimum");
/* Computing MAX */
	d__1 = *abstol, d__2 = safmin * 2.;
	*abstol = f2cmax(d__1,d__2);
    }

/*     Adjust RELTOL */

    if (*reltol >= 0.) {
	*reltol = f2cmax(*reltol,eps);
    }

/*     =================================================================== */

/*     JMAX is the maximum index of the column to be factorized, */
/*     which is also limited by the first stopping criterion KMAX. */

    jmax = f2cmin(*kmax,minmn);

/*     =================================================================== */

/*     Quick return if possible for the case when the second or third */
/*     stopping criterion for the whole original matrix is satified, */
/*     i.e. MAXC2NRM <= ABSTOL or RELMAXC2NRM <= RELTOL */
/*     (which is ONE <= RELTOL). */

    if (maxc2nrm <= *abstol || 1. <= *reltol) {

	*k = 0;
	*maxc2nrmk = maxc2nrm;
	*relmaxc2nrmk = 1.;

	i__1 = minmn;
	for (j = 1; j <= i__1; ++j) {
	    tau[j] = 0.;
	}

	work[1] = (doublereal) lwkopt;
	return 0;
    }

/*     ================================================================== */
/*     Factorize columns */
/*     ================================================================== */

/*     Determine the block size. */

    nbmin = 2;
    nx = 0;

    if (nb > 1 && nb < minmn) {

/*        Determine when to cross over from blocked to unblocked code. */
/*        (for N less than NX, unblocked code should be used). */

/* Computing MAX */
	i__1 = 0, i__2 = ilaenv_(&c__3, "DGEQP3RK", " ", m, n, &c_n1, &c_n1, (
		ftnlen)8, (ftnlen)1);
	nx = f2cmax(i__1,i__2);

	if (nx < minmn) {

/*           Determine if workspace is large enough for blocked code. */

	    if (*lwork < lwkopt) {

/*              Not enough workspace to use optimal block size that */
/*              is currently stored in NB. */
/*              Reduce NB and determine the minimum value of NB. */

		nb = (*lwork - (*n << 1)) / (*n + 1);
/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DGEQP3RK", " ", m, n, &c_n1, 
			&c_n1, (ftnlen)8, (ftnlen)1);
		nbmin = f2cmax(i__1,i__2);

	    }
	}
    }

/*     ================================================================== */

/*     DONE is the boolean flag to rerpresent the case when the */
/*     factorization completed in the block factorization routine, */
/*     before the end of the block. */

    done = FALSE_;

/*     J is the column index. */

    j = 1;

/*     (1) Use blocked code initially. */

/*     JMAXB is the maximum column index of the block, when the */
/*     blocked code is used, is also limited by the first stopping */
/*     criterion KMAX. */

/* Computing MIN */
    i__1 = *kmax, i__2 = minmn - nx;
    jmaxb = f2cmin(i__1,i__2);

    if (nb >= nbmin && nb < jmax && jmaxb > 0) {

/*        Loop over the column blocks of the matrix A(1:M,1:JMAXB). Here: */
/*        J   is the column index of a column block; */
/*        JB  is the column block size to pass to block factorization */
/*            routine in a loop step; */
/*        JBF is the number of columns that were actually factorized */
/*            that was returned by the block factorization routine */
/*            in a loop step, JBF <= JB; */
/*        N_SUB is the number of columns in the submatrix; */
/*        IOFFSET is the number of rows that should not be factorized. */

	while(j <= jmaxb) {

/* Computing MIN */
	    i__1 = nb, i__2 = jmaxb - j + 1;
	    jb = f2cmin(i__1,i__2);
	    n_sub__ = *n - j + 1;
	    ioffset = j - 1;

/*           Factorize JB columns among the columns A(J:N). */

	    i__1 = *n + *nrhs - j + 1;
	    dlaqp3rk_(m, &n_sub__, nrhs, &ioffset, &jb, abstol, reltol, &kp1, 
		    &maxc2nrm, &a[j * a_dim1 + 1], lda, &done, &jbf, 
		    maxc2nrmk, relmaxc2nrmk, &jpiv[j], &tau[j], &work[j], &
		    work[*n + j], &work[(*n << 1) + 1], &work[(*n << 1) + jb 
		    + 1], &i__1, &iwork[1], &iinfo);

/*           Set INFO on the first occurence of Inf. */

	    if (iinfo > n_sub__ && *info == 0) {
		*info = (ioffset << 1) + iinfo;
	    }

	    if (done) {

/*              Either the submatrix is zero before the end of the */
/*              column block, or ABSTOL or RELTOL criterion is */
/*              satisfied before the end of the column block, we can */
/*              return from the routine. Perform the following before */
/*              returning: */
/*                a) Set the number of factorized columns K, */
/*                   K = IOFFSET + JBF from the last call of blocked */
/*                   routine. */
/*                NOTE: 1) MAXC2NRMK and RELMAXC2NRMK are returned */
/*                         by the block factorization routine; */
/*                      2) The remaining TAUs are set to ZERO by the */
/*                         block factorization routine. */

		*k = ioffset + jbf;

/*              Set INFO on the first occurrence of NaN, NaN takes */
/*              prcedence over Inf. */

		if (iinfo <= n_sub__ && iinfo > 0) {
		    *info = ioffset + iinfo;
		}

/*              Return from the routine. */

		work[1] = (doublereal) lwkopt;

		return 0;

	    }

	    j += jbf;

	}

    }

/*     Use unblocked code to factor the last or only block. */
/*     J = JMAX+1 means we factorized the maximum possible number of */
/*     columns, that is in ELSE clause we need to compute */
/*     the MAXC2NORM and RELMAXC2NORM to return after we processed */
/*     the blocks. */

    if (j <= jmax) {

/*        N_SUB is the number of columns in the submatrix; */
/*        IOFFSET is the number of rows that should not be factorized. */

	n_sub__ = *n - j + 1;
	ioffset = j - 1;

	i__1 = jmax - j + 1;
	dlaqp2rk_(m, &n_sub__, nrhs, &ioffset, &i__1, abstol, reltol, &kp1, &
		maxc2nrm, &a[j * a_dim1 + 1], lda, &kf, maxc2nrmk, 
		relmaxc2nrmk, &jpiv[j], &tau[j], &work[j], &work[*n + j], &
		work[(*n << 1) + 1], &iinfo);

/*        ABSTOL or RELTOL criterion is satisfied when the number of */
/*        the factorized columns KF is smaller then the  number */
/*        of columns JMAX-J+1 supplied to be factorized by the */
/*        unblocked routine, we can return from */
/*        the routine. Perform the following before returning: */
/*           a) Set the number of factorized columns K, */
/*           b) MAXC2NRMK and RELMAXC2NRMK are returned by the */
/*              unblocked factorization routine above. */

	*k = j - 1 + kf;

/*        Set INFO on the first exception occurence. */

/*        Set INFO on the first exception occurence of Inf or NaN, */
/*        (NaN takes precedence over Inf). */

	if (iinfo > n_sub__ && *info == 0) {
	    *info = (ioffset << 1) + iinfo;
	} else if (iinfo <= n_sub__ && iinfo > 0) {
	    *info = ioffset + iinfo;
	}

    } else {

/*        Compute the return values for blocked code. */

/*        Set the number of factorized columns if the unblocked routine */
/*        was not called. */

	*k = jmax;

/*        If there exits a residual matrix after the blocked code: */
/*           1) compute the values of MAXC2NRMK, RELMAXC2NRMK of the */
/*              residual matrix, otherwise set them to ZERO; */
/*           2) Set TAU(K+1:MINMN) to ZERO. */

	if (*k < minmn) {
	    i__1 = *n - *k;
	    jmaxc2nrm = *k + idamax_(&i__1, &work[*k + 1], &c__1);
	    *maxc2nrmk = work[jmaxc2nrm];
	    if (*k == 0) {
		*relmaxc2nrmk = 1.;
	    } else {
		*relmaxc2nrmk = *maxc2nrmk / maxc2nrm;
	    }

	    i__1 = minmn;
	    for (j = *k + 1; j <= i__1; ++j) {
		tau[j] = 0.;
	    }

	}

/*     END IF( J.LE.JMAX ) THEN */

    }

    work[1] = (doublereal) lwkopt;

    return 0;

/*     End of DGEQP3RK */

} /* dgeqp3rk_ */

