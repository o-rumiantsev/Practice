#include <iostream>
#include <fstream>
#include <string>
#include <map>
#ifndef archieve_h
#define archieve_h

void lz78(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *
);

void rle(
  std::ifstream *,
  std::ofstream *,
  std::filebuf *
);


// Compression
//
void compress_file(char *filename, char *output_filename) {
  std::ifstream input (filename, std::ifstream::binary);
  std::ofstream temp_out ("temp.comp", std::ios::binary);
  temp_out << std::hex << std::uppercase;

  std::filebuf *buf_temp = input.rdbuf();

  rle(&input, &temp_out, buf_temp);

  input.close();
  temp_out.close();

  std::ifstream temp_in ("temp.comp", std::ifstream::binary);
  std::ofstream output (output_filename, std::ios::binary);
  output << std::hex << std::uppercase;

  std::filebuf *buf = temp_in.rdbuf();

  lz78(&temp_in, &output, buf);

  temp_in.close();
  output.close();
}


void lz78(
  std::ifstream *input,
  std::ofstream *output,
  std::filebuf *buf
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
      std::cout << encoded << " ";

      *output << encoded;
      phrases.insert(std::pair<std::string, int>(phrase, code--));
      phrase.clear();
    }
  }

  std::cout << std::endl;
}


void rle(
  std::ifstream *input,
  std::ofstream *output,
  std::filebuf *buf
) {
  int size = buf->pubseekoff(0, input->end, input->in);

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
