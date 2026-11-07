/**
 * Spec located at: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html
 */
#ifndef _CLASS_FILE_H
#define _CLASS_FILE_H

#include "AccessFlag.h"
#include "AttributeInfo.h"
#include "ConstantPoolEntry.h"
#include "CpuInfo.h"
#include "FieldInfo.h"
#include "MethodInfo.h"
#include "ReadOverflow.h"
#include "Tag.h"
#include "Tanam.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <optional>
#include <iomanip>
#include <utility>
#include <memory>

using rawFile = std::vector<uint8_t>;
using Entry = ConstantPoolEntry;
using EntryPtr = std::unique_ptr<Entry>;
using ConstantPool = std::vector<EntryPtr>;

class ClassFile {
  private:
    rawFile buffer;
    size_t bufferIdx;
    uint32_t readByte();
    uint32_t readHalfWord();
    uint32_t readWord();
    void setAttributes();
    void setConstantPool();
    void setFields();
    void setInterfaces();
    void setMethods();
  
  public:
    u4 magic;
    u2 minorVersion;
    u2 majorVersion;
    u2 constantPoolCount;

    // size is constant_pool_count - 1
    ConstantPool constantPool;

    u2 accessFlags;
    u2 thisClass;
    u2 superClass;
    u2 interfacesCount;
    
    // size is interface_count
    std::vector<u2> interfaces; // vector of indicies in constantPool.  
                                // Must point to ConstantClassInfo instance
    // Interfaces interfaces;
    u2 fieldsCount;
    Fields fields;
    u2 methodsCount;
    Methods methods;
    u2 attributesCount;
    Attributes attributes;
    ClassFile();
    ClassFile(rawFile buffer);
    bool initFromBuffer();
    void hex_dump();
    void setBuffer(rawFile buffer);
    friend std::ostream& operator<<(std::ostream &os, const ClassFile &clazz);
};

#endif /* _CLASS_FILE_H */

// END OF FILE

