// Copyright 2012 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <fstream>
#include <iostream>

int main() {
  std::ifstream filer("./practice.cpp", std::ios_base::in);
  if (!filer) {
    printf("cannot open file\n");
    return 1;
  }
  while (!(filer.eof())) {
    char c = (filer.get());
    if (c != EOF) {
      putchar(c);
    }
  }
  filer.close();
  return 0;
}