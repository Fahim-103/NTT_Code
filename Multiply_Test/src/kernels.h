#include <adf.h>

#define  SMPL	64

using namespace adf;

void test_multiply (input_buffer <int32, extents<SMPL>> & ix,
				    output_buffer <int32, extents<SMPL>> & oy);
