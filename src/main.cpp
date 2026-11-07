// #include "tanam.h"
#include "tanam/ClassFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void readClassFile(std::string &classFilePath, std::vector<uint8_t> &buffer);

void readClassFile(std::string &classFilePath, std::vector<uint8_t> &buffer) {
 std::cout << "Processing " << classFilePath << std::endl;

 std::ifstream file(classFilePath, std::ios::binary);
 if (!file.is_open()) {
   std::cerr << "Failed to open: " << classFilePath << std::endl;
   return;
 }

 buffer.assign(
     std::istreambuf_iterator<char>(file),
     std::istreambuf_iterator<char>()
 );
 std::cout << "It opened.  Read " << buffer.size() << " bytes" << std::endl;
 file.close();

 return;
}  // End of the 'readClassFile' function

// int main(int, char** argv) {
//     std::string classFilePath(argv[1]);
//     std::vector<uint8_t> buffer;
//     readClassFile(classFilePath, buffer);
//
// //    for (const auto c : buffer) {
// //      std::cout << c;
// //    }
// //    std::cout << std::endl;
//
//
//     // for (int i = 0; i < buffer.size(); i+= 4) {
//     //   uint32_t val = buffer.at(i)   << 24 |
//     //                  buffer.at(i+1) << 16 |
//     //                  buffer.at(i+2) << 8  |
//     //                  buffer.at(i+3);
//     //   std::cout << std::hex << val << std::dec << std::endl;
//     // }
//     // std::cout << std::endl << std::endl;
//
//     ClassFile classFile(std::move(buffer));
//     classFile.hex_dump();
//     std::cout << classFile << std::endl;
//     return 0;
// }  // End of the 'main' function

void parse_file(std::string path) {
  std::vector<uint8_t> buffer;
  readClassFile(path, buffer);
  ClassFile classFile(std::move(buffer));
  classFile.hex_dump();
  std::cout << classFile << std::endl;
}  // End of the 'parse_file' function

PYBIND11_MODULE(my_module, m) {
  m.doc() = "pybind11 example plugin";
  m.def("parse_file", &parse_file, "A function for parsing a java class file");
}

// END OF FILE
