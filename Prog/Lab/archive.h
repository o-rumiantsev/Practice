#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#ifndef archieve_h
#define archieve_h

#define filled_byte(bits, mask) (log2(bits) / (mask * 8) == 1 && bits != 1)

void lz78_comp(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *,
  int *,
  int *
);

// Compression
//
//
void compress_file(char *filename, char *output_filename) {
  std::ifstream input (filename, std::ifstream::binary);
  std::ofstream output (output_filename, std::ios::app);

  std::filebuf *buf = input.rdbuf();

  int terminal_bell = 7;
  output.write(reinterpret_cast<const char*>(&terminal_bell), sizeof(char));
  output.write(reinterpret_cast<const char*>(&terminal_bell), sizeof(char));
  output << filename;
  output.write(reinterpret_cast<const char*>(&terminal_bell), sizeof(char));
  output.write(reinterpret_cast<const char*>(&terminal_bell), sizeof(char));

  int input_size = 0;
  int output_size = 0;

  lz78_comp(&input, &output, buf, &input_size, &output_size);

  int diff = input_size - output_size;
  float coef = float(float(diff) / float(input_size));
  std::cout << "Input: " << input_size << std::endl;
  std::cout << "Output: " << output_size << std::endl;
  std::cout << "Compression coeficient: " << coef << std::endl;

  input.close();
  output.close();
}


void lz78_comp(
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
    if (iter == phrases.end() || i == size - 1) {
      std::string subphrase = phrase.substr(0, phrase.length() - 1);
      std::map<std::string, int>::iterator it = phrases.find(subphrase);

      if (filled_byte(phrases.size(), byte_mask)) {
        ++byte_mask;
      }

      output->write(reinterpret_cast<const char *>(&it->second), byte_mask);
      *output << byte;
      *output_size += sizeof(char) + byte_mask;

      phrases.insert(std::pair<std::string, int>(phrase, code++));
      phrase.clear();
    }
  }
}


// Decompression
//

void separate_decomp(
  std::ifstream *,
  std::filebuf *
);

void lz78_decomp(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *,
  int,
  int
);

void decompress_file(char *filename) {
  std::ifstream input (filename, std::ifstream::binary);
  std::filebuf *buf = input.rdbuf();

  separate_decomp(&input, buf);

  input.close();
}

void separate_decomp(
  std::ifstream *input,
  std::filebuf *buf
) {
  int size = buf->pubseekoff(0, input->end, input->in);
  buf->pubseekpos(0, input->in);

  int prev_byte = buf->sgetc();
  int reading_filename = 0;
  int reading_buffer = 0;
  int compressed_size = 0;
  int offset = 0;
  std::string output_filename;

  for (int i = 1; i < size; ++i) {
    buf->pubseekpos(i, input->in);
    int byte = buf->sgetc();

    if (byte == 7 && prev_byte == 7) {
      prev_byte = byte;
      std::cout << "bell" << std::endl;
      if (reading_filename) {
        offset = i + 1;
        reading_filename = 0;
        reading_buffer = 1;
        std::cout << "Reading buffer..." << std::endl;
      } else if (reading_buffer) {
        std::string filename = output_filename.substr(
        0, output_filename.length() - 1
        );
        std::ofstream output (filename, std::ios::app);
        lz78_decomp(input, &output, buf, compressed_size - 1, offset);
        output.close();
        reading_filename = 1;
        reading_buffer = 0;
        compressed_size = 0;
        std::cout << "Stop reading buffer..." << std::endl;
        std::cout << "Reading next filename..." << std::endl;
        output_filename.clear();
      } else {
        std::cout << "Reading filename..." << std::endl;
        reading_filename = 1;
        reading_buffer = 0;
      }
      continue;
    }

    if (reading_filename) {
      prev_byte = byte;

      output_filename.push_back(byte);
      continue;
    }

    if (reading_buffer) ++compressed_size;

    prev_byte = byte;
  }

  std::string filename = output_filename.substr(
    0, output_filename.length() - 1
  );
  std::cout << output_filename << " " << compressed_size << std::endl;
  std::ofstream output (filename, std::ios::app);
  lz78_decomp(input, &output, buf, compressed_size - 1, offset);
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

void lz78_decomp(
  std::ifstream *input,
  std::ofstream *output,
  std::filebuf *buf,
  int size,
  int offset
) {
  int code = 1;
  int byte_mask = 1;
  std::map<int, std::string> phrases;
  std::string phrase;

  for (int i = offset; i < offset + size; i += byte_mask + 1) {
    buf->pubseekpos(i, input->in);

    if (filled_byte(phrases.size(), byte_mask)) {
      ++byte_mask;
    }

    char *index_bytes = new char[byte_mask];
    buf->sgetn(index_bytes, byte_mask);
    int index = bytes_to_int(index_bytes, byte_mask);
    buf->pubseekpos(i + byte_mask, input->in);
    char byte = buf->sgetc();
    delete[] index_bytes;

    if (index != 0) {
      std::map<int, std::string>::iterator it = phrases.find(index);
      *output << it->second;
      phrase = it->second;
    }

    *output << byte;
    phrase.push_back(byte);
    phrases.insert(std::pair<int, std::string>(code++, phrase));
    phrase.clear();
  }
}


#endif
