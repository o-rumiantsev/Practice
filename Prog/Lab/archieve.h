#include <iostream>
#include <fstream>
#include <string>
#include <map>
#ifndef archieve_h
#define archieve_h

void rle(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *,
  int *
);

void lz78(
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
  std::ofstream temp_out ("temp.comp", std::ios::binary);
  temp_out << std::hex << std::uppercase;

  std::filebuf *buf_temp = input.rdbuf();

  int input_size = 0;

  rle(&input, &temp_out, buf_temp, &input_size);

  input.close();
  temp_out.close();


  std::ifstream temp_in ("temp.comp", std::ifstream::binary);
  std::ofstream output (output_filename, std::ios::app);
  output << std::hex << std::uppercase;

  std::filebuf *buf = temp_in.rdbuf();

  int output_size = 0;

  lz78(&temp_in, &output, buf, &input_size, &output_size);

  int diff = input_size - output_size;
  float coef = float(float(diff) / float(input_size));
  std::cout << "Input: " << input_size << std::endl;
  std::cout << "Output: " << output_size << std::endl;
  std::cout << "Compression coeficient: " << coef << std::endl;

  temp_in.close();
  remove("temp.comp");
  output.close();
}


void rle(
  std::ifstream *input,
  std::ofstream *output,
  std::filebuf *buf,
  int *input_size
) {
  int size = buf->pubseekoff(0, input->end, input->in);
  *input_size = size;

  int counter = 0;
  int previous_byte = -1;

  for (int i = 0; i < size; ++i) {
    buf->pubseekpos(i, input->in);
    int byte = buf->sgetc();

    if (byte == previous_byte) {
      --counter;
    } else if (counter != 0) {
      output->write(
        (char *) &counter, sizeof(counter) / sizeof(int)
      );
      output->write(
        (char *) &previous_byte, sizeof(previous_byte) / sizeof(int)
      );
      counter = 0;
    } else if (previous_byte != -1) {
      output->write(
        (char *) &previous_byte, sizeof(previous_byte) / sizeof(int)
      );
    }

    previous_byte = byte;
  }
}


void lz78(
  std::ifstream *input,
  std::ofstream *output,
  std::filebuf *buf,
  int *input_size,
  int *output_size
) {
  int size = buf->pubseekoff(0, input->end, input->in);
  int code = -1;
  std::map<std::string, int> phrases;
  std::string phrase;

  for (int i = 0; i < size; ++i) {
    buf->pubseekpos(i, input->in);
    char byte = buf->sgetc();
    phrase.push_back(byte);

    std::map<std::string, int>::iterator iter = phrases.find(phrase);
    if (iter == phrases.end()) {
      std::string encoded;
      std::string subphrase = phrase.substr(0, phrase.length() - 1);
      std::map<std::string, int>::iterator it = phrases.find(subphrase);

      if (it != phrases.end()) {
        encoded.push_back(it->second);
      }

      encoded.push_back(byte);

      *output << encoded;
      *output_size += encoded.length();

      phrases.insert(std::pair<std::string, int>(phrase, code--));
      phrase.clear();
    }
  }
}



// Decompression
//
void decompress_file(char *filename) {
  std::ifstream input (filename, std::ifstream::binary);
  std::filebuf *buf = input.rdbuf();

  int size = buf->pubseekoff(0, input.end, input.in);

  for (int i = 0; i < size; ++i) {
    buf->pubseekpos(i, input.in);
    char *buffer = new char[1];
    buf->sgetn(buffer, 1);
    delete[] buffer;
  }

  input.close();
}

#endif
