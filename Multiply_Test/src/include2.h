
#ifndef __INCLUDES_H__
#define __INCLUDES_H__

int32 const chess_storage(%chess_alignof(v4int32)) x[16] =   {  1,  2,  3,  4,
																5,  6,  7,  8,
																9, 10, 11, 12,
															   13, 14, 15, 16
																};

int32 const chess_storage(%chess_alignof(v4int32)) tw[8] =   {1, 16, -1, -16,
										                      10000, 1000000, 100, 10};


/*

int32 const chess_storage(%chess_alignof(v4int32)) tww[16] = {1,  1,   1,   1,
		                                                      1, 32, 253, 129,
															  1, 253, 16, 193,
															  1, 129, 193, 225
															  };

*/







int32 const chess_storage(%chess_alignof(v4int32)) tww[16] = {1,  1,   1,   1,
		                                                      1, 32, 129, 253,
															  1, 253,193,  16,
															  1, 129, 225, 193
															  };




#endif
