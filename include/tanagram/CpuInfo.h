#ifndef __CONSTANT_POOL_ENTRY
#define __CONSTANT_POOL_ENTRY

#include "Tag.h"
#include "Tanagram.h"
#include <iostream>
#include <iomanip>
#include <memory>

/**
 * Interface for the ConstantPool classes
 */
class CpuInfo {
  public:
    virtual ~CpuInfo() = default;
    virtual Tag getTag() const = 0;
    virtual void print(std::ostream &os) const = 0;
};  // End of the 'CpuInfo' class

inline std::ostream& operator<<(std::ostream& os, const std::unique_ptr<CpuInfo> &entry) {
  if (entry) {
    entry->print(os);
  } else {
    os << " UNKNOWN\n";
  }
  return os;
};

class ConstantClassInfo : public CpuInfo {
  private:
    Tag tag;  // When reading use u1
    u2 nameIndex;  // TODO 
  public:
    ConstantClassInfo(Tag tag, u2 nameIndex) 
      : tag(tag), nameIndex(nameIndex) { };
    
    Tag getTag() const override { 
      return Tag::CONSTANT_Class;
    };  // End of the 'getTag' function
    
    u2 getNameIndex() const { 
      return nameIndex; 
    };  // End of the 'getNameIndex' function

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "nameIndex: 0x";
      os << std::setfill('0') << std::setw(4);
      os << std::hex << nameIndex << std::dec << "\n";
      padding.pad = 4; 
      os << padding << "}";
    };  // End of the 'print' function
};  // End of the 'ConstantClassInfo' class

class ConstantFieldrefInfo : public CpuInfo {
  private:
    Tag tag;  // When reading use u1
    u2 classIndex;
    u2 nameAndTypeIndex;  // TODO Probably going to be an enum
  public:
    ConstantFieldrefInfo(Tag tag, u2 classIndex, u2 nameAndTypeIndex) 
      : tag(tag), classIndex(classIndex), nameAndTypeIndex(nameAndTypeIndex){ };

    Tag getTag() const override {
      return Tag::CONSTANT_Fieldref;
    };

    u2 getClassIndex() const {
      return classIndex;
    };

