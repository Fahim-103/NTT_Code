cmake_minimum_required(VERSION 3.27)
project(test_one_v2 C)

set(CMAKE_C_STANDARD 11)

add_executable(test_one_v2 main.c
        ntt_calc.h
        ntt_fwd_inv.h)
