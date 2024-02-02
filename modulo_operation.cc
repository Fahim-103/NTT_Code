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
	v16int32 xbuff;
	v8int32 x21buff, x22buff;


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



	n0 = srs(lmul4_sym     (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 0) , 0);  x21buff = upd_v(x21buff, 0, n0);

	n1 = srs(lmul4_antisym (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 1) , 0) ; x21buff = upd_v(x21buff, 1, n1);


	n2 = srs(lmul4_sym     (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 2)  ,0) ; x22buff = upd_v(x22buff, 2, n2);
	n3 = srs(lmul4_antisym (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 3)  ,0) ; x22buff = upd_v(x22buff, 3, n3);

	/////////////////////////////////////////////

	v8float x1, x2, y, y_inv;

	x1 = as_v8float(x21buff);
	x2 = as_v8float(x22buff);
	//x = as_v8float(concat(n0,n1));

	y = as_v8float(aie::broadcast<int32,8> (7681));


	aie::vector<float,8> vf_div,vf1,vf1_inv,vf2;

	vf1 = y;
	vf2 = x1;

	vf1_inv = aie::inv(vf1);///////////////////////////
	vf_div  = aie::mul(vf1_inv,vf2);


	v8int32 vf_div_fix = as_v8int32(vf_div);


	float   n = inv(7681);
	int a = (int)(n * (-184224));

	printf("%f \n", n);
	printf("%d \n", a);
	printf("%d \n", -184224- a*7681 + 7681);

	//vf_mul = aie::mul(vf_div,vf1);

	//aie::vector<int32,16> vout = aie::sub(x2buff - vf_mul);








	//136 100 151 225 121 166 150 39 249 202 91 75 120 16 90 141




	aie::vector<int32,4> n0_vec = n0;
	aie::vector<int32,4> n1_vec = n1;
	aie::vector<int32,4> n2_vec = n2;
	aie::vector<int32,4> n3_vec = n3;

	aie::vector<int32,8> x1_vec = vf_div_fix;


	aie::print(n0_vec,true,"n0 value=");
	aie::print(n1_vec,true,"n1 value=");
	aie::print(n2_vec,true,"n2 value=");
	aie::print(n3_vec,true,"n3 value=");

	aie::print(vf1_inv,true,"float_value= ");
	aie::print(x1_vec,true,"fx_value= ");





}
