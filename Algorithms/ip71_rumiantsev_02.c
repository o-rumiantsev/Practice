#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int g_film_count;

int **read_from_file(char *);
int *get_arr(int **, int, int, int);
int *find_inversions(int *, int);



int main(int argc, char **argv) {
  int **source = read_from_file(argv[1]);

  for (int i = 1; i <= 10; ++i) {
    for (int j = 0; j < g_film_count; ++j) printf("%d ", source[i][j]);
    printf("\n");
  }

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

  int ucount = atoi(split[0]);
  g_film_count = atoi(split[1]);
  memset(str, '\0', 80);

  int **source = (int **)calloc(ucount + 1, sizeof(int *));

  for (int i = 0; i < ucount; ++i) {
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

  return source;
}


//
//
//
int *get_arr(int **source, int len, int u1, int u2) {
  int *res = (int *)calloc(g_film_count, sizeof(int));
  int *arr1 = source[u1];
  int *arr2 = source[u2];

  for (int i = 1; i <= g_film_count; ++i) {
    int j = 0;
    while (arr1[j] != i) ++j;
    res[i - 1] = arr2[j];
  }

  for (int i = 0; i < g_film_count; ++i) printf("%d\n", res[i]);

  return res;
}


//
// int *find_inversions(int *arr, int len) {
//
// }
