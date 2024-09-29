#include <cmath>
#include <iostream>
#include <string>

using namespace std;

/* def nearest_divisor(number: int) -> int: */
int nearestDivisor(int number) {
  int divisor = 1;
  for (int i = 2; i <= sqrt(number); ++i) {
    if (number % i == 0) {
      if (i < number / i) {
        divisor = i;
      } else {
        divisor = number / i;
      }
    }
  }
  return divisor;
}
/*
def str_index(string: str, found: str, size_buf: int = -1) -> int:
    length_s: int = len(string)
    length_f: int = len(found)
    if size_buf == -1:
        size_buf = nearest_divisor(length_f)
    if length_f % size_buf != 0:
        raise ValueError("length_f must be a multiple of size_buf.")
    for i in range(length_s - length_f + 1):
        if string[i:i+size_buf] == found[:size_buf]:
            for j in range(i, i + length_f, size_buf):
                if string[j:j+size_buf] != found[j-i:j-i+size_buf]:
                    break
            else:
                return i
    return -1
*/
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

int main() { cout << strIndex("hello world", "world"); }
