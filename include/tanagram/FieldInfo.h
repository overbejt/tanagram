#ifndef __FIELD_INFO
#define __FIELD_INFO

#include "AccessFlag.h"
#include "AttributeInfo.h"
#include "Tanagram.h"
#include <iostream>
#include <utility>
#include <iomanip>

using Attributes = std::vector<AttributeInfo>;

class FieldInfo {
  public:
    FieldInfo(
        AccessFlag accessFlags,
        u2 nameIndex,
        u2 descriptorIndex,
        u2 attributesCount,
        Attributes attributes)
        : accessFlags(accessFlags),
          nameIndex(nameIndex),
          descriptorIndex(descriptorIndex),
          attributesCount(attributesCount),
          attributes(std::move(attributes)) { };
    AccessFlag accessFlags; // u2
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributesCount;
    Attributes attributes;
    friend std::ostream& operator<<(std::ostream &os, const FieldInfo &current);
};

using Fields = std::vector<FieldInfo>;

inline std::ostream& operator<<(std::ostream &os, const FieldInfo &current) {
  os << "{ accessFlags: " << current.accessFlags;
  os << ", nameIndex: 0x";
  os << std::setfill('0') << std::setw(4) << std::hex;
  os << current.nameIndex << ", descriptorIndex: 0x";
  os << current.descriptorIndex << ", attributesCount: 0x";
  os << current.attributesCount << ", attributes: [ ";
  for (const auto& a : current.attributes) {
    os << a << ", ";
  }
  os << " ] }" << std::dec;
  return os;
};

#endif /* __FIELD_INFO */

// END OF FILE

