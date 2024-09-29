from functools import lru_cache, cache
from typing import Any
import time

@cache
def nearest_divisor(number):
    divisor = 1
    for i in range(2, int(number**0.5) + 1):
        if number % i == 0:
            if i < number / i:
                divisor = i
            else:
                divisor = number // i
    return divisor

@lru_cache(typed=True, maxsize=30)
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


fnd = 'wor'

string = "hello world"

print(str_index(string, fnd))
