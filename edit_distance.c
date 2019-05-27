#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../memoization/memo_long_int.h"
#include "edit_distance.h"

#define PRINT_REFERENCES  

const char * edit_dist_instance_fname_parameter = "--edit_dist_instance_fname";

int64_t * X, * Y;
int32_t nX, nY;
int64_t memo_calls, dist_calls, cache_misses, prev_cache_misses;
long int distance;
long int pattern_references;
long int cache_reads;
long int cache_writes;
long int cache_misses;
long int pattern_reference_threshold;
long int memo_calls, dist_calls;
long int lru_queue_size;

int64_t levenshtein_distance(long int len_s, long int len_t);

char (*check_preemptive_halt_edit_dist_)();
char check_preemptive_halt_edit_dist_activated();
char check_preemptive_halt_edit_dist_deactivated();

/* PUBLIC */

void initialize_edit_distance(int argc, char **argv){
  //printf("initialize edit distance\n");
  char instance_fname[200];
  for(int g=1; g<argc; g++){
    if(strcmp(argv[g], edit_dist_instance_fname_parameter) == 0){
      if(g+1 < argc){
        strcpy(instance_fname, &argv[++g][0]);
      }
    }
  }
  check_preemptive_halt_edit_dist_ = check_preemptive_halt_edit_dist_deactivated;
  FILE * fp;
  int n;
  if((fp = fopen(instance_fname, "r"))==NULL){
    fprintf(stderr, "Error opening instance file:-->%s<--\n", instance_fname);
    exit(EXIT_FAILURE);
  }
  n = fscanf(fp, "%d\n", &nX);
  X = calloc(nX, sizeof(int64_t));
  for(int64_t g = 0; g < nX; g++){
    n = fscanf(fp, "%ld", &X[g]);
    //printf(">%ld<", X[g]);
  }
  n = fscanf(fp, "%d\n", &nY);
  Y = calloc(nY, sizeof(int64_t));
  for(int64_t g = 0; g < nY; g++){
    n = fscanf(fp, "%ld", &Y[g]);
    //printf(">%ld<", Y[g]);
  }
  //printf("\n");
  fclose(fp);
  pattern_references = 0;
  cache_reads = 0;
  cache_writes = 0;
  memo_calls = dist_calls = cache_misses = prev_cache_misses = 0;
}

void set_cache_miss_threshold_edit_distance(int64_t t){
  prev_cache_misses = t;
}

void set_preemptive_halt_edit_distance(int p){
  check_preemptive_halt_edit_dist_ = p ? check_preemptive_halt_edit_dist_activated : check_preemptive_halt_edit_dist_deactivated;
}

void reset_edit_distance(long int p){
  memo_calls = dist_calls = cache_misses = 0;
}

long int get_cache_misses_edit_distance(){
  return cache_misses;
}

void solve_edit_distance(){
  //printf("solve edit distance\n");
  distance = levenshtein_distance(nX, nY);
}

void solve_edit_distancei_standalone(int argc, char **argv) {
  initialize_long_int_cache(argc, argv);
  initialize_edit_distance(argc, argv);
  distance = levenshtein_distance(nX, nY);
  printf("%ld %ld %ld %ld\n", distance, lru_queue_size, dist_calls, memo_calls);
}

/* PRIVATE */

char check_preemptive_halt_edit_dist_deactivated(){
  return 0;
}

char check_preemptive_halt_edit_dist_activated(){
  return (cache_misses > prev_cache_misses) ? 1 : 0;
}

uint64_t generate_key_edit_distance(int32_t i, int32_t j) {
  return (((int64_t) i) << 32) | (((int64_t) j) & 0xffffffffu);
}

int64_t memo_levenshtein_distance(long int len_s, long int len_t);

int64_t levenshtein_distance(long int len_s, long int len_t) {
  int64_t * val, len;
  uint64_t * key;
  if(check_preemptive_halt_edit_dist_()){
    return 0;
  }
  dist_calls++;
  key = calloc(1, sizeof (int64_t));
  *key = generate_key_edit_distance(len_s, len_t);
  val = cache_read_long_int(key);
  cache_reads++;
  if(val == NULL){
    len = memo_levenshtein_distance(len_s, len_t);
    val = &len;
    cache_write_long_int(key, val);
    cache_writes++;
  }
  len = *val;
  return len;
}

int X_(long int k){
  pattern_references++;
  //  if(pattern_reference_threshold < pattern_references){
  //    printf("pattern references exceeded threshold\n");
  //    exit(0);
  //  }
  return X[k];
}

int Y_(long int k){
  pattern_references++;
  //  if(pattern_reference_threshold < pattern_references){
  //    printf("pattern references exceeded threshold\n");
  //    exit(0);
  //  }
  return Y[k];
}

int64_t memo_levenshtein_distance(long int i, long int j) {
  memo_calls++;
  //  printf("%ld %ld\n", i,j);
  if (i == 0) return j;
  if (j == 0) return i;
  int64_t cost = (X_(i - 1) == Y_(j - 1)) ? 0 : 1;
  int64_t c1 = levenshtein_distance(i - 1, j) + 1;
  int64_t c2 = levenshtein_distance(i, j - 1) + 1;
  int64_t c3 = levenshtein_distance(i - 1, j - 1) + cost;
  int64_t min = (c1 < c2) ? c1 : c2;
  return (c3 < min) ? c3 : min;
}


