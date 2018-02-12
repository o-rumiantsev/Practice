#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *read_file(char *);
int *get_even_only(int *, int);
int *get_odd_only(int *, int);
void sort_even(int *);
void sort_odd(int *);
void write_file(int *);

int g_even_length = 0;
int g_odd_length = 0;
int g_instance_length = 0;

int main() {
  char input[256];
  fgets(input, 256, stdin);
  input[strlen(input) - 1] = '\0';

  int *instance = read_file(input);

  int *even = get_even_only(instance, g_instance_length);
  int *odd = get_odd_only(instance, g_instance_length);

  free(instance);

  int *sorted = (int *)malloc(sizeof(int) * g_instance_length);
  int index = 0;

  for (int i = 0; i < g_even_length; ++i) sorted[index++] = even[i];
  for (int i = 0; i < g_odd_length; ++i) sorted[index++] = odd[i];

  write_file(sorted);

  free(sorted);
  return 0;
};


// File I/O
//
//
int *read_file(char *input_path) {
  FILE *input;
  int c;
  int i = 0;
  char text[100000];

  input_path[strlen(input_path)] = '\0';
  input = fopen(input_path, "r");

  if (!input) {
    perror(input_path);
    exit(1);
  }

  while ((c = fgetc(input)) != '\n') {
    text[i++] = c;
  }

  text[i] = '\0';
  g_instance_length = atoi(text);
  memset(text, '\0', i);
  i = 0;

  int *instance = (int *)malloc(sizeof(int) * g_instance_length);
  int k = 0;

  do {
    c = fgetc(input);
    if (c != '\n' && c != EOF) text[i++] = c;
    else {
      text[i] = '\0';
      if (strlen(text) > 0) instance[k++] = atoi(text);
      memset(text, '\0', i);
      i = 0;
    }
  } while (c != EOF);
  fclose(input);
  return instance;
};


void write_file(int *instance) {
  FILE *output;
  char output_path[80];
  sprintf(output_path, "output_%d.txt", g_instance_length);

  output = fopen(output_path, "w");

  for (int i = 0; i < g_instance_length; ++i) {
    if (i < g_instance_length - 1) fprintf(output, "%d\n", instance[i]);
    else fprintf(output, "%d", instance[i]);
  }

  fclose(output);
};


// Get even and odd numbers
// from instance
//
int *get_even_only(int *arr, int length) {
  int *even = (int*)malloc(sizeof(int) * length);
  int index = 0;

  for (int i = 0; i < length; ++i) {
    if (arr[i] % 2 == 0) even[index++] = arr[i];
  };

  g_even_length = index;
  sort_even(even);
  return even;
};

int *get_odd_only(int *arr, int length) {
  int *odd = (int *)malloc(sizeof(int) * length);
  int index = 0;

  for (int i = 0; i < length; ++i) {
    if (arr[i] % 2 == 1) odd[index++] = arr[i];
  };

  g_odd_length = index;
  sort_odd(odd);
  return odd;
};


// Sort
//
//
void swap(int *arr, int i, int j) {
  int k = arr[i];
  arr[i] = arr[j];
  arr[j] = k;
};

void sort_even(int *even) {
  for (int i = 1; i < g_even_length; ++i) {
    for (int j = i; j > 0; --j) {
      if (even[j] < even[j - 1]) swap(even, j, j - 1);
      else break;
    }
  }
};

void sort_odd(int *odd) {
  for (int i = 1; i < g_odd_length; ++i) {
    for (int j = i; j > 0; --j) {
      if (odd[j] > odd[j - 1]) swap(odd, j, j - 1);
      else break;
    }
  }
};
