
#ifndef __INCLUDES_H__
#define __INCLUDES_H__

int32 const chess_storage(%chess_alignof(v4int32)) x[16] =   {160, 124, 81, 103, 204, 114, 75, 250, 15, 138, 194, 38, 19, 58, 39, 155};

int32 const chess_storage(%chess_alignof(v4int32)) tw[8] =   {1, 16, -1, -16,
										                      10000, 1000000, 100, 10}; //for zbuff twiddle for 4-point NTT w_4


int32 const chess_storage(%chess_alignof(v4int32)) tww[16] = {1,  1,   1,   1,
		                                                      1, 32, 129, 253,
															  1, 253,193,  16,
															  1, 129, 225, 193
															  }; // twiddle multiplication, w_16 in this case





#endif
