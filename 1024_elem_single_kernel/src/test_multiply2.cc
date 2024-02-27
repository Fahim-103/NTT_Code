//taking two 16 bit buffers (xbuff, zbuff) and multiplying

#include <adf.h>
#include "nttsub.h"
#include "include.h"
#include "twiddle.h"



using namespace adf;

void test_multiply (input_window_int32  * restrict inputx,
			        output_window_int32 * restrict outputy){

    int32 *xbuff =  (int32 *)inputx->ptr;    //read access
	int32 *ybuff =  (int32 *)outputy->ptr;    //write


	int32 * restrict tw01 = (int32 *) stage0_tw1;
	int32 * restrict tw02 = (int32 *) stage0_tw2;
	int32 * restrict tw03 = (int32 *) stage0_tw3;


	int32 * restrict ntt_tmp1 =  ntt_1;  //pointer for storage array
   // int32 * restrict ntt_tmp2 =  ntt_2;


	stage0_ntt(xbuff,  ntt_tmp1, tw01, tw02, tw03);



	for (int r = 0; r<1024; r++){

		//printf("%d ", *ntt_tmp1++);

		*ybuff++ = *ntt_tmp1++;
	}






}

/*



#include "aie_api/aie.hpp"
#include "aie_api/utils.hpp"
#include "aie_api/aie_adf.hpp"
#include "aie_api/operators.hpp"

#define  SMPL	64

using namespace adf;

void test_multiply (input_window_int32  * restrict inputx,
			        output_window_int32 * restrict outputy){

    int32 *xbuff =  (int32 *)inputx->ptr;    //read access
	int32 *ybuff =  (int32 *)outputy->ptr;    //write

	int32 chess_storage(%chess_alignof(int16)) tmp1_buff[16];
	int32 chess_storage(%chess_alignof(int32)) tmp2_buff[16];

	v4int32 * restrict tmp1 = (v4int32 *) tmp1_buff;
	int32 * restrict tmp2 = (int32 *) tmp2_buff;

	v4int32 * restrict tmp3 = (v4int32 *) (tmp1+1);
	int32 * in = (int32 *) xbuff;


	*tmp3++ = *in++;
	*tmp3++ = *in++;
	*tmp3++ = *in++;
	*tmp3++ = *in++;






	//int32 * restrict tmp1 =  tmp1_buff;
	//int32 * restrict tmp2 =  tmp2_buff;

	for (int i = 0; i<16; i++){

			tmp2[i] = in[i];
		}


	for (int i = 0; i<16; i++){

		printf("%d ", tmp2_buff[i]);
	}




}





*/





















/*
	v4int32 * xx = (v4int32 *) x; //256 bit update
	v16int32 xbuff, x2buff;


	xbuff = upd_v(upd_v(xbuff, 0, *xx++), 1, *xx++);
	xbuff = upd_v(upd_v(xbuff, 3, *xx++), 2, *xx++);


	v8int32 * zz = (v8int32 *)tw;
	v8int32 zbuff = *zz;


	v4int32 n0, n1, n2, n3 , n_test, n_t;

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

	aie::accum<acc80,4> x_con_f2 = lmul4_sym     (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 0);
	n_test = srs(x_con_f2,32);

	n_t = n0-n2;

	//v8int32 x_con_f2_down_q = srs( mul(aie::downshift(x_con_f2,16), p0), 0);



	//136 100 151 225 121 166 150 39 249 202 91 75 120 16 90 141


	v4int64 m0, m1, m2, m3;


	m0 = lsrs(lmul4_sym     (xbuff, 0, 0x2310, 4, 12, zbuff, 0, 0x0000, 0) , 0);




	aie::vector<int32,4> n0_vec = n0;
	aie::vector<int32,4> n1_vec = n1;
	aie::vector<int32,4> n2_vec = n2;
	aie::vector<int32,4> n3_vec = n3;


	//v4int32 n4 = as_v4int32 (m0);
	aie::vector<int32,4> n4_vec = n_t;





	aie::print(n0_vec,true,"n0 value=");
	aie::print(n4_vec,true,"m0 value=");

	aie::print(n1_vec,true,"n1 value=");
	aie::print(n2_vec,true,"n2 value=");
	aie::print(n3_vec,true,"n3 value=");




	//aie::vector<int32,16> x9_vec = aie::sub()
*/
