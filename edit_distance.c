#include "edit_distance.h"

char * X, * Y;

void initialize_edit_distance(int argc, char **argv) {

  // parse options for edit_distance, eg. input files, output destination, etc.
  initialize_long_int_cache(argc, argv);
}

int64_t generate_key(int16_t i, int16_t j) {

  return (((int16_t) i) << 16) | (((int16_t) j) & 0xffffffffu);
}

int64_t memo_levenshtein_distance(const char *s, int32_t len_s, const char *t, int32_t len_t);

int64_t levenshtein_distance(const char *s, int32_t len_s, const char *t, int32_t len_t) {

  int64_t * val, * key, len;

  key = calloc(1, sizeof (int64_t));
  *key = generate_key(len_s, len_t);
  val = cache_read_long_int(key);
  if (val == NULL) {
    len = memo_levenshtein_distance(s, len_s, t, len_t);
    val = &len;
    cache_write_long_int(key, val);
  }
  len = *val;
  return len;
}

int64_t memo_levenshtein_distance(const char *s, int32_t len_s, const char *t, int32_t len_t) {

  int cost, c1, c2, c3, min;

  if (len_s == 0)
    return len_t;
  if (len_t == 0)
    return len_s;
  if (s[len_s - 1] == t[len_t - 1]) {
    cost = 0;
  } else {
    cost = 1;
  }
  c1 = levenshtein_distance(s, len_s - 1, t, len_t) + 1;
  c2 = levenshtein_distance(s, len_s, t, len_t - 1) + 1;
  c3 = levenshtein_distance(s, len_s - 1, t, len_t - 1) + cost;
  min = (c1 < c2) ? c1 : c2;
  min = (c3 < min) ? c3 : min;
  return min;
}

void solve_edit_distance(int argc, char **argv) {

  const char * word1;
  const char * word2;
  int32_t len1;
  int32_t len2;
  int64_t d;

  initialize_edit_distance(argc, argv);
  word1 = "pieces";
  word2 = "paces";
  len1 = strlen(word1);
  len2 = strlen(word2);
  d = levenshtein_distance(word1, len1, word2, len2);
  printf("The edit distance between %s and %s is %ld.\n",
          word1, word2, d);
}

/*
// len_s and len_t are the number of characters in string s and t respectively
int LevenshteinDistance(const char *s, int len_s, const char *t, int len_t)
{ 
  int cost;

  /* base case: empty strings * /
  if (len_s == 0) return len_t;
  if (len_t == 0) return len_s;

  /* test if last characters of the strings match * /
  if (s[len_s-1] == t[len_t-1])
      cost = 0;
  else
      cost = 1;

  /* return minimum of delete char from s, delete char from t, and delete char from both * /
  return minimum(LevenshteinDistance(s, len_s - 1, t, len_t    ) + 1,
                 LevenshteinDistance(s, len_s    , t, len_t - 1) + 1,
                 LevenshteinDistance(s, len_s - 1, t, len_t - 1) + cost);
}
 */