#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void getX(
  ifstream *,
  int *,
  int *,
  int *,
  string,
  int
);

void getY(
  float *,
  int *,
  int,
  int,
  int
);

void get_Y(
  ifstream *,
  float *,
  string,
  int
);

void fillZ(
  float *,
  float *,
  int,
  float *,
  int
);

int main() {
  ifstream input ("Disney.txt");
  string line;
  getline(input, line);

  int size = stoi(line);
  int *X = new int[size];
  line.clear();

  int X_max, X_min;
  getX(&input, X, &X_max, &X_min, line, size);
  input.close();

  float *Y = new float[size];
  getY(Y, X, X_max, X_min, size);

  ofstream output ("Y.txt");
  for (int i = 0; i < size; ++i) output << Y[i] << endl;
  output.close();

  input.open("_Y.txt");
  getline(input, line);

  int _size = stoi(line);
  float *_Y = new float[_size];
  line.clear();

  get_Y(&input, _Y, line, _size);
  input.close();

  float *Z = new float[size];
  fillZ(Z, Y, size, _Y, _size);

  output.open("Z.txt");
  for (int i = 0; i < size; ++i) output << Z[i] << endl;
  output.close();
}


void getX(
  ifstream *input,
  int *X,
  int *X_max,
  int *X_min,
  string line,
  int size
) {
  for (int i = 0; i < size; ++i) {
    getline(*input, line);
    X[i] = stoi(line);
    line.clear();

    if (i == 0) {
      *X_max = X[i];
      *X_min = X[i];
    }
    if (X[i] > *X_max) *X_max = X[i];
    if (X[i] < *X_min) *X_min = X[i];
  }
}

void getY(
  float *Y,
  int *X,
  int X_max,
  int X_min,
  int size
) {
  float Y_max = 5587.65, Y_min = 16.3516;
  float coef = (Y_max - Y_min) / (X_max - X_min);

  for (int i = 0; i < size; ++i) {
    Y[i] = X[i] * coef;
  }
}

void get_Y(
  ifstream *input,
  float *_Y,
  string line,
  int _size
) {
  for (int i = 0; i < _size; ++i) {
    getline(*input, line);
    _Y[_size - i - 1] = stof(line);
    line.clear();
  }
}

void fillZ(
  float *Z,
  float *Y,
  int size,
  float *_Y,
  int _size
) {
  for (int i = 0; i < size; ++i) {
    for (int j = 1; j < _size; ++j) {
      if (Y[i] < _Y[j]) {
        float avg = (_Y[j] + _Y[j - 1]) / 2;
        Z[i] = Y[i] < avg ? _Y[j - 1] : _Y[j];
        break;
      }
    }
  }
}
