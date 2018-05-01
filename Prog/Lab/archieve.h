#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#ifndef archieve_h
#define archieve_h

#define filled_byte(bits, mask) (log2(bits) / (mask * 8) == 1 && bits != 1)

void lz78(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *,
  int *,
  int *
);

void _lz78(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *,
  int *,
  int *
);

// Compression
//
void compress_file(char *filename, char *output_filename) {
  std::ifstream input (filename, std::ifstream::binary);
  std::ofstream output (output_filename, std::ios::app);

  std::filebuf *buf = input.rdbuf();

  int input_size = 0;
  int output_size = 0;

  lz78(&input, &output, buf, &input_size, &output_size);

  int diff = input_size - output_size;
  float coef = float(float(diff) / float(input_size));
  std::cout << "Input: " << input_size << std::endl;
  std::cout << "Output: " << output_size << std::endl;
  std::cout << "Compression coeficient: " << coef << std::endl;

  input.close();
  output.close();
}


void lz78(
  std::ifstream *input,
  std::ofstream *output,
  std::filebuf *buf,
  int *input_size,
  int *output_size
) {
  int size = buf->pubseekoff(0, input->end, input->in);
  *input_size = size;
  int code = 1;
  int byte_mask = 1;
  std::map<std::string, int> phrases;
  std::string phrase;

  for (int i = 0; i < size; ++i) {
    buf->pubseekpos(i, input->in);
    char byte = buf->sgetc();
    phrase.push_back(byte);

    std::map<std::string, int>::iterator iter = phrases.find(phrase);
    if (iter == phrases.end()) {
      std::string subphrase = phrase.substr(0, phrase.length() - 1);
      std::map<std::string, int>::iterator it = phrases.find(subphrase);

      if (filled_byte(phrases.size(), byte_mask)) {
        ++byte_mask;
      }

      output->write(reinterpret_cast<const char *>(&it->second), byte_mask);
      output->write((char *) &byte, sizeof(char));
      *output_size += sizeof(char) + byte_mask;

      phrases.insert(std::pair<std::string, int>(phrase, code++));
      phrase.clear();
    }
  }
}


// Decompression
//
void decompress_file(char *filename) {
  std::ifstream input (filename, std::ifstream::binary);
  std::ofstream output ("example.txt", std::ios::app);

  std::filebuf *buf = input.rdbuf();

  int input_size = 0;
  int output_size = 0;

  _lz78(&input, &output, buf, &input_size, &output_size);

  std::cout << "Input: " << input_size << std::endl;
  std::cout << "Output: " << output_size << std::endl;

  input.close();
  output.close();
}

int bytes_to_int(char *array_of_chars, int size) {
  int res = 0;
  int *bytes = new int[size];

  for (int i = 0; i < size; i++) {
    char byte = array_of_chars[i];
    if (byte < 0) {
      int diff = 256 + byte;
      bytes[i] = diff;
    } else {
      bytes[i] = byte;
    }

  }

  while (size--) res = res * 256 + bytes[size];
  delete[] bytes;

  return res;
};

void _lz78(
  std::ifstream *input,
  std::ofstream *output,
  std::filebuf *buf,
  int *input_size,
  int *output_size
) {
  int size = buf->pubseekoff(0, input->end, input->in);
  *input_size = size;
  int code = 1;
  int byte_mask = 1;
  std::map<int, std::string> phrases;
  std::string phrase;

  for (int i = 0; i < size; i += byte_mask + 1) {
    if (filled_byte(phrases.size(), byte_mask)) {
      ++byte_mask;
    }

    buf->pubseekpos(i, input->in);
    char *index_bytes = new char[byte_mask];
    buf->sgetn(index_bytes, byte_mask);
    int index = bytes_to_int(index_bytes, byte_mask);
    buf->pubseekpos(i + byte_mask, input->in);
    char byte = buf->sgetc();

    if (index != 0) {
      std::map<int, std::string>::iterator it = phrases.find(index);
      *output << it->second;
      phrase = it->second;
    }

    output->write((char *) &byte, sizeof(char));
    phrase.push_back(byte);
    *output_size += phrase.length();
    phrases.insert(std::pair<int, std::string>(code++, phrase));
    phrase.clear();
    delete[] index_bytes;
  }
}


#endif
