#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#ifndef archieve_h
#define archieve_h

#define filled_byte(bits, mask) (log2(bits) / (mask * 8) == 1 && bits != 1)

void rle(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *,
  int *,
  int *
);

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
void compress_file(char *filename, char *output_filename, char *type) {
  std::ifstream input (filename, std::ifstream::binary);
  std::ofstream output (output_filename, std::ios::app);

  std::filebuf *buf = input.rdbuf();

  int terminal_bell = 7;
  output << filename;
  output.write(reinterpret_cast<const char*>(&terminal_bell), sizeof(char));
  output.write(reinterpret_cast<const char*>(&terminal_bell), sizeof(char));

  int input_size = 0;
  int output_size = 0;
  std::string lz_algorithm ("lz");
  std::string rle_algorithm ("rle");

  if (type == lz_algorithm) {
    lz78_comp(&input, &output, buf, &input_size, &output_size);
  } else if (type == rle_algorithm){
    rle(&input, &output, buf, &input_size, &output_size);
  }

  int diff = input_size - output_size;
  float coef = float(float(diff) / float(input_size));
  std::cout << "Input: " << input_size << std::endl;
  std::cout << "Output: " << output_size << std::endl;
  std::cout << "Compression coeficient: " << coef << std::endl;

  input.close();
  output.close();
}

void rle(
  std::ifstream *input,
  std::ofstream *output,
  std::filebuf *buf,
  int *input_size,
  int *output_size
) {
  int size = buf->pubseekoff(0, input->end, input->in);
  buf->pubseekpos(0, input->in);

  *input_size = size;
  int bytes_count = 1;

  for (int i = 0; i < size - 1; ++i) {
    char byte = buf->sgetc();

    buf->pubseekpos(i + 1, input->in);
    char next_byte = buf->sgetc();

    if (byte == next_byte && bytes_count != 255) {
      ++bytes_count;
      continue;
    }

    if (bytes_count > 1) {
      output->write(reinterpret_cast<const char *>(&bytes_count), sizeof(char));
      *output_size += 1;
    }

    *output << byte;
    *output_size += 1;

    bytes_count = 1;
  }
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

      if (code == 65535) {
        phrases.clear();
        byte_mask = 1;
        code = 1;
      }

      phrases.insert(std::pair<std::string, int>(phrase, code++));
      phrase.clear();
    }
  }
}


// Decompression
//

void lz78_decomp(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *,
  int
);

std::string read_filename(
  std::ifstream *,
  std::filebuf *,
  int *
);

void decompress_file(char *filename) {
  std::ifstream input (filename, std::ifstream::binary);
  std::filebuf *buf = input.rdbuf();

  // separate_decomp(&input, buf);
  int pos;
  std::string output_filename = read_filename(&input, buf, &pos);

  std::ofstream output (output_filename, std::ios::app);
  lz78_decomp(&input, &output, buf, ++pos);

  input.close();
  output.close();
}

std::string read_filename(
  std::ifstream *input,
  std::filebuf *buf,
  int *pos
) {
  std::string filename;
  int prev_byte;
  int byte = buf->sgetc();
  *pos = 0;

  while (!(byte == 7 && prev_byte == 7)) {
    filename.push_back(byte);
    prev_byte = byte;
    buf->pubseekpos(++(*pos), input->in);
    byte = buf->sgetc();
  }

  return filename.substr(
    0, filename.length() - 1
  );
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
  int offset
) {
  int size = buf->pubseekoff(0, input->end, input->in);
  int code = 1;
  int byte_mask = 1;
  std::map<int, std::string> phrases;
  std::string phrase;

  for (int i = offset; i < size; i += byte_mask + 1) {
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
