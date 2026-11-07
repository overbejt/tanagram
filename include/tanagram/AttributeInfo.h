#ifndef __ATTRIBUTE_INFO
#define __ATTRIBUTE_INFO

#include "Tanagram.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using Infos = std::vector<u1>;

class AttributeInfo {
  public:
    AttributeInfo(u2 attributeNameIndex, u4 attributeLength, Infos info) 
      : attributeNameIndex(attributeNameIndex), 
        attributeLength(attributeLength), 
        info(std::move(info)) { };
    u2 attributeNameIndex;
    u4 attributeLength;
    Infos info;
    friend std::ostream& operator<<(std::ostream &os, const AttributeInfo &current);
};

using Attributes = std::vector<AttributeInfo>;

inline std::ostream& operator<<(std::ostream &os, const AttributeInfo &current) {
  Padding padding{6};
  os << "{\n";
  os << padding << "attributeNameIndex: 0x";
  os << std::setfill('0') << std::setw(4) << std::hex;
  os << current.attributeNameIndex << ", \n";
  os << padding << "attributeLength: 0x";
  os << current.attributeLength << std::setw(2) << "\n";
  os << padding << "info: [ ";
  if (current.info.size() == 0) {
    os << "]\n";
  } else {
    for (const auto& i : current.info) {
      os << std::setfill('0') << std::setw(2) << std::hex;
      os << (uint32_t)i << ", ";
    }
    os << std::dec << " ]\n";
  }
  padding.pad = 4;
  os << padding << "}";
  return os;
};

#endif /* __ATTRIBUTE_INFO */

// END OF FILE

