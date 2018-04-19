#include <iostream>
#include <fstream>
#ifndef archieve_h
#define archieve_h



void compress_file(char *filename) {
  std::ifstream input (filename, std::ifstream::binary);
  std::filebuf *buf = input.rdbuf();

  int size = buf->pubseekoff(0, input.end, input.in);

  int repeated_bytes = 0;
  int counter = 0;
  int previous_byte = -1;

  for (int i = 0; i < size; ++i) {
    buf->pubseekpos(i, input.in);
    char *buffer = new char[1];
    buf->sgetn(buffer, 1);

    int byte = int(buffer[0]);
    if (byte == previous_byte) {
      ++counter;
    } else if (counter != 0) {
      repeated_bytes += counter - 1;
      counter = 0;
    }

    previous_byte = byte;
    delete[] buffer;
  }

  float comp_coef = float(float(repeated_bytes) / float(size));
  std::cout << "Compression coeficient: " << comp_coef << std::endl;

  input.close();
}



#endif
