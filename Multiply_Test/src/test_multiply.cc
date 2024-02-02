//taking two 16 bit buffers (xbuff, zbuff) and multiplying

#include <adf.h>
#include "include.h"

#include "aie_api/aie.hpp"
#include "aie_api/utils.hpp"
#include "aie_api/aie_adf.hpp"

#define  SMPL	64

using namespace adf;

void test_multiply (input_buffer <int32, extents<SMPL>> & ix,
				output_buffer <int32, extents<SMPL>> & oy){

	auto in_buff  = aie::begin_vector<32>(ix);
	auto out_buff = aie::begin_vector<32>(oy);


	v4int32 * xx = (v4int32 *) x; //256 bit update
	v16int32 xbuff, x2buff;


	xbuff = upd_v(upd_v(xbuff, 0, *xx++), 1, *xx++);
	xbuff = upd_v(upd_v(xbuff, 3, *xx++), 2, *xx++);


	v8int32 * zz = (v8int32 *)tw;
	v8int32 zbuff = *zz;


	v4int32 n0, n1, n2, n3;

	v4int32 * t = (v4int32 *) tww;

	v4int32 t0 = *t++;
	v4int32 t1 = *t++;
	v4int32 t2 = *t++;
	v4int32 t3 = *t;



	n0 = srs(lmul4_sym     (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 0) , 0);  x2buff = upd_v(x2buff, 0, n0);

	n1 = srs(lmul4_antisym (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 1) , 0) ; x2buff = upd_v(x2buff, 1, n1);


	n2 = srs(lmul4_sym     (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 2)  ,0) ; x2buff = upd_v(x2buff, 2, n2);
	n3 = srs(lmul4_antisym (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 3)  ,0) ; x2buff = upd_v(x2buff, 3, n3);

	/////////////////////////////////////////////

	v16int32 xtbuff;
	v4int32 m0, m1, m2, m3;


	m0 = srs(lmul4_sym     (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 0) , 0);  xtbuff = upd_v(xtbuff, 0, m0);

	m1 = srs(mul(srs(lmul4_antisym (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 1) , 0) , t1),0) ; xtbuff = upd_v(xtbuff, 1, m1);


	m2 = srs(mul(srs(lmul4_sym     (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 2)  ,0) , t2),0) ; xtbuff = upd_v(xtbuff, 2, m2);
	m3 = srs(mul(srs(lmul4_antisym (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 3)  ,0) , t3),0) ; xtbuff = upd_v(xtbuff, 3, m3);




	//v16int32 temp_buff = aie::


	aie::vector<int32,16> x1_vec = xbuff;
	aie::vector<int32,8>  x2_vec = zbuff;
	aie::vector<int32,16> x3_vec = x2buff;


	//aie::vector<int32,16> x4_vec = aie::transpose(x3_vec, 4, 4) ;




	aie::vector<int32,16> x5_vec = xtbuff;

	v16int32 temp_buff = aie::transpose(x5_vec, 4, 4) ;

	///////////////////////////////////////////// combining//////////

	v16int32 xt1buff;
	v4int32 k0, k1, k2, k3;



	k0 = srs(lmul4_sym     (temp_buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 0) , 0);  xt1buff = upd_v(xt1buff, 0, k0);

	k1 = srs(lmul4_antisym (temp_buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 1) , 0) ; xt1buff = upd_v(xt1buff, 1, k1);


	k2 = srs(lmul4_sym     (temp_buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 2)  ,0) ; xt1buff = upd_v(xt1buff, 2, k2);
	k3 = srs(lmul4_antisym (temp_buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 3)  ,0) ; xt1buff = upd_v(xt1buff, 3, k3);







	//136 100 151 225 121 166 150 39 249 202 91 75 120 16 90 141




	aie::vector<int32,16> x4_vec = temp_buff;
	aie::vector<int32,16> x6_vec = xt1buff;

	x6_vec = aie::add (x6_vec, int32 (2000*257));


	aie::vector<int32,4> n0_vec = n0;
	aie::vector<int32,4> n1_vec = n1;
	aie::vector<int32,4> n2_vec = n2;
	aie::vector<int32,4> n3_vec = n3;

	aie::print(x1_vec,true,"xbuff value=");
	aie::print(x2_vec,true,"zbuff value=");



	aie::print(n0_vec,true,"n0 value=");
	aie::print(n1_vec,true,"n1 value=");
	aie::print(n2_vec,true,"n2 value=");
	aie::print(n3_vec,true,"n3 value=");

	aie::print_matrix(x3_vec,4,"x2buff value=");

	aie::print_matrix(x5_vec,4,"twiddle mltpl value=");

	aie::print(x4_vec,true,"transpose value=");

	aie::print_matrix(x4_vec,4,"transpose value matrix=");
	aie::print_matrix(x6_vec,4,"end matrix=");


	//aie::vector<int32,16> x9_vec = aie::sub()

}
