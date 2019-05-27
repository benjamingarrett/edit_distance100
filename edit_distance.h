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
  void initialize_edit_distance(int argc, char **argv);
  void set_cache_miss_threshold_edit_distance(int64_t t);
  void set_preemptive_halt_edit_distance(int p);
  void reset_edit_distance(long int p);
  long int get_cache_misses_edit_distance();
  void solve_edit_distance();
  void solve_edit_distance_standalone(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* EDIT_DISTANCE_H */