    u2 getNameAndTypeIndex() const {
      return nameAndTypeIndex;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "classIndex: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << classIndex << ",\n";
      os << padding << "nameAndTypeIndex: 0x";
      os << nameAndTypeIndex << std::dec;
      os << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantFieldrefInfo' class

class ConstantMethodrefInfo : public CpuInfo {
  private:
    Tag tag;  // When reading use u1
    u2 classIndex;
    u2 nameAndTypeIndex;

  public:
    ConstantMethodrefInfo(Tag tag, u2 classIndex, u2 nameAndTypeIndex) 
      : tag(tag), classIndex(classIndex), nameAndTypeIndex(nameAndTypeIndex) { };
    
    Tag getTag() const override {
      return Tag::CONSTANT_Methodref;
    };

    u2 getClassIndex() const {
      return classIndex;
    };

    u2 getNameAndTypeIndex() const {
      return nameAndTypeIndex;
    };


    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n"; 
      os << padding << "classIndex: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << classIndex << ",\n";
      os << padding << "nameAndTypeIndex: 0x";
      os << std::setfill('0') << std::setw(4) << "" << std::hex;
      os << nameAndTypeIndex << std::dec << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantMethodrefInfo' class

class ConstantInterfaceMethodrefInfo : public CpuInfo {
  private:
    Tag tag;  // When reading use u1
    u2 classIndex;
    u2 nameAndTypeIndex;

  public:
    ConstantInterfaceMethodrefInfo(Tag tag, u2 classIndex, u2 nameAndTypeIndex) 
      : tag(tag), classIndex(classIndex), nameAndTypeIndex(nameAndTypeIndex) { };

    Tag getTag() const override {
      return Tag::CONSTANT_InterfaceMethodref;
    };

    u2 getClassIndex() const {
      return classIndex;
    };

    u2 getNameAndTypeIndex() {
      return nameAndTypeIndex;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "classIndex: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << classIndex << ",\n"; 
      os << padding << "nameAndTypeIndex: 0x" << nameAndTypeIndex;
      os << std::dec << "\n  }";
    };
};  // End of the 'ConstantInterfaceMethodrefInfo' class

class ConstantStringInfo : public CpuInfo {
  private:
    Tag tag;  // When reading use u1
    u2 stringIndex;

  public:
    ConstantStringInfo(Tag tag, u2 stringIndex) 
      : tag(tag), stringIndex(stringIndex) { };

    Tag getTag() const override {
      return Tag::CONSTANT_String;
    };

    u2 getStringIndex() {
      return stringIndex;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "stringIndex: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      padding.pad = 4; 
      os << stringIndex << std::dec << "\n";
      os << padding << "}";
    };
};  // End of the 'ConstantStringInfo' class

class ConstantIntegerInfo : public CpuInfo {
  private:
    Tag tag;  // When reading use u1
    u4 bytes;

  public:
    ConstantIntegerInfo(Tag tag, u4 bytes) 
      : tag(tag), bytes(bytes) { };

    Tag getTag() const override {
      return Tag::CONSTANT_Integer;
    };

    u4 getBytes() {
      return bytes;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "bytes: 0x";
      os << std::setfill('0') << std::setw(8) << std::hex;
      os << bytes << std::dec << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantIntegerInfo' class

class ConstantFloatInfo : public CpuInfo {
  private:
    Tag tag;  // When reading use u1
    u4 bytes;

  public:
    ConstantFloatInfo(Tag tag, u4 bytes) 
      : tag(tag), bytes(bytes) { };
    
    Tag getTag() const override {
      return Tag::CONSTANT_Float;
    };

    u4 getBytes() {
      return bytes;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "bytes: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << bytes << std::dec << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantFloatInfo' class

class ConstantLongInfo : public CpuInfo {
  private:
    Tag tag;  // When reading use u1
    u4 highBytes;
    u4 lowBytes;
  
  public:
    ConstantLongInfo(Tag tag, u4 highBytes, u4 lowBytes) 
      : tag(tag), highBytes(highBytes), lowBytes(lowBytes) { };

    Tag getTag() const override {
      return Tag::CONSTANT_Long;
    };

    u4 getHighBytes() {
      return highBytes;
    };

    u4 getLowBytes() {
      return lowBytes;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "highBytes: 0x";
      os << std::setfill('0') << std::setw(8) << std::hex;
      os << highBytes << ",\n";
      os << padding << "lowBytes: 0x" << lowBytes;
      os << std::dec << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantLongInfo' class

class ConstantDoubleInfo : public CpuInfo {
  private:
    Tag tag;  // Use u1 when reading
    u4 highBytes;
    u4 lowBytes;

  public:
    ConstantDoubleInfo(Tag tag, u4 highBytes, u4 lowBytes) 
      : tag(tag), highBytes(highBytes), lowBytes(lowBytes) { };

    Tag getTag() const override {
      return Tag::CONSTANT_Double;
    };

    u4 getHighBytes() {
      return highBytes;
    };

    u4 getLowBytes() {
      return lowBytes;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "highBytes: 0x";
      os << std::setfill('0') << std::setw(8) << std::hex;
      os << highBytes << ",\n";
      os << padding << "lowBytes: 0x" << lowBytes;
      os << std::dec << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantDoubleInfo' class

class ConstantNameAndTypeInfo : public CpuInfo {
  private:
    Tag tag;  // Use u1 when reading
    u2 nameIndex;
    u2 descriptorIndex;

  public:
    ConstantNameAndTypeInfo(Tag tag, u2 nameIndex, u2 descriptorIndex) 
      : tag(tag), nameIndex(nameIndex), descriptorIndex(descriptorIndex) { };
    
    Tag getTag() const override {
      return Tag::CONSTANT_NameAndType;
    };

    u2 getnameIndex() {
      return nameIndex;
    };

    u2 getDescriptorIndex() {
      return descriptorIndex;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "nameIndex: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << nameIndex << ",\n";
      os << padding << "descriptorIndex: 0x";
      os << descriptorIndex << std::dec << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantNameAndTypeInfo' class

class ConstantUtf8Info : public CpuInfo {
  private:
    Tag tag;  // Use u1 when reading
    u2 length;
    std::vector<u1> bytes;

  public:
    ConstantUtf8Info(Tag tag, u2 length, std::vector<u1> bytes) 
      : tag(tag), length(length), bytes(std::move(bytes)) { };
    
    Tag getTag() const override {
      return Tag::CONSTANT_Utf8;
    };

    u2 getLength() {
      return length;
    };

    // TODO I don't like this.  Rather have it be a public member var and just operate on it directly
    std::vector<u1> getBytes() {
      return bytes;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "length: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << length << ",\n";
      os << padding << "bytes: [ ";
      for (const auto b : bytes) {
        os << b << ", ";
      }
      os << std::dec << " ]\n";
      padding.pad = 4;
      os << padding << "}";
    };
};

class ConstantMethodHandleInfo : public CpuInfo {
  private:
    Tag tag;  // Use u1 when reading
    u1 referenceKind;
    u2 referenceIndex;

  public:
    ConstantMethodHandleInfo(Tag tag, u1 referenceKind, u2 referenceIndex) 
      : tag(tag), referenceKind(referenceKind), referenceIndex(referenceIndex) { };

    Tag getTag() const override {
      return Tag::CONSTANT_MethodHandle;
    };

    u1 getReferenceKind() {
      return referenceKind;
    };

    u2 getReferenceIndex() {
      return referenceIndex;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "referenceKind: 0x";
      os << std::setfill('0') << std::setw(2) << std::hex;
      os << referenceKind << ",\n";
      os << padding << "referenceIndex: 0x";
      os << std::setw(4) << referenceIndex << std::dec;
      os << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantMethodHandleInfo' class

class ConstantMethodTypeInfo : public CpuInfo {
  private:
    Tag tag;  // Use u1 when reading
    u2 description;

  public:
    ConstantMethodTypeInfo(Tag tag, u2 description) 
      : tag(tag), description(description) { };

    Tag getTag() const override {
      return Tag::CONSTANT_MethodType;
    };

    u2 getDescription() {
      return description;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "description: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << description << std::dec << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantMethodTypeInfo' class

class ConstantInvokeDynamicInfo : public CpuInfo {
  private:
    Tag tag;  // Use u1 when reading
    u2 descriptorIndex;

  public:
    ConstantInvokeDynamicInfo(Tag tag, u2 descriptorIndex) 
      : tag(tag), descriptorIndex(descriptorIndex) { };
    
    Tag getTag() const override {
      return Tag::CONSTANT_InvokeDynamic;
    };

    u2 getDescriptorIndex() {
      return descriptorIndex;
    };

    void print(std::ostream& os) const override {
      Padding padding{6};
      os << "{\n";
      os << padding << "tag: " << tag << ",\n";
      os << padding << "descriptorIndex: 0x";
      os << std::setfill('0') << std::setw(4) << std::hex;
      os << descriptorIndex << std::dec << "\n";
      padding.pad = 4;
      os << padding << "}";
    };
};  // End of the 'ConstantInvokeDynamicInfo' class

#endif /* __CONSTANT_POOL_ENTRY */

// END OF FILE

