#ifndef __METHOD_INFO
#define __METHOD_INFO

#include "AttributeInfo.h"
#include "Tanagram.h"
#include <iostream>
#include <iomanip>
#include <memory>

class MethodInfo {
  public:
    MethodInfo(
        u2 accessFlags, 
        u2 nameIndex, 
        u2 descriptorIndex, 
        u2 attributesCount, 
        Attributes attributes) : 
        accessFlags(accessFlags), 
        nameIndex(nameIndex), 
        descriptorIndex(descriptorIndex), 
        attributesCount(attributesCount), 
        attributes(std::move(attributes)) { };
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributesCount;
    Attributes attributes;
    friend std::ostream& operator<<(std::ostream &os, const MethodInfo &current);
};

using Methods = std::vector<MethodInfo>;

inline std::ostream& operator<<(std::ostream &os, const MethodInfo &current) {
  Padding padding{6};
  os << "{\n";
  os << padding << "accessFlags: 0x";
  os << std::setfill('0') << std::setw(4) << std::hex;
  os << current.accessFlags << ",\n";
  os << padding << "nameIndex: 0x";
  os << current.nameIndex << ",\n";
  os << padding << "descriptorIndex: 0x";
  os << current.descriptorIndex << ",\n";
  os << padding << "attributesCount: 0x";
  os << current.attributesCount << ",\n";
  os << padding << "attributes: [";
  if (current.attributes.size() == 0) {
    os << "]\n";
  } else {
    os << "\n";
    padding.pad += 2;
    for (const auto& a : current.attributes) {
      // Nested AttributeInfo list manually expanded for padding
      // Going to have to go hands on here
      os << padding << "{\n";
      padding.pad += 2;
      os << padding << "attributeNameIndex: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << a.attributeNameIndex << ", \n";
      os << padding << "attributeLength: 0x";
      os << a.attributeLength << std::setw(2) << "\n";
      os << padding << "info: [ ";
      if (a.info.size() == 0) {
        os << "]\n";
      } else {
        for (const auto& i : a.info) {
          os << std::setfill('0') << std::setw(2) << std::hex;
          os << (uint32_t)i << ", ";
        }
        os << std::dec << " ]\n";
      }
      padding.pad -= 2;
      os << padding << "}\n";
      // End of the nested AttributeInfo list
    }
    padding.pad -= 2;
    os << padding << "]\n" << std::dec;
  }
  padding.pad -= 2;
  os << padding << "}";
  return os;
};

#endif /* __METHOD_INFO */

// END OF FILE

