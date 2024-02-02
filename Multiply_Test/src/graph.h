
#include <kernels.h>

using namespace adf;


class test_graph : public adf::graph{

public:


	adf::port<input>  gr_in;
    adf::port<output> gr_out;
    adf::kernel kl;

    test_graph(){

    	kl = adf::kernel::create(test_multiply);
    	adf::runtime<ratio>(kl) = 0.8 ;
    	source(kl) = "test_multiply.cc" ;




    	adf::connect<>(gr_in, kl.in[0]);
    	adf::connect<>(kl.out[0], gr_out);

    };

};
