#ifndef __TANAM_H
#define __TANAM_H

#include <cstdint>
#include <vector>
#include <iomanip>

using u1 = uint8_t;  // 1 byte
using u2 = uint16_t; // 2 bytes
using u4 = uint32_t; // 4 bytes

struct Padding {
  int pad; 
};

inline std::ostream& operator<<(std::ostream& os, Padding& padding) {
  os << std::setfill(' ') << std::setw(padding.pad) << "";
  return os;
};

#endif /* __TANAM_H */

// END OF FILE
