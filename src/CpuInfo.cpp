#include "tanam/CpuInfo.h"

CpuInfo::CpuInfo() { }

int CpuInfo::getInfoSize() const {
  switch (tag) {
    case Tag::CONSTANT_Class: return 3;
    case Tag::CONSTANT_Fieldref: return 5;
    case Tag::CONSTANT_Methodref: return 5;
    case Tag::CONSTANT_InterfaceMethodref: return 5;
    case Tag::CONSTANT_String: return 3;
    case Tag::CONSTANT_Integer: return 5;
    case Tag::CONSTANT_Float: return 5;
    case Tag::CONSTANT_Long: return 9;
    case Tag::CONSTANT_Double: return 9;
    case Tag::CONSTANT_NameAndType: return 5;
    case Tag::CONSTANT_Utf8: return 4;
    case Tag::CONSTANT_MethodHandle: return 4;
    case Tag::CONSTANT_MethodType: return 3;
    case Tag::CONSTANT_InvokeDynamic: return 5;
    default: return 0;
  }
}  // End of the 'getInfoSize' function

std::ostream& operator<<(std::ostream &os, const CpuInfo &cpu_info) {
  os << "{ " << cpu_info.tag << ", ";
  os << "0x" << std::setfill('0') << std::setw(2);
  os << std::hex << (uint32_t)cpu_info.tag << std::dec;
  os << ", ";
  os << "0x" << std::setfill('0') << std::setw(2);
  os << std::hex << (uint32_t)cpu_info.getInfoSize() << std::dec;
  os << " }";
  return os;
}  // End of the overloaded << operator for the CpuInfo class

// END OF FILE

