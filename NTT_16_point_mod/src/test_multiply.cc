#include "ntt16point.h"
#include "include.h"


#define  SMPL	64

using namespace adf;

void test_multiply (
		input_window_int32  * restrict inputx,
	    output_window_int32 * restrict outputy){

    int32 *xbuff =  (int32 *)inputx->ptr;    //read access
	int32 *ybuff =  (int32 *)outputy->ptr;    //write


	stage0_ntt(xbuff, ybuff);

}

