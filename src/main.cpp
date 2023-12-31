#include "blowfish.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// prints help message
void help() {
  cout << "Usage:" << endl
       << "./blow "
       << "-m <encrypt|decrypt> "
       << "-k <key_file> "
       << "-i <input_file> " << endl;
  cout << "-h : print this help message" << endl;
  cout << "-m : cipher mode [encrypt|decrypt]" << endl;
  cout << "-k : key filename" << endl;
  cout << "-i : input filename" << endl;
}

// The main driver function
int main(int argc, char *argv[]) {
  if (argc == 2 && strcmp(argv[1], "-h") == 0) {
    help();
    return 0;
  }

  if (argc != 7) {
    help();
    return 1;
  }

  string mode = "";
  string key_file = "";
  string input_file = "";

  // parsing arguments
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 'm':
        if (strcmp(argv[i + 1], "encrypt") == 0) {
          mode = "encrypt";
        } else if (strcmp(argv[i + 1], "decrypt") == 0) {
          mode = "decrypt";
        } else {
          help();
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
        help();
        return 1;
      }
    }
  }

  if (mode == "" || key_file == "" || input_file == "") {
    help();
    return 1;
  }

  // reading the key from the key file
  ifstream kf(key_file, ios::in | ios::binary);
  if (!kf) {
    cout << "Cannot open " << key_file << endl;
    return 1;
  }
  vector<unsigned char> key(istreambuf_iterator<char>(kf), {});
  kf.close();

  // reading input to be encrypted/decrypted from the input file
  fstream inf(input_file, ios::in | ios::binary);
  if (!inf) {
    cout << "Cannot open " << input_file << endl;
    return 1;
  }
  vector<unsigned char> input(istreambuf_iterator<char>(inf), {});
  inf.close();

  // Setting an alias of the input as output.
  // We will be doing in place encryption/decryption
  vector<unsigned char> &output = input;

  // Creating the blowfish cipher object with key
  Blowfish bf(key.data(), key.size());

  // Calculate padding length
  int padding = (8 - input.size() % 8) % 8;
  if (mode == "encrypt") {
    // Adding additional padding if the input size is not multiple of 8 bytes
    if (padding > 0) {
      int t = padding;
      while (t--) {
        input.push_back(0x00);
      }
    }
    // call to encryption
    bf.encrypt(input.data(), input.size());
  } else {
    // call to decryption
    bf.decrypt(input.data(), input.size());
  }

  // write encrypted/decrypted data to the [out|in]put file
  fstream ouf(input_file, ios::out | ios::binary);
  if (!ouf) {
    cout << "Cannot open " << input_file << " to write encrypted/decrypted data"
         << endl;
    return 1;
  }
  ouf.write((char *)output.data(), output.size());

  return 0;
}
