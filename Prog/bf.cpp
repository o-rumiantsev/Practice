#include <iostream>
#include <string>

using namespace std;

// Move element with index i to left
//
//
string move_left(string src, int i) {
  if (src[i + 1] && src[i + 1] != ' ') {
    char k = src[i];
    src[i] = src[i + 1];
    src[i + 1] = k;
    return move_left(src, i + 1);
  }
  return src;
}

// Remove invalid symbols
//
//
string validate(string src) {
  int len = src.length();
  int move_count = 0;

  for (int i = 0; i < len; ++i) {
    if (
      src[i] != '+' &&
      src[i] != '-' &&
      src[i] != '[' &&
      src[i] != ']' &&
      src[i] != '<' &&
      src[i] != '>' &&
      src[i] != '.' &&
      src[i] != ','
    ) {
      src[i] = ' ';
      ++move_count;
    }
  }

  for (int i = src.length(); i >= 0; --i) {
    if (src[i] == ' ') src = move_left(src, i);
  }

  string valid = src.substr(0, len - move_count);
  return valid;
}

// Recursive optimization
//
//
string opt(string src) {
  bool optimized = true;
  int len = src.length();
  int move_count = 0;

  for (int i = 0; i < len; ++i) {
    if (
      (src[i] == '+' && src[i + 1] == '-') ||
      (src[i] == '-' && src[i + 1] == '+') ||
      (src[i] == '[' && src[i + 1] == ']') ||
      (src[i] == '<' && src[i + 1] == '>') ||
      (src[i] == '>' && src[i + 1] == '<')
    ) {
      src[i] = ' ';
      src[i + 1] = ' ';
      move_count += 2;
      optimized = false;
    }
  }

  for (int i = src.length(); i >= 0; --i) {
    if (src[i] == ' ') src = move_left(src, i);
  }

  string result = src.substr(0, len - move_count);

  if (!optimized) return opt(result);
  else return result;
}

// Count unpaired [ and ]
//
//
int count_unpaired(string src) {
  if (src[0] == ']') return 1;
  int count = 0;
  int len = src.length();

  for (int i = 0; i < len; ++i) {
    if (src[i] == '[') ++count;
    else if (src[i] == ']') --count;
  }

  return count;
}

// Main translator
//
//
string brainfuck_to_c(string source_code) {
  string valid = validate(source_code);

  string src = opt(valid);

  int unpaired = count_unpaired(src);
  if (unpaired) return string("Error!");

  string result;
  int len = src.length();

  int count = 0;
  string tab;

  for (int i = 0; i < len; ++i) {
    if (src[i] == '+' ||
        src[i] == '-' ||
        src[i] == '>' ||
        src[i] == '<'
    ) ++count;

    if (
      src[i] == '.' ||
      src[i] == ',' ||
      src[i] == '[' ||
      src[i] == ']' ||
      src[i] != src[i + 1]
    ) {
      if (src[i] == '+') {
        result.append(tab);
        result.append("*p += ");
        result.append(to_string(count));
        result.append(";\n");
        count = 0;
      } else if (src[i] == '-') {
        result.append(tab);
        result.append("*p -= ");
        result.append(to_string(count));
        result.append(";\n");
        count = 0;
      } else if (src[i] == '>') {
        result.append(tab);
        result.append("p += ");
        result.append(to_string(count));
        result.append(";\n");
        count = 0;
      } else if (src[i] == '<') {
        result.append(tab);
        result.append("p -= ");
        result.append(to_string(count));
        result.append(";\n");
        count = 0;
      } else if (src[i] == '.') {
        result.append(tab);
        result.append("putchar(*p);\n");
      } else if (src[i] == ',') {
        result.append(tab);
        result.append("*p = getchar();\n");
      } else if (src[i] == '[') {
        result.append(tab);
        result.append("if (*p) do {\n");
        tab.append("  ");
      } else if (src[i] == ']') {
        tab.pop_back();
        tab.pop_back();
        result.append(tab);
        result.append("} while (*p);\n");
      }
    }

  }

  return result;
}


int main(int argc, char **argv) {
  for (int i = 0; i < 50; ++i) {
    string res = brainfuck_to_c("<-.[,,+]---><[][-,>[[+[],>+>..,><+[<.,+<>..<-.[,,+]---><[][-,>[[+[],>+>..,><+[<.,+<>..-+,[[+,.><>[><><<-.-,<->>>.++<-,.<][++--,<[-,],++[,->+[-]]]]]]]]]<-.[,,+]---><[][-,>[[+[],>+>..,><+[<.,+<>..-+,[[+,.><>[><><<-.-,<->>>.++<-,.<][++--,<[-,],++[,->+[-]]]]]]]]]<-.[,,+]---><[][-,>[[+[],>+>..,><+[<.,+<>..-+,[[+,.><>[><><<-.-,<->>>.++<-,.<][++--,<[-,],++[,->+[-]]]]]]]]]<-.[,,+]---><[][-,>[[+[],>+>..,><+[<.,+<>..-+,[[+,.><>[><><<-.-,<->>>.++<-,.<][++--,<[-,],++[,->+[-]]]]]]]]]-+,[[+,.><>[><><<-.-,<->>>.++<-,.<][++--,<[-,],++[,->+[-]]]]]]]]]");
  }
  cout << "End" << endl;
  // cout << res << endl;
  return 0;
}