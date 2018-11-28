/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   edit_distance.h
 * Author: benjamin
 *
 * Created on August 14, 2017, 4:52 PM
 */

#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../memoization/memo_long_int.h"
void initialize_edit_distance(int argc, char **argv);
void reset_edit_distance(long int p);
long int get_cache_misses_edit_distance();
long int get_cache_hits_edit_distance();
void solve_edit_distance();
void solve_edit_distance_OLD(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* EDIT_DISTANCE_H */

