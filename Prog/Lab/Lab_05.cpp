#include <iostream>
#include "archive.h"
#include <string>

using namespace std;

int main(int argc, char **argv) {
  char *mode = argv[1];
  char *algorithm = argv[2];

  string compress_mode = "--compress";
  string decompress_mode = "--decompress";

  if (mode == compress_mode) {
    cout << "compressing..." << endl;
    char *output = argv[3];
    remove(output);
    compress_file(argv[4], output, algorithm);
  } else if (mode == decompress_mode) {
    cout << "decompressing..." << endl;
    decompress_file(argv[3]);
  } else {
    cout << "Invalid mode" << endl;
    cout << "--compress";
    cout << " to comress files" << endl;
    cout << "--decompress";
    cout << " to decompress files" << endl;
  }

  return 0;
}
