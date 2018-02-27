#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define INT_MAX 2147483647

int g_user;
int g_film_count;
int g_ucount;

int **read_from_file(char *);
int *get_arr(int *, int *);
int count_inversions(int *, int, int);
char **strsplit(char *, const char *);
void sort_and_writefile(int **);

int main(int argc, char **argv) {
  int **source = read_from_file(argv[1]);
  g_user = atoi(argv[2]);
  int **result = (int **)calloc(g_ucount, sizeof(int *));

  int k = 0;
  for (int i = 1; i <= g_ucount; ++i) {
    if (i != g_user) {
      int *arr = get_arr(source[g_user], source[i]);
      int invs = count_inversions(arr, 0, g_film_count - 1);
      result[k] = (int *)calloc(2, sizeof(int));
      result[k][0] = i;
      result[k][1] = invs;
      ++k;
    }
  }

  sort_and_writefile(result);

  return 0;
}


// Split string by appropriate delimiter
//
//
char **strsplit(char *source, const char *delimiter) {
  char **result = (char **)calloc(80, sizeof(char *));
  char *split = (char *)calloc(80, sizeof(char));

  int i = 0;
  int j = 0;
  int k = 0;
  while (source[i] != '\n' && source[i] != '\0') {
    if (source[i] != ' ') {
      split[k++] = source[i++];
    } else {
      result[j] = (char *)calloc(strlen(split), sizeof(char *));
      strcpy(result[j++], split);
      memset(split, '\0', 80);
      k = 0;
      ++i;
    }
  }
  result[j] = (char *)calloc(strlen(split), sizeof(char *));
  strcpy(result[j++], split);
  free(split);

  return result;
}


// Get matrix of ints from file
//
//
int **read_from_file(char *src_file) {
  FILE *input = fopen(src_file, "r");

  if (!input) {
    perror("No such file in directory\n");
    exit(1);
  }

  char *str = (char *)calloc(80, sizeof(char));
  fgets(str, 80, input);

  char **split = strsplit(str, " ");

  g_ucount = atoi(split[0]);
  g_film_count = atoi(split[1]);
  memset(str, '\0', 80);

  int **source = (int **)calloc(g_ucount + 1, sizeof(int *));

  for (int i = 0; i < g_ucount; ++i) {
    fgets(str, 80, input);
    split = strsplit(str, " ");
    memset(str, '\0', 80);

    int user = atoi(split[0]);
    int *films = (int *)calloc(g_film_count, sizeof(int));
    for (int k = 0; k < g_film_count; ++k) films[k] = atoi(split[k + 1]);
    source[user] = films;
  }

  free(split);
  free(str);
  fclose(input);

  return source;
}


// Merge
//
//
void merge(int **arr, int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;

  int **L = (int **)calloc(n1, sizeof(int *));
  int **R = (int **)calloc(n2, sizeof(int *));

  for (int i = 0; i < n1; ++i) L[i] = arr[p + i];
  for (int i = 0; i < n2; ++i) R[i] = arr[q + i + 1];

  L[n1] = (int *)calloc(2, sizeof(int));
  R[n2] = (int *)calloc(2, sizeof(int));

  L[n1][1] = INT_MAX;
  R[n2][1] = INT_MAX;

  int i = 0;
  int j = 0;
  for (int k = p; k <= r; ++k) {
    if (L[i][1] <= R[j][1]) {
      arr[k] = L[i++];
    } else arr[k] = R[j++];
  }
}


// Merge sort result
//
//
void merge_sort(int **arr, int p, int r) {
  if (p < r) {
    int q = floor((p + r) / 2);
    merge_sort(arr, p, q);
    merge_sort(arr, q + 1, r);
    merge(arr, p, q, r);
  }
}

// Sort result and write it to file
//
//
void sort_and_writefile(int **result) {
  merge_sort(result, 0, g_ucount - 2);

  FILE *output = fopen("ip71_rumiantsev_02_output.txt", "a");

  fprintf(output, "%d\n", g_user);

  for (int i = 0; i < g_ucount - 1; ++i) {
    fprintf(output, "%d %d\n", result[i][0], result[i][1]);
  }

  fclose(output);
}


// Get array to find inversions in it
//
//
int *get_arr(int *arr1, int *arr2) {
  int *res = (int *)calloc(g_film_count, sizeof(int));

  for (int i = 1; i <= g_film_count; ++i) {
    int j = 0;
    while (arr1[j] != i) ++j;
    res[i - 1] = arr2[j];
  }

  return res;
}


// Count inversions from different parts of array
//
//
int count_split_invs(int *arr, int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;

  int *L = (int *)calloc(n1 + 1, sizeof(int));
  int *R = (int *)calloc(n2 + 2, sizeof(int));

  for (int i = p, k = 0; i <= q; ++i) L[k++] = arr[i];
  for (int i = q + 1, k = 0; i <= r; ++i) R[k++] = arr[i];

  L[n1] = INT_MAX;
  R[n2] = INT_MAX;

  int i = 0;
  int j = 0;
  int invs = 0;

  for (int k = p; k <= r; ++k) {
    if (L[i] <= R[j]) arr[k] = L[i++];
    else {
      arr[k] = R[j++];
      invs += n1 - i;
    }
  }

  free(L);
  free(R);
  return invs;
};


// Count inversions in array
//
//
int count_inversions(int *arr, int p, int r) {
  int n = r - p + 1;
  int inversions = 0;
  if (n == 1) return 0;
  else {
    int q = (p + r) / 2;
    int left = count_inversions(arr, p, q);
    int right = count_inversions(arr, q + 1, r);
    int split = count_split_invs(arr, p, q, r);
    inversions = left + right + split;
  }

  return inversions;
}
