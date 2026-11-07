#ifndef _TAG
#define _TAG

#include <iostream>
#include <utility>

enum class Tag {
  CONSTANT_Class              = 7,
  CONSTANT_Fieldref           = 9,
  CONSTANT_Methodref          = 10,
  CONSTANT_InterfaceMethodref = 11,
  CONSTANT_String             = 8,
  CONSTANT_Integer            = 3,
  CONSTANT_Float              = 4,
  CONSTANT_Long               = 5,
  CONSTANT_Double             = 6,
  CONSTANT_NameAndType        = 12,
  CONSTANT_Utf8               = 1,
  CONSTANT_MethodHandle       = 15,
  CONSTANT_MethodType         = 16,
  CONSTANT_InvokeDynamic      = 18
};

inline std::ostream& operator<<(std::ostream &os, const Tag &tag) {
  switch (tag) {
    case Tag::CONSTANT_Class: return os << "CONSTANT_Class";
    case Tag::CONSTANT_Fieldref: return os << "CONSTANT_Fieldref";
    case Tag::CONSTANT_Methodref: return os << "CONSTANT_Methodref";
    case Tag::CONSTANT_InterfaceMethodref: return os << "CONSTANT_InterfaceMethodref";
    case Tag::CONSTANT_String: return os << "CONSTANT_String";
    case Tag::CONSTANT_Integer: return os << "CONSTANT_Integer";
    case Tag::CONSTANT_Float: return os << "CONSTANT_Float";
    case Tag::CONSTANT_Long: return os << "CONSTANT_Long";
    case Tag::CONSTANT_Double: return os << "CONSTANT_Double";
    case Tag::CONSTANT_NameAndType: return os << "CONSTANT_NameAndType";
    case Tag::CONSTANT_Utf8: return os << "CONSTANT_Utf8";
    case Tag::CONSTANT_MethodHandle: return os << "CONSTANT_MethodHandle";
    case Tag::CONSTANT_MethodType: return os << "CONSTANT_MethodType";
    case Tag::CONSTANT_InvokeDynamic: return os << "CONSTANT_InvokeDynamic";
    default: return os << "UNKNOWN";
  }
};  // End of the overloaded << operator for the Tag class

#endif /* _TAG */

// END OF FILE

