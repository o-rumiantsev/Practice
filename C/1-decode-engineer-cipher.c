#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getCol(int, char *, char);
int getRow(int, char **, char);
void offset(int, char *);
char *decode(char *, char*);
char *genKey(char *, char *);
char **genMatrix(char *);

int main() {
  int i = 0;
  int c;
  char encoded[256];
  char secret[256];

  printf("Enter encoded message: ");
  fgets(encoded, 256, stdin);
  printf("Enter secret word: ");
  fgets(secret, 256, stdin);

  char *decoded = decode(secret, encoded);
  printf("Encoded message: %s \n", decoded);

  free(decoded);
  return 0;
};


char *decode(char *secret, char *encoded) {
  char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  char **matrix = genMatrix(alphabet);
  char *key = genKey(secret, encoded);

  int size = strlen(key);
  char *decoded = (char*)malloc(sizeof(char) * size);

  int msize = strlen(alphabet);

  for (int i = 0; i < size; ++i) {
    int row = getRow(msize, matrix, key[i]);
    int col = getCol(msize, matrix[row], encoded[i]);
    decoded[i] = matrix[0][col];
  };

  free(matrix);
  free(key);

  return decoded;
};


char **genMatrix(char *alphabet) {
  int length = strlen(alphabet);

  char **matrix = (char **)malloc(sizeof(char*) * length);

  for (int i = 0; i < length; i++){
    matrix[i] = (char*)malloc(sizeof(char) * length);
    strcpy(matrix[i], alphabet);
    offset(length, alphabet);
  }

  return matrix;
}


void offset(int length, char *alphabet) {
  for (int i = 0; i < length - 1; i++) {
    char c = alphabet[i];
    alphabet[i] = alphabet[i + 1];
    alphabet[i + 1] = c;
  };
};

char *genKey(char *secret, char *encoded) {
  int k = 0;
  int size = strlen(encoded);
  char *key = (char*)malloc(sizeof(char) * size);

  for (int i = 0; i < size; ++i) {
    if (k >= strlen(secret) - 1) {
      k = 0;
    }
    key[i] = secret[k++];
  };
  key[size] = '\0';

  return key;
};

int getRow(int size, char **matrix, char cryptoLetter) {
  for (int i = 0; i < size; ++i) {
    if (matrix[i][0] == cryptoLetter) {
      return i;
    }
  };
};


int getCol(int size, char *row, char letter) {
  for (int i = 0; i < strlen(row); ++i) {
    if (row[i] == letter) return i;
  };
};
