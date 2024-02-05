#ifndef __NTT16POINT_H__
#define __NTT16POINT_H__


#include <adf.h>
#include "twiddle.h"

#include "aie_api/aie.hpp"
#include "aie_api/utils.hpp"
#include "aie_api/aie_adf.hpp"


inline __attribute__((always_inline)) void stage0_ntt ( int32 * restrict x, int32 * restrict y){

	v4int32 * xx = (v4int32 *) x; //16 byte 4 elem update
	v4int32 * yy = (v4int32 *) y;
	v16int32 x1buff, x2buff;

	// update x1buff with proper permutation

	x1buff = upd_v(upd_v(x1buff, 0, *xx++), 1, *xx++);
	x1buff = upd_v(upd_v(x1buff, 3, *xx++), 2, *xx++);

	// 4-point NTT twiddle

	v8int32 * zz = (v8int32 *)tw; ////////
	v8int32 zbuff = *zz;

	// 4-point NTT stage00

	v4int32 m0, m1, m2, m3;

	v4int32 * t = (v4int32 *) tww;

	v4int32 t0 = *t++;
	v4int32 t1 = *t++;
	v4int32 t2 = *t++;
	v4int32 t3 = *t;


	m0 = srs(lmul4_sym     (x1buff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 0) , 0);  x2buff = upd_v(x2buff, 0, m0);
	m1 = srs(mul(srs(lmul4_antisym (x1buff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 1) , 0) , t1),0) ; x2buff = upd_v(x2buff, 1, m1);


	m2 = srs(mul(srs(lmul4_sym     (x1buff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 2)  ,0) , t2),0) ; x2buff = upd_v(x2buff, 2, m2);
	m3 = srs(mul(srs(lmul4_antisym (x1buff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 3)  ,0) , t3),0) ; x2buff = upd_v(x2buff, 3, m3);


	// 4-point NTT stage01

	aie::vector<int32,16> x_vec = x2buff;
	v16int32 temp_buff = aie::transpose(x_vec, 4, 4) ;

	v4int32 k0, k1, k2, k3;

	k0 = srs(lmul4_sym     (temp_buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 0) , 0) ; *yy++ = k0;
	k1 = srs(lmul4_antisym (temp_buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 1) , 0) ; *yy++ = k1;


	k2 = srs(lmul4_sym     (temp_buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 2)  ,0) ; *yy++ = k2;
	k3 = srs(lmul4_antisym (temp_buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 3)  ,0) ; *yy   = k3;

}

#endif
