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


	v4int32 n0, n1, n2, n3, t1, t2, t3 ;

	v4int32 * t = (v4int32 *) tww;

	t1 = *t++;
	t2 = *t++;
	t3 = *t;


	n0 = srs(lmul4_sym             (xbuff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 0) , 0);  x2buff = upd_v(x2buff, 0, n0);
	n1 = srs(mul(srs(lmul4_antisym (xbuff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 1) , 0) , t1),0) ; x2buff = upd_v(x2buff, 1, n1);


	n2 = srs(mul(srs(lmul4_sym     (xbuff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 2) , 0) , t2),0) ; x2buff = upd_v(x2buff, 3, n2);
	n3 = srs(mul(srs(lmul4_antisym (xbuff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 3) , 0) , t3),0) ; x2buff = upd_v(x2buff, 2, n3);


	v4int32 m0, m1, m2, m3;

	m0 = srs(lmul4_sym             (x2buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 0) , 0);  xbuff = upd_v(xbuff, 0, m0);
	m1 = srs(mul(srs(lmul4_antisym (x2buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 1) , 0) , t1),0) ; xbuff = upd_v(xbuff, 1, m1);


	m2 = srs(mul(srs(lmul4_sym     (x2buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 2) , 0) , t2),0) ; xbuff = upd_v(xbuff, 3, m2);
	m3 = srs(mul(srs(lmul4_antisym (x2buff, 0, 0x3210, 4, 12, zbuff, 0, 0x0000, 3) , 0) , t3),0) ; xbuff = upd_v(xbuff, 2, m3);




	aie::vector<int32,16> x1_vec = xbuff;
	aie::vector<int32,8>  x2_vec = zbuff;
	aie::vector<int32,16> x3_vec = x2buff;


	aie::vector<int32,4> n0_vec = n0;
	aie::vector<int32,4> n1_vec = n1;
	aie::vector<int32,4> n2_vec = n2;
	aie::vector<int32,4> n3_vec = n3;

	aie::print(x1_vec,true,"xbuff value=");
	aie::print(x2_vec,true,"zbuff value=");
	aie::print(x3_vec,true,"x2buff value=");


	aie::print(n0_vec,true,"n0 value=");
	aie::print(n1_vec,true,"n1 value=");
	aie::print(n2_vec,true,"n2 value=");
	aie::print(n3_vec,true,"n3 value=");

}


/*
//v16int32 xbuff =

int16 const chess_storage(%chess_alignof(v16int16)) x[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
v8int16 * xx = (v8int16 *) x;
v8int16 const xbuff = *xx++;
v8int16 const zbuff = *xx;




aie::vector<int16,8> x1_vec = xbuff;
aie::vector<int16,8> x2_vec = zbuff;

aie::print(x1_vec,true,"xbuff value=");
aie::print(x2_vec,true,"zbuff value=");


	//upd_w(upd_w(buff, 0, window_readincr_v8(x0)), 1, window_readincr_v8(x1))
	//upd_w = 128 upd_v = 256 upd_x = 512

	//v16cint16 czbuff = *cxx; //////////

	//v4acc80 acc;

There are four main variants of the SRS intrinsics based on width of input and output data-types:

    bsrs is used to convert integer
        48-bit accumulator data into a corresponding signed 8-bit vector
    ubsrs is used to convert integer
        48-bit accumulator data into a corresponding unsigned 8-bit vector
    srs is used to convert integer
        48-bit accumulator data into a corresponding 16-bit vector, or
        80-bit accumulator data into a corresponding 32-bit vector  //////////////////////////
    lsrs is used to convert integer
        48-bit accumulator data into a corresponding 32-bit vector, or
        80-bit accumulator data into a corresponding 64-bit vector







*/

//////////////////////////////////////


//acc=mac16(acc, xbuff, 0, 0x73727170, 0x77767574, 0x3120, zbuff, 0, 0x0, 0x0, 1);

//lsrs(mul4_sym(    bufa, 0, 0x3210, 4, 12, coe, 0, 0x0000, 0)

//v4int32 test;

//test = srs(acc, 0); // srs 128 b acc80 ;;; lsrs 256 b for int for acc80


//aie::vector<cint16,16> cx2_vec = czbuff; ///////

//v16cint16 * cxx = (v16cint32 *) x; //


//aie::vector<cint16,16> cx2_vec = czbuff; ///////

//aie::print(cx2_vec,true,"czbuff value="); //////




/*
for (int i = 0; i<16; i++)
	{

		*out_buff++ = *in_buff++;


	}
*/
