#include "tanagram/ClassFile.h"
#include <stdexcept>

ClassFile::ClassFile() {
}  // End of the 'ClassFile' Constructor

ClassFile::ClassFile(const std::string& classFilePath) {
  readClassFile(classFilePath);
  initFromBuffer();
}  // End of the 'ClassFile' overloaded Constructor

void ClassFile::processFile(const std::string& classFilePath) {
  readClassFile(classFilePath);
  initFromBuffer();
}  // End of the 'process_file' function

bool ClassFile::initFromBuffer() {
  bufferIdx = 0;
  try {
    magic = readWord();
    minorVersion = readHalfWord();
    majorVersion = readHalfWord();
    constantPoolCount = readHalfWord();
    setConstantPool();
    accessFlags = readHalfWord();
    thisClass = readHalfWord();
    superClass = readHalfWord();
    interfacesCount = readHalfWord();
    setInterfaces();
    fieldsCount = readHalfWord();
    setFields();
    methodsCount = readHalfWord();
    setMethods();
    attributesCount = readHalfWord();
    setAttributes();
    return true;
  } catch (const ReadOverflowException& e) {
    std::cerr << "Read Error: " << e.what() << std::endl;
    return false;
  } 
  // catch (const std::exception& e) {
  //   std::cerr << "aww crap!\n" << e.what() << std::endl;
  //   return false;
  // } 
}  // End of the 'initFromBuffer' function

void ClassFile::readClassFile(const std::string &classFilePath) {
 std::cout << "Processing " << classFilePath << std::endl;

 std::ifstream file(classFilePath, std::ios::binary);
 if (!file.is_open()) {
   std::cerr << "Failed to open: " << classFilePath << std::endl;
   return;  // TODO escape early
 }

 buffer.assign(
     std::istreambuf_iterator<char>(file),
     std::istreambuf_iterator<char>()
 );
 std::cout << "Read " << buffer.size() << " bytes" << std::endl;
 file.close();

 return;
}  // End of the 'readClassFile' function

/**
 * Boo-yah
 */
