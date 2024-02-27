//taking two 16 bit buffers (xbuff, zbuff) and multiplying

//#include <adf.h>
#include "nttsub6.h"
#include "include.h"
#include "twiddle.h"


using namespace adf;

void test_multiply (input_window_int32  * restrict inputx,
			        output_window_int32 * restrict outputy){



    int32 *xbuff =  (int32 *)inputx->ptr;    //read access
	int32 *ybuff =  (int32 *)outputy->ptr;    //write



	int32 * restrict tw00 = (int32 * restrict) stage0_tw;
	int32 * restrict tw01 = (int32 * restrict) stage1_tw;
	int32 * restrict tw02 = (int32 * restrict) stage2_tw;


	int32 * restrict ntt_tmp1 = ntt_1a;  //pointer for storage arra

	int32 * restrict ntt_tmp2 =  ntt_2a;


	stage0_ntt(xbuff, tw00, ntt_tmp1);


	for (int i = 0; i < 4; i++){

		stage1_ntt(ntt_tmp1, tw01, ntt_tmp2, i);



	}


	for (int i = 0; i < 16; i++){

		stage2_ntt(ntt_tmp2, tw02, ntt_tmp1, i);

	}


	stage3_ntt(ntt_tmp1, ybuff);



}

