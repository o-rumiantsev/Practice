#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tab(int n) {
  char *spaces = (char *)malloc(n * sizeof(char));
  for (int i = 0; i < n; ++i) spaces[i] = ' ';
  return spaces;
}

const char* brainfuck_to_c (const char* source) {
  int source_length = strlen(source);

  int operators = 0;
  int i = 0;
  while (i != source_length) {
    if ((source[i] != source[i + 1]) ||
        (source[i] == '[' && source[i + 1] == '[') ||
        (source[i] == ']' && source[i + 1] == ']')) operators++;
    ++i;
  }

  char **translated = (char **)malloc(operators * sizeof(char *));

  i = 0;
  int k = 0;
  int o = 0;
  int count = 0;
  int tabs = 0;
  while (o != operators && i < source_length) {
    if (source[i] == '+' ||
        source[i] == '-' ||
        source[i] == '>' ||
        source[i] == '<'
    ) ++count;

    if (source[i] != source[i + 1]) {
      if (source[i] == '+') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%s*p += %d;\\n", tab(tabs), count);
        translated[k++] = line;
        count = 0;
        ++o;
      } else if (source[i] == '-') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%s*p -= %d;\\n", tab(tabs), count);
        translated[k++] = line;
        count = 0;
        ++o;
      } else if (source[i] == '>') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%sp += %d;\\n", tab(tabs), count);
        translated[k++] = line;
        count = 0;
        ++o;
      } else if (source[i] == '<') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%sp -= %d;\\n", tab(tabs), count);
        translated[k++] = line;
        count = 0;
        ++o;
      } else if (source[i] == '[') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%sif (*p) do {\\n", tab(tabs));
        translated[k++] = line;
        count = 0;
        tabs += 2;
        ++o;
      } else if (source[i] == ']') {
        char *line = (char *)malloc(80 * sizeof(char));
        tabs -= 2;
        sprintf(line, "%s} while (*p);\\n", tab(tabs));
        translated[k++] = line;
        count = 0;
        ++o;
      } else if (source[i] == '.') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%sputchar(*p);\\n", tab(tabs));
        translated[k++] = line;
        count = 0;
        ++o;
      } else if (source[i] == ',') {
        char *line = (char *)malloc(80 * sizeof(char));
        sprintf(line, "%s*p = getchar();\\n", tab(tabs));
        translated[k++] = line;
        count = 0;
        ++o;
      }
    }
    ++i;
  }

  for (int i = 0; i < operators; ++i) {
    printf("%s\n", translated[i]);
  }

  printf("%d\n", operators);
  return source;
}

int main() {
  const char *output = brainfuck_to_c("+++++[>++++.<-]");
  printf("%s\n", output);
}
