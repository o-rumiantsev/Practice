#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char *arr, int i, int j) {
  char k = arr[i];
  arr[i] = arr[j];
  arr[j] = k;
};

void move_to_end(char *source, int i) {
  int source_length = strlen(source);
  while (i < source_length) {
    swap(source, i, i + 1);
    ++i;
  }
}

int count_unpaired(const char *source) {
  int count = 0;
  int source_length = strlen(source);

  for (int i = 0; i < source_length; ++i) {
    if (source[i] == '[') ++count;
    else if (source[i] == ']') --count;
  }

  return count;
}

char *optimize(const char *source) {
  int source_length = strlen(source);
  char *optimized = (char *)malloc(source_length * sizeof(char *));
  strcpy(optimized, source);

  int optimization_index = 0;
  for (int i = 0; i < source_length; ++i) {
    if (
      optimized[i] != '+' &&
      optimized[i] != '-' &&
      optimized[i] != '>' &&
      optimized[i] != '<' &&
      optimized[i] != '[' &&
      optimized[i] != ']' &&
      optimized[i] != '.' &&
      optimized[i] != ','
    ) {
      optimized[i] = ' ';
      ++optimization_index;
    }
  }

  int opt = 0;
  while (!opt) {
    for (int i = 0; i < source_length; ++i) {
      opt = 1;

      if (
        (optimized[i] == '+' && optimized[i + 1] == '-') ||
        (optimized[i] == '-' && optimized[i + 1] == '+') ||
        (optimized[i] == '<' && optimized[i + 1] == '>') ||
        (optimized[i] == '>' && optimized[i + 1] == '<') ||
        (optimized[i] == '[' && optimized[i + 1] == ']')
      ) {
        optimized[i] = ' ';
        optimized[i + 1] = ' ';
        optimization_index += 2;
        opt = 0;
      }

    }
  }

  for (int i = source_length; i > 0; --i) {
    if (optimized[i] == ' ') move_to_end(optimized, i);
  }

  if (optimization_index) {
    int source_optimized_length = source_length - optimization_index;
    char *source_optimized = (char *)malloc(
      source_optimized_length * sizeof(char)
    );
    strncpy(source_optimized, optimized, source_optimized_length);
    free(optimized);
    return source_optimized;
  }

  return optimized;
}

const char *brainfuck_to_c(const char *source_not_optimized) {
  printf("START: %s\n", source_not_optimized);
  int source_length = strlen(source_not_optimized);
  char *source = optimize(source_not_optimized);
  int unpaired = count_unpaired(source_not_optimized);

  if (unpaired) return "Error!";

  int operators = 0;
  int i = 0;
  while (i != source_length) {
    if (
      (source[i] != source[i + 1]) ||
      (source[i] == '[' && source[i + 1] == '[') ||
      (source[i] == ']' && source[i + 1] == ']')
    ) operators++;
    ++i;
  }

  i = 0;
  int o = 0;
  int count = 0;
  int tabs = 0;

  char *result = (char *)malloc(80 * operators * sizeof(char));
  while (o != operators && i < source_length) {
    if (source[i] == '+' ||
        source[i] == '-' ||
        source[i] == '>' ||
        source[i] == '<'
    ) ++count;

    if (source[i] != source[i + 1]) {
      if (source[i] == ']') tabs -=2;

      char *ident = (char *)malloc(tabs * sizeof(char));
      memset(ident, ' ', tabs);
      if (source[i] == '+') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%s*p += %d;\n", ident, count);
        strcat(result, line);
        free(line);
        count = 0;
        ++o;
      } else if (source[i] == '-') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%s*p -= %d;\n", ident, count);
        strcat(result, line);
        free(line);
        count = 0;
        ++o;
      } else if (source[i] == '>') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%sp += %d;\n", ident, count);
        strcat(result, line);
        free(line);
        count = 0;
        ++o;
      } else if (source[i] == '<') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%sp -= %d;\n", ident, count);
        strcat(result, line);
        free(line);
        count = 0;
        ++o;
      } else if (source[i] == '[') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%sif (*p) do {\n", ident);
        tabs += 2;
        strcat(result, line);
        free(line);
        count = 0;
        ++o;
      } else if (source[i] == ']') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%s} while (*p);\n", ident);
        strcat(result, line);
        free(line);
        count = 0;
        ++o;
      } else if (source[i] == '.') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%sputchar(*p);\n", ident);
        strcat(result, line);
        free(line);
        count = 0;
        ++o;
      } else if (source[i] == ',') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%s*p = getchar();\n", ident);
        strcat(result, line);
        free(line);
        count = 0;
        ++o;
      }

      free(ident);
      printf("%s\n", ident);
    }
    ++i;
  }

  free(source);
  return result;
}

int main() {
  // brainfuck_to_c("++++");
  // brainfuck_to_c("----");
  // brainfuck_to_c(">>>>");
  // brainfuck_to_c("<<<<");
  // brainfuck_to_c(".");
  // brainfuck_to_c(",");
  // brainfuck_to_c("[[[]]");
  // brainfuck_to_c("[][]");
  brainfuck_to_c("[.]");
  const char *output = brainfuck_to_c(".,.<>>,+.[><>--]+,-[.<,[]>+.><>-]>>");
  const char *expected = "putchar(*p);\n*p = getchar();\nputchar(*p);\np += 1;\n*p = getchar();\n*p += 1;\nputchar(*p);\nif (*p) do {\n  p += 1;\n  *p -= 2;\n} while (*p);\n*p += 1;\n*p = getchar();\n*p -= 1;\nif (*p) do {\n  putchar(*p);\n  p -= 1;\n  *p = getchar();\n  p += 1;\n  *p += 1;\n  putchar(*p);\n  p += 1;\n  *p -= 1;\n} while (*p);\np += 2;\n";
  printf("Expected:\n%s\n", expected);
  printf("Actual:\n%s\n", output);
  printf("%d\n", !strcmp(output, expected));
}
