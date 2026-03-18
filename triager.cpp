#include "sharehack.h"
#include <cstring>
#include <iostream>

// TODO: change input
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "(.) need to provide an arg to the triager" << std::endl;
    return -1;
  }
  size_t len = std::strlen(argv[1]);
  return LLVMFuzzerTestOneInput(argv[1], len);
}
