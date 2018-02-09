#include <stdio.h>
#include <string.h>

int getRow(int, char **, char);
int getCol(int, char **, char);
char *offset(int, char *);
char *encode(char *, char*);
char *genKey(char *, char *);
char **genMatrix(void);

int main() {
  int i = 0;
  int c;
  char message[] = "message"; //[256];
  char secret[] = "secret"; //[256];

  // fgets(message, 256, stdin);
  // fgets(secret, 256, stdin);

  char *encoded = encode(secret, message);

  // printf("Encoded message: %s\n", encoded);
  return 0;
};


char *encode(char *secret, char *message) {
  int size = strlen(message) + 1;
  char encoded[size];
  char **matrix = genMatrix();
  char *key = genKey(secret, message);


  int msize = sizeof(matrix)/sizeof(char *);

  for (int i = 0; i < size - 1; ++i) {
    int row = getRow(msize, matrix, key[i]);
    int col = getCol(msize, matrix, message[i]);
    encoded[i] = matrix[row][col];
  };


  char *pointer = key;
  return pointer;
};


char **genMatrix(void) {
  char *matrix[27];
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz ";
  int length = strlen(alphabet);

  for (int i = 0; i < length; ++i) {
    // char *row =
    matrix[i] = offset(length, alphabet);
  };
  printf("%s \n", matrix[i]);

  char **pointer = matrix;
  // for (int i = 0; i < length; ++i) {
  //   printf("%s \n", pointer[i]);
  // }
  return pointer;
};


char *offset(int length, char *string) {
  char result[length + 1];
  strcpy(result, string);

  for (int i = 0; i < length - 1; i++) {
    char c = string[i];
    string[i] = string[i + 1];
    string[i + 1] = c;
  };

  char *pointer = result;
  return pointer;
};


char *genKey(char *secret, char *message) {
  int k = 0;
  int size = strlen(message) + 1;
  char key[size];

  for (int i = 0; i < strlen(message); ++i) {
    if (k >= strlen(secret)) {
      k = 0;
    }
    key[i] = secret[k++];
  };

  char *pointer = key;
  return pointer;
};



int getRow(int size, char **matx, char cryptoLetter) {
  for (int i = 0; i < size; ++i) {
    if (matx[i][0] == cryptoLetter) {
      return i;
    }
  };
};


int getCol(int size, char **matx, char letter) {
  for (int i = 0; i < strlen(matx[0]); ++i) {
    if (matx[0][i] == letter) return i;
  };
};
