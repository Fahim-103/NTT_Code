#include <stdio.h>
//#include "ntt_calc.h"
#include "ntt_fwd_inv.h"

int main() {


    static test_case_t tests = {.m = 10, .q = 12289, .w = 11, .w_inv = 5586, .n_inv.op = 12277};
    //static test_case_t tests = {.m = 10, .q = 12289, .w = 10302, .w_inv = 8974, .n_inv.op = 12277};
   
    _init_test(&tests);  //test_case parameter initiation

    const test_case_t *t;
    t = &tests;
    /**************************************************************************/

    ////prepare two input vector
    int s = t ->n;
    uint64_t a_in[s]; uint64_t * a_i = a_in;
    uint64_t a[s];  // a for total calculation
    for (int i = 0; i<(s); i++){
        a_in[i] = i;
        a[i] = i;
    }

    printf("Printing input\n");

    for (int i = 0; i < t->n; i++) {
        printf("%llu ", a_in[i]);
    }
    printf("\n");
    //// generate Forward NTT -- a
    fwd_ntt_ref_harvey(a, t->n, t->q, t->w_powers, t->w_powers_con, t->m);

    printf("Printing Forward NTT of a bit_rev\n");
    for (int i = 0; i < t->n; i++) {
        printf("%llu ", a[i]);
    }
    printf("\n");

    //generate Inverse NTT
    inv_ntt_ref_harvey(a, t->n, t->q, t->n_inv, WORD_SIZE, t->w_inv_powers,
                       t->w_inv_powers_con, t->m);


    //////////////////////////////////////////////////////////

    printf("Printing Reverse NTT of a bit_rev\n");

    for (int i = 0; i < t->n; i++) {
        printf("%llu ", a[i]);
    }



    ////// stage0  1024 -> 256 times 4-elem FFT   in the block of 1024 tw[1024] 256-256-256-256 ////////////////////
    uint64_t p = t->q;
    uint64_t temp1[1024];
    uint64_t temp2[1024];

    uint64_t s0[4];
    uint64_t w_powers_n0[4];
    uint64_t w_powers_con_n0[4];

    w_powers_n0[0] = t->w_powers[0];
    w_powers_n0[1] = t->w_powers[256];
    w_powers_n0[2] = t->w_powers[512];
    w_powers_n0[3] = t->w_powers[768];

    w_powers_con_n0[0] =  t->w_powers_con[0];
    w_powers_con_n0[1] =  t->w_powers_con[256];
    w_powers_con_n0[2] =  t->w_powers_con[512];
    w_powers_con_n0[3] =  t->w_powers_con[768];

    ///////////////// stage0  1024 -> 256 //////////////////

    uint64_t tw0[1024];
    for (int i = 0; i < 256; i++){

        tw0[i]     = t->w_powers[0*i];
        tw0[i+256] = t->w_powers[1*i];
        tw0[i+512] = t->w_powers[2*i];
        tw0[i+768] = t->w_powers[3*i];
    }

    //printf("Printing tw_0\n");

    // for (int i = 0; i < t->n; i++) {
    // printf("%llu, ", tw0[i]);
    //}

    // printf("\n");


    for (int i =0; i < (1024/4) ; i++){

        s0[0] = a_in[0+i];
        s0[1] = a_in[256+i];
        s0[2] = a_in[512+i];
        s0[3] = a_in[768+i];

        fwd_ntt_ref_harvey(s0, 4, t->q, w_powers_n0, w_powers_con_n0, 2);


        temp1[0+i]   = (s0[0] * tw0[i]) % p;
        temp1[256+i] = (s0[1] * tw0[256 + i] ) % p;
        temp1[512+i] = (s0[2] * tw0[512 + i]) % p;
        temp1[768+i] = (s0[3] * tw0[768 + i]) % p;

    }




    /*printf("\nstage0\n");
    for (int i =0; i < 1024; i++){

        printf("%lu ", temp1[i]);
    }*/

    ////////////////////////////// stage1 256 -> 64 block //////////////////////

    uint64_t tw1[256];
    for (int i = 0; i < 64; i++){

        tw1[  0 + i] = t->w_powers[0*i];
        tw1[ 64 + i] = t->w_powers[1*i*4];
        tw1[128 + i] = t->w_powers[2*i*4];
        tw1[192 + i] = t->w_powers[3*i*4];



    }

    for (int i =0; i < 4; i++){
    //int i = 2;
        for (int j =0; j<(256/4); j++ ){
            s0[0] = temp1[0+j+i*256];
            s0[1] = temp1[64+j+i*256];
            s0[2] = temp1[128+j+i*256];
            s0[3] = temp1[192+j+i*256];

            fwd_ntt_ref_harvey(s0, 4, t->q, w_powers_n0, w_powers_con_n0, 2);

            temp1[0+j+i*256]   = (s0[0] * tw1[  0+j]) % p;
            temp1[64+j+i*256]  = (s0[1] * tw1[ 64+j]) % p;
            temp1[128+j+i*256] = (s0[2] * tw1[128+j]) % p;
            temp1[192+j+i*256] = (s0[3] * tw1[192+j]) % p;
        }
    }


/*

    uint64_t w_powers_na[64];
    uint64_t w_powers_con_na[64];
    uint64_t temp2a[64];

    for (int i = 0; i < 64; i++){

        w_powers_na[i] = t->w_powers[4*4*i];
        w_powers_con_na[i] =  t->w_powers_con[4*4*i];
        temp2a[i] = temp1[768+128+i];
    }


    fwd_ntt_ref_harvey(temp2a, 64, t->q, w_powers_na, w_powers_con_na, 6);
    //fwd_ntt_ref_harvey(temp2b, 256, t->q, w_powers_na, w_powers_con_na, 8);
   // fwd_ntt_ref_harvey(temp2c, 256, t->q, w_powers_na, w_powers_con_na, 8);
    //fwd_ntt_ref_harvey(temp2d, 256, t->q, w_powers_na, w_powers_con_na, 8);

    printf("\ntem2abcd\n");
    for (int i = 0; i < 64; i++){

        printf("%llu ", temp2a[i]);
    }

*/

    ////////////////////////////// stage2 64 -> 16 block //////////////////////

    uint64_t tw2[64];
    for (int i = 0; i < 16; i++){

        tw2[ 0 + i] = t->w_powers[0*i];
        tw2[16 + i] = t->w_powers[1*i*4*4];
        tw2[32 + i] = t->w_powers[2*i*4*4];
        tw2[48 + i] = t->w_powers[3*i*4*4];



    }

    for (int i =0; i < 4; i++){
        for (int j =0; j < 4; j++){
            for (int k =0; k<(64/4); k++ ){
                s0[0] = temp1[ 0 + k + j*64 + i*256];
                s0[1] = temp1[16 + k + j*64 + i*256];
                s0[2] = temp1[32 + k + j*64 + i*256];
                s0[3] = temp1[48 + k + j*64 + i*256];

                fwd_ntt_ref_harvey(s0, 4, t->q, w_powers_n0, w_powers_con_n0, 2);

                temp1[ 0 + k + j*64 + i*256] = (s0[0] * tw2[ 0 + k]) % p;
                temp1[16 + k + j*64 + i*256] = (s0[1] * tw2[16 + k]) % p;
                temp1[32 + k + j*64 + i*256] = (s0[2] * tw2[32 + k]) % p;
                temp1[48 + k + j*64 + i*256] = (s0[3] * tw2[48 + k]) % p;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////

/*

    uint64_t w_powers_na[16];
    uint64_t w_powers_con_na[16];
    uint64_t temp2a[16];

    for (int i = 0; i < 16; i++){

        w_powers_na[i]     = t->w_powers[4*4*4*i];
        w_powers_con_na[i] = t->w_powers_con[4*4*4*i];
        temp2a[i] = temp1[768+192+48+i];
    }


    fwd_ntt_ref_harvey(temp2a, 16, t->q, w_powers_na, w_powers_con_na, 4);
    //fwd_ntt_ref_harvey(temp2b, 256, t->q, w_powers_na, w_powers_con_na, 8);
    // fwd_ntt_ref_harvey(temp2c, 256, t->q, w_powers_na, w_powers_con_na, 8);
    //fwd_ntt_ref_harvey(temp2d, 256, t->q, w_powers_na, w_powers_con_na, 8);

    printf("\ntem2abcd\n");
    for (int i = 0; i < 64/4; i++){

        printf("%lu ", temp2a[i]);
    }

*/


    return 0;
}