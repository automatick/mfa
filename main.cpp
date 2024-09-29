#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int nearestDivisor(int number) {
  if (number < 2)
    return 1;
  int divisor = 1;
  for (int i = 2; i <= sqrt(number); ++i) {
    if (number % i == 0) {
      divisor = (i < number / i) ? i : number / i;
    }
  }
  return divisor;
}

int strIndex(const string &str, const string &found, int sizeBuf = -1) {
  size_t lengthS = str.length();
  size_t lengthF = found.length();
  if (sizeBuf == -1) {
    sizeBuf = nearestDivisor(lengthF);
  }
  if (lengthF % sizeBuf != 0) {
    throw std::runtime_error("length_f must be a multiple of size_buf.");
  }

  int end = lengthS - lengthF;
  for (int i = 0; i <= end; ++i) {
    if (str.substr(i, sizeBuf) == found.substr(0, sizeBuf)) {
      bool match = true;
      for (int j = i; j < i + lengthF; j += sizeBuf) {
        if (str.substr(j, sizeBuf) != found.substr(j - i, sizeBuf)) {
          match = false;
          break;
        }
      }
      if (match) {
        return i;
      }
    }
  }
  return -1;
}

string readFile(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    throw runtime_error("File not found!");
  }
  string result;
  string line;
  while (getline(file, line)) {
    result += line + "\n";
  }
  return result;
}

// Main function
int main() {
  try {
    string content = readFile("lorem.txt");
    int index = strIndex(content, "yar");
    cout << "Index: " << index << endl; // Print the index
  } catch (const std::exception &e) {
    cerr << "Error: " << e.what() << endl; // Print error messages
  }
  return 0;
}
