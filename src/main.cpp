#include "blowfish.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void printhelp() {
  cout << "Usage:" << endl
       << "./blow "
       << "-m <encrypt|decrypt> "
       << "-k <key_file> "
       << "-i <input_file> " << endl;
  cout << "./blow -h : print this help message" << endl;
}

int main(int argc, char *argv[]) {
  if (argc == 2 && strcmp(argv[1], "-h") == 0) {
    printhelp();
    return 0;
  }

  if (argc != 7) {
    printhelp();
    return 1;
  }

  string mode = "";
  string key_file = "";
  string input_file = "";

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 'm':
        if (strcmp(argv[i + 1], "encrypt") == 0) {
          mode = "encrypt";
        } else if (strcmp(argv[i + 1], "decrypt") == 0) {
          mode = "decrypt";
        } else {
          printhelp();
          return 1;
        }
        break;
      case 'k':
        key_file = argv[i + 1];
        break;
      case 'i':
        input_file = argv[i + 1];
        break;
      default:
        printhelp();
        return 1;
      }
    }
  }

  if (mode == "" || key_file == "" || input_file == "") {
    printhelp();
    return 1;
  }

  ifstream kf(key_file, ios::in | ios::binary);
  if (!kf) {
    cout << "Cannot open " << key_file << endl;
    return 1;
  }
  vector<unsigned char> key(istreambuf_iterator<char>(kf), {});
  kf.close();

  fstream inf(input_file, ios::in | ios::binary);
  if (!inf) {
    cout << "Cannot open " << input_file << endl;
    return 1;
  }
  vector<unsigned char> input(istreambuf_iterator<char>(inf), {});
  inf.close();

  vector<unsigned char> output(input.size());

  Blowfish bf;
  bf.init(key.data(), key.size());

  if (mode == "encrypt") {
    bf.Encrypt(input.data(), output.data(), input.size());
  } else if (mode == "decrypt") {
    bf.Decrypt(input.data(), output.data(), input.size());
  }

  fstream ouf(input_file, ios::out | ios::binary);
  if (!ouf) {
    cout << "Cannot open " << input_file << " to write encrypted/decrypted data"
         << endl;
    return 1;
  }
  ouf.write((char *)output.data(), output.size());

  return 0;
}
