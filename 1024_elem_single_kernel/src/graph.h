
#include "kernels.h"

extern int32 ntt_1a[1024];/////////////////////
extern int32 ntt_2a[1024];


extern int32 stage0_tw[768];
extern int32 stage1_tw[192];
extern int32 stage2_tw[48];



using namespace adf;


class test_graph : public adf::graph{

public:

    parameter buf1a;  ////////////////////////////////////
    parameter buf2a;

    parameter buf3;
    parameter buf4;
    parameter buf5;



	adf::port<input>  gr_in;
    adf::port<output> gr_out;
    adf::kernel kl;

    test_graph(){

    	kl = adf::kernel::create(test_multiply);
    	adf::runtime<ratio>(kl) = 0.9 ;
    	source(kl) = "test_multiply.cc" ;


        buf1a = parameter::array(ntt_1a);//////////////////////
        buf2a = parameter::array(ntt_2a);


        buf3 = parameter::array(stage0_tw);
        buf4 = parameter::array(stage1_tw);
        buf5 = parameter::array(stage2_tw);


        connect<>(buf1a, kl);//////////////////////////
        connect<>(buf2a, kl);

        connect<>(buf3, kl);
        connect<>(buf4, kl);
        connect<>(buf5, kl);


    	adf::connect<window<1024*4>>(gr_in, kl.in[0]);
    	adf::connect<window<1024*4>>(kl.out[0], gr_out);

    };

};
