
#ifndef __INCLUDES_H__
#define __INCLUDES_H__

int32 const chess_storage(%chess_alignof(v4int32)) x[16] =   {  0,	4,	8,	12,
		16,	20,	24,	28,
		32,	36,	40,	44,
		48,	52,	56,	60
																};

int32 const chess_storage(%chess_alignof(v4int32)) tw[8] =   {1, 5756, -1, -5756,
										                      10000, 1000000, 100, 10};


/*

int32 const chess_storage(%chess_alignof(v4int32)) tww[16] = {1,  1,   1,   1,
		                                                      1, 32, 253, 129,
															  1, 253, 16, 193,
															  1, 129, 193, 225
															  };

*/







int32 const chess_storage(%chess_alignof(v4int32)) tww[16] = {1,	1,	1,	1,
		1,	2132,	2784,	5953,
		1,	5953,	527,	5756,
		1,	2784,	97,	527

															  };




#endif