void ClassFile::setConstantPool() {
  // It's constantPoolCount - 1 according to the spec
  for (size_t cpuInfoIdx = 0; cpuInfoIdx < (size_t)(constantPoolCount - 1); cpuInfoIdx++) {
    Tag tag = (Tag)buffer.at(bufferIdx++);
    switch (tag) {
      case Tag::CONSTANT_Class: {
        uint32_t nameIndex = readHalfWord();
        ConstantClassInfo entry(tag, nameIndex);
        EntryPtr objPtr = std::make_unique<ConstantClassInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_Fieldref: {
        uint32_t classIndex = readHalfWord();
        uint32_t nameAndTypeIndex = readHalfWord();
        ConstantFieldrefInfo entry(
            tag, classIndex, nameAndTypeIndex);
        EntryPtr objPtr = std::make_unique<ConstantFieldrefInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_Methodref: {
        uint32_t classIndex = readHalfWord();
        uint32_t nameAndTypeIndex = readHalfWord();
        ConstantMethodrefInfo entry(
            tag, classIndex, nameAndTypeIndex);
        EntryPtr objPtr = std::make_unique<ConstantMethodrefInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_InterfaceMethodref: {
        uint32_t classIndex = readHalfWord();
        uint32_t nameAndTypeIndex = readHalfWord();
        ConstantInterfaceMethodrefInfo entry(
            tag, classIndex, nameAndTypeIndex);
        EntryPtr objPtr = std::make_unique<ConstantInterfaceMethodrefInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_String: {
        uint32_t stringIndex = readHalfWord();
        ConstantStringInfo entry(tag, stringIndex);
        EntryPtr objPtr = std::make_unique<ConstantStringInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_Integer: {
        uint32_t bytes = readWord();
        ConstantIntegerInfo entry(tag, bytes);
        EntryPtr objPtr = std::make_unique<ConstantIntegerInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_Float: {
        uint32_t bytes = readWord();
        ConstantFloatInfo entry(tag, bytes);
        EntryPtr objPtr = std::make_unique<ConstantFloatInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_Long: {
        uint32_t highBytes = readWord();
        uint32_t lowBytes = readWord();
        ConstantLongInfo entry(tag, highBytes, lowBytes);
        EntryPtr objPtr = std::make_unique<ConstantLongInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_Double: {
        uint32_t highBytes = readWord();
        uint32_t lowBytes = readWord();
        ConstantDoubleInfo entry(tag, highBytes, lowBytes);
        EntryPtr objPtr = std::make_unique<ConstantDoubleInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_NameAndType: {
        uint32_t nameIndex = readHalfWord();
        uint32_t descriptorIndex = readHalfWord();
        ConstantNameAndTypeInfo entry(tag, nameIndex, descriptorIndex);
        EntryPtr objPtr = std::make_unique<ConstantNameAndTypeInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_Utf8: {
        uint32_t length = readHalfWord();
        std::vector<u1> bytes;
        for (uint32_t i = 0; i < length; i++) {
          u1 byte = buffer.at(bufferIdx++);
          bytes.push_back(byte);
        }
        ConstantUtf8Info entry(tag, length, std::move(bytes));
        EntryPtr objPtr = std::make_unique<ConstantUtf8Info>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_MethodHandle: {
        u1 referenceKind = buffer.at(bufferIdx++);
        uint32_t referenceIndex = readHalfWord();
        ConstantMethodHandleInfo entry(tag, referenceKind, referenceIndex);
        EntryPtr objPtr = std::make_unique<ConstantMethodHandleInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_MethodType: {
        uint32_t description = readHalfWord();
        ConstantMethodTypeInfo entry(tag, description);
        EntryPtr objPtr = std::make_unique<ConstantMethodTypeInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      case Tag::CONSTANT_InvokeDynamic: {
        uint32_t descriptorIndex = readHalfWord();
        ConstantInvokeDynamicInfo entry(tag, descriptorIndex);
        EntryPtr objPtr = std::make_unique<ConstantInvokeDynamicInfo>(entry);
        constantPool.push_back(std::move(objPtr));
        break;
      }
      default: {
        std::cout << "{ i: " << cpuInfoIdx << " tag: 0x";
        std::cout << std::setfill('0') << std::setw(2) << std::hex;
        std::cout << (uint32_t)tag << std::dec;
        std::cout << ", bufferIdx: " << bufferIdx;
        std::cout << " }"<< std::endl;
        break;
      }
    }
  }
}  // End of the 'setConstantPool' function

void ClassFile::setInterfaces() {
  for (size_t i = 0; i < interfacesCount; i++) {
    uint32_t interfaceIndex = readHalfWord();
    interfaces.push_back(interfaceIndex);
  }
}  // End of the 'setInterfaces' function

void ClassFile::setFields() {
  for (size_t f = 0; f < fieldsCount; f++) {
    AccessFlag accessFlags = (AccessFlag)readHalfWord();
    uint32_t nameIndex = readHalfWord();
    uint32_t descriptorIndex = readHalfWord();
    uint32_t attributesCount = readHalfWord();
    Attributes attributes;
    for (size_t i = 0; i < attributesCount; i++) {
      uint32_t attributeNameIndex = readHalfWord();
      uint32_t attributeLength = readWord();
      Infos info;
      for (size_t i = 0; i < attributeLength; i++) {
        uint32_t byte = readByte();
        info.push_back(byte);
      }
      AttributeInfo attributeInfo(
          attributeNameIndex, attributeLength, std::move(info));
      attributes.push_back(attributeInfo);
    }
    FieldInfo fieldInfo(
        accessFlags, nameIndex, descriptorIndex, 
        attributesCount, std::move(attributes));
    fields.push_back(fieldInfo);
  }
}  // End of the 'setFields' function

void ClassFile::setMethods() {
  for (size_t m = 0; m < methodsCount; m++) {
    uint32_t accessFlags = readHalfWord();
    uint32_t nameIndex = readHalfWord();
    uint32_t descriptorIndex = readHalfWord();
    uint32_t attributesCount = readHalfWord();
    Attributes attributes;
    for (size_t a = 0; a < attributesCount; a++) {
      uint32_t attributeNameIndex = readHalfWord();
      uint32_t attributeLength = readWord();
      Infos infos;
      for (size_t i = 0; i < attributeLength; i++) {
        u1 byte = readByte();
        infos.push_back(byte);
      }
      AttributeInfo attribute(
          attributeNameIndex, attributeLength, std::move(infos));
      attributes.push_back(attribute);
    }
    MethodInfo method(
        accessFlags, nameIndex, descriptorIndex, 
        attributesCount, std::move(attributes));
    methods.push_back(method); 
  }
}  // End of the 'setMethods' function

void ClassFile::setAttributes() {
  for (size_t a = 0; a < attributesCount; a++) {
    uint32_t attributeNameIndex = readHalfWord();
    uint32_t attributeLength = readWord();
    Infos infos;
    for (size_t i = 0; i < attributeLength; i++) {
      u1 byte = readByte();
      infos.push_back(byte);
    }
    AttributeInfo attribute(
        attributeNameIndex, 
        attributeLength, 
        std::move(infos));
    attributes.push_back(attribute);
  }
}  // End of the 'setAttributes' function

uint32_t ClassFile::readByte() {
  if (bufferIdx > buffer.size()) {
    throw ReadOverflowException("readByte exceedes buffer size");
  }
  uint32_t byte = (uint32_t)buffer.at(bufferIdx++);
  return byte;
}  // End of the 'readByte' function

uint32_t ClassFile::readHalfWord() {
  if (bufferIdx + 2 > buffer.size()) {
    throw ReadOverflowException("readHalfWord exceedes buffer size");
  }
  uint32_t upper = (uint32_t)buffer.at(bufferIdx++);
  uint32_t lower = (uint32_t)buffer.at(bufferIdx++);
  uint32_t halfWord = (upper << 8) | lower;
  return halfWord;
}  // End of the 'readHalfWord' function

uint32_t ClassFile::readWord() {
  if (bufferIdx + 4 > buffer.size()) {
    throw ReadOverflowException("readWord exceeds buffer size");
  }
  uint32_t upperHigh = (uint32_t)buffer.at(bufferIdx++);
  uint32_t lowerHigh = (uint32_t)buffer.at(bufferIdx++);
  uint32_t upperLow = (uint32_t)buffer.at(bufferIdx++);
  uint32_t lowerLow = (uint32_t)buffer.at(bufferIdx++);
  uint32_t word = (upperHigh << 24) | 
                  (lowerHigh << 16) | 
                  (upperLow  << 8)  | 
                  lowerLow;
  return word;
}  // End of the 'readWord' function

std::ostream& operator<<(std::ostream &os, const ClassFile &clazz) {
  os << "ClassFile {\n";
  os << "  magic: 0x" << std::hex << clazz.magic << std::dec << ",\n";
  
  os << "  minor version: 0x";
  os << std::setfill('0') << std::setw(4) << std::hex;
  os << clazz.minorVersion << ",\n";
  
  os << "  major version: 0x";
  os << std::setfill('0') << std::setw(4) << std::hex;
  os << clazz.majorVersion << ",\n";
  
  os << "  constant pool count: 0x";
  os << std::setfill('0') << std::setw(4) << std::hex;
  os << clazz.constantPoolCount << ",\n";
  
  os << "  constantPool.size(): 0x";
  os << std::setfill('0') << std::setw(4) << std::hex;
  os << clazz.constantPool.size() << ",\n";

  os << "  constantPool: [";
  if (clazz.constantPool.size() == 0) {
    os << "],\n";
  } else {
    os << "\n";
    for (const auto& cur_cpu_info : clazz.constantPool) {
      os << "    " << cur_cpu_info << ",\n";
    }
    os << "  ]\n";
  }

  os << "  accessFlags: 0x";
  os << std::setfill('0') << std::setw(4) << std::hex;
  os << clazz.accessFlags << std::dec << ",\n";

  os << "  thisClass: 0x";
  os << std::setfill('0') << std::setw(2) << std::hex;
  os << clazz.thisClass << std::dec << ",\n";

  os << "  superClass: 0x";
  os << std::setfill('0') << std::setw(2) << std::hex;
  os << clazz.superClass << std::dec << ",\n";

  os << "  interfacesCount: 0x";
  os << std::setfill('0') << std::setw(2) << std::hex;
  os << clazz.interfacesCount << std::dec << ",\n";

  os << "  interfaces: [";
  if (clazz.interfaces.size() == 0) {
    os << "],\n"; 
  } else {
    os << "\n"; 
    for (const auto& i : clazz.interfaces) {
      os << "    " << i << ", ";
    }
    os << "  ],\n";
  }

  os << "  fieldsCount: 0x";
  os << std::setfill('0') << std::setw(2) << std::hex;
  os << clazz.fieldsCount << std::dec << ",\n";

  os << "  fields: [";
  if (clazz.fields.size() == 0) {
    os << "],\n";
  } else {
    os << "\n";
    for (const auto& f : clazz.fields) {
      os << f << ",\n";
    }
    os << "  ],\n";
  }

  os << "  methodsCount: 0x";
  os << std::setfill('0') << std::setw(2) << std::hex;
  os << clazz.methodsCount << std::dec << ",\n";

  os << "  methods: [";
  if (clazz.methods.size() == 0) {
    os << "],\n";
  } else {
    os << "\n";
    for (const auto& m : clazz.methods) {
      os << "    " << m << ",\n";
    }
    os << "  ]\n";
  }

  os << "  attributesCount: 0x";
  os << std::setfill('0') << std::setw(2) << std::hex;
  os << clazz.attributesCount << std::dec << ",\n";

  // TODO Implement print for ClassFile.attributes
  os << "  attributes: [";
  if (clazz.attributes.size() == 0) {
    os << "]\n";
  } else {
    os << "\n";
    for (const auto& a : clazz.attributes) {
      os << "    " << a << ",\n";
    }
    os << "  ]\n";
  }

  os << "}\n";
  return os;
}  // End of the 'operator<<' function

void ClassFile::hexDump() {
  int i = 0;
  std::cout << std::hex;
  std::cout << std::setfill(' ') << std::setw(4) << i << ": ";
  for (const auto c : buffer) {
    if (i % 16 == 0 && i != 0) {
      std::cout << std::endl << std::setfill(' ') << std::setw(4) << i << ": ";
    }
    if (i % 4 == 0 && i != 0 && i % 16 != 0) {
      std::cout << ' ';
    }
    uint32_t val = c;
    std::cout << std::setfill('0') << std::setw(2) << val;
    i++;
  }
  std::cout << std::dec << std::endl << std::endl;
}  // End of the 'hex_dump' function

// END OF FILE

