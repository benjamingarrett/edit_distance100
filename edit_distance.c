#include "edit_distance.h"

#define FALSE 0
#define TRUE 1

#define PRINT_REFERENCES  

const char * first_pattern_parameter = "--edit_dist_first_pattern";
const char * second_pattern_parameter = "--edit_dist_second_pattern";
const char * pair_of_patterns_parameter = "--edit_dist_pattern_pair";
const char * pattern_reference_threshold_parameter = "--edit_dist_pattern_reference_threshold";

int * X, * Y;
long int nX, nY;

long int pattern_references;
long int cache_reads;
long int cache_writes;
long int cache_misses;
long int cache_hits;
long int pattern_reference_threshold;
long int memo_calls, dist_calls;
long int lru_queue_size;
long int distance;

int64_t levenshtein_distance(long int len_s, long int len_t);

/* PUBLIC */

void initialize_edit_distance(int argc, char **argv) {

  char first_pattern_fname[200], second_pattern_fname[200], double_pattern_fname[200];
  char have_double_pattern = FALSE;
  for(int g=1; g<argc; g++){
    if(strcmp(argv[g], first_pattern_parameter) == 0) {
      if(g+1 < argc){
        strcpy(first_pattern_fname, &argv[++g][0]);
      }
    }
    if(strcmp(argv[g], second_pattern_parameter) == 0) {
      if(g+1 < argc){
        strcpy(second_pattern_fname, &argv[++g][0]);
      }
    }
    if(strcmp(argv[g], pair_of_patterns_parameter) == 0){
      if(g+1 < argc){
        strcpy(double_pattern_fname, &argv[++g][0]);
        have_double_pattern = TRUE;
      }
    }
    if(strcmp(argv[g], pattern_reference_threshold_parameter) == 0){
      if(g+1 < argc){
        pattern_reference_threshold = (uint64_t) atoi(argv[++g]);
      }
    }
  }
  FILE * fp;
  int n;
  if(have_double_pattern == FALSE){
//    printf("reading %s\n", first_pattern_fname);
    if((fp = fopen(first_pattern_fname, "r")) == NULL){
      fprintf(stderr, "Could not open %s\n", first_pattern_fname);
      exit(1);
    }
    n = fscanf(fp, "%ld\n", &nX);
    X = calloc(nX, sizeof(int));
    for(int g=0; g<nX; g++){
      n = fscanf(fp, "%d", &X[g]);
//      printf(">%d<", X[g]);
    }
//    printf("\n");
    fclose(fp);
//    printf("reading %s\n", second_pattern_fname);
    if((fp = fopen(second_pattern_fname, "r"))==NULL){
      fprintf(stderr, "Could not open %s\n", second_pattern_fname);
      exit(1);
    }
    n = fscanf(fp, "%ld\n", &nY);
    Y = calloc(nY, sizeof(int));
    for(int g=0; g<nY; g++){
      n = fscanf(fp, "%d", &Y[g]);
//      printf(">%c<", Y[g]);
    }
//    printf("\n");
    fclose(fp);
  } else {
//    printf("reading %s\n", double_pattern_fname);
    fp = fopen(double_pattern_fname, "r");
    if (fp == NULL) {
      printf("Error opening file: %s\n", double_pattern_fname);
      exit(EXIT_FAILURE);
    }
    n = fscanf(fp, "%ld\n", &nX);
    X = calloc(nX, sizeof(int));
//    printf("reading %ld symbols\n", nX);
    for (long int g = 0; g < nX; g++) {
      n = fscanf(fp, "%d", &X[g]);
//      printf(">%d<", X[g]);
    }
//    printf("\n");
    n = fscanf(fp, "\n%ld\n", &nY);
    Y = calloc(nY, sizeof(int));
//    printf("reading %ld symbols\n", nY);
    for (long int g = 0; g < nY; g++) {
      n = fscanf(fp, "%d", &Y[g]);
//      printf(">%d<", Y[g]);
    }
//    printf("\n");
    fclose(fp);
  }
  pattern_references = 0;
  cache_reads = 0;
  cache_writes = 0;
  memo_calls = dist_calls = cache_misses = cache_hits = 0;
}

void reset_edit_distance(){
  cache_misses = cache_hits = 0;
}

int32_t get_cache_misses_edit_distance(){
  return cache_misses;
}

int32_t get_cache_hits_edit_distance(){
  return cache_hits;
}

void solve_edit_distance(){
  distance = levenshtein_distance(nX, nY);
}

void solve_edit_distancei_OLD(int argc, char **argv) {

  initialize_long_int_cache(argc, argv);
  initialize_edit_distance(argc, argv);
  distance = levenshtein_distance(nX, nY);
  printf("%ld %ld %ld %ld\n", distance, lru_queue_size, dist_calls, memo_calls);
}

/* PRIVATE */

uint64_t generate_key(int16_t i, int16_t j) {
//  uint64_t key = (((int16_t) i) << 16) | (((int16_t) j) & 0xffffffffu);
//  printf("key of %d and %d --> %ld %x\n", i,j,key,key);
  return (((int16_t) i) << 16) | (((int16_t) j) & 0xffffffffu);
}

int64_t memo_levenshtein_distance(long int len_s, long int len_t);

int64_t levenshtein_distance(long int len_s, long int len_t) {

  int64_t * val, len;
  uint64_t * key;

  dist_calls++;
  key = calloc(1, sizeof (int64_t));
  *key = generate_key(len_s, len_t);
  val = cache_read_long_int(key);
  cache_reads++;
  if (val == NULL) {
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


