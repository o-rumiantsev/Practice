#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getRow(int, char **, char);
int getCol(int, char **, char);
void offset(int, char *);
void copyString(char *, char *);
char *encode(char *, char*);
char *genKey(char *, char *);
char **genMatrix(char *);

int main() {
  int i = 0;
  int c;
  char message[256];
  char secret[256];

  printf("Enter message: ");
  fgets(message, 256, stdin);
  printf("Enter secret word: ");
  fgets(secret, 256, stdin);

  char *encoded = encode(secret, message);
  printf("Encoded message: %s \n", encoded);

  free(encoded);
  return 0;
};


char *encode(char *secret, char *message) {
  char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  char **matrix = genMatrix(alphabet);
  char *key = genKey(secret, message);

  int size = strlen(key);
  char *encoded = (char*)malloc(sizeof(char) * size);

  int msize = strlen(alphabet);

  for (int i = 0; i < size; ++i) {
    int row = getRow(msize, matrix, key[i]);
    int col = getCol(msize, matrix, message[i]);
    encoded[i] = matrix[row][col];
  };

  free(matrix);
  free(key);

  return encoded;
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


char *genKey(char *secret, char *message) {
  int k = 0;
  int size = strlen(message);
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


int getCol(int size, char **matrix, char letter) {
  for (int i = 0; i < strlen(matrix[0]); ++i) {
    if (matrix[0][i] == letter) return i;
  };
};
