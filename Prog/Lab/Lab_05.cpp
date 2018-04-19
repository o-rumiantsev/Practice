#include <iostream>
#include "archieve.h"

using namespace std;

int main(int argc, char **argv) {
  int i;
  for (i = 1; i < argc; ++i) {
    compress_file(argv[i]);
  }
  return 0;
}
