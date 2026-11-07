#ifndef _TANAM_H
#define _TANAM_H

#include <cstdint>
#include <vector>
#include <iomanip>

using u1 = uint8_t;  // 1 byte
using u2 = uint16_t; // 2 bytes
using u4 = uint32_t; // 4 bytes

// TODO DEPRECATED
// struct cpu_info { u1 idk; };
// struct field_info { u1 idk; };
// struct method_info { u1 idk; };
// struct attribute_info { u1 idk; };

struct Padding {
  int pad; 
};

inline std::ostream& operator<<(std::ostream& os, Padding& padding) {
  os << std::setfill(' ') << std::setw(padding.pad) << "";
  return os;
};

#endif /* _TANAM_H */

// END OF FILE
