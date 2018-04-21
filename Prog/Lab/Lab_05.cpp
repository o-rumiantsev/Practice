#include <iostream>
#include "archieve.h"
#include <string>

using namespace std;

int main(int argc, char **argv) {
  char *mode = argv[1];
  string compress_mode = "--compress";
  string decompress_mode = "--decompress";

  if (mode == compress_mode) {
    cout << "compressing..." << endl;
    char *output = argv[2];
    int i;
    for (i = 3; i < argc; ++i) {
      compress_file(argv[i], output);
    }
  } else if (mode == decompress_mode) {
    cout << "decompressing..." << endl;
    decompress_file(argv[2]);
  } else {
    cout << "Ivalid mode" << endl;
    cout << "--compress";
    cout << " to comress files" << endl;
    cout << "--decompress";
    cout << " to decompress files" << endl;
  }

  return 0;
}
