#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *read_file(char *);
void sort(int *);
void write_file(int *);

int g_instance_length = 0;

int main() {
  char input[80];
  printf("Enter input file name: ");
  fgets(input, 80, stdin);
  input[strlen(input) - 1] = '\0';

  int *instance = read_file(input);
  sort(instance);
  write_file(instance);

  free(instance);
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
  char output_path[] = "ip71_rumiantsev_output.txt";

  output = fopen(output_path, "w");

  for (int i = 0; i < g_instance_length; ++i) {
    if (i < g_instance_length - 1) fprintf(output, "%d\n", instance[i]);
    else fprintf(output, "%d", instance[i]);
  }

  fclose(output);
  printf("Sorted sucsessfully\n");
};

// Sort
//
//
void swap(int *arr, int i, int j) {
  int k = arr[i];
  arr[i] = arr[j];
  arr[j] = k;
};

void sort(int *instance) {
  for (int i = 1; i < g_instance_length; ++i) {
    if (instance[i] % 2 == 1) {
      for (int j = i; j > 0; --j) {
        if (
          instance[j - 1] % 2 == 0 || instance[j] < instance[j - 1]
        ) break;
        else swap(instance, j, j - 1);
      }
    } else {
      for (int j = i; j > 0; --j) {
        if (
          instance[j - 1] % 2 == 1 || instance[j] < instance[j - 1]
        ) swap(instance, j, j - 1);
        else break;
      }
    }
  }
};
