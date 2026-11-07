/**
 * Spec located at: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html
 */
#ifndef __CLASS_FILE_H
#define __CLASS_FILE_H

#include "AccessFlag.h"
#include "AttributeInfo.h"
#include "ConstantPoolEntry.h"
#include "CpuInfo.h"
#include "FieldInfo.h"
#include "MethodInfo.h"
#include "ReadOverflow.h"
#include "Tag.h"
#include "Tanagram.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <optional>
#include <iomanip>
#include <utility>
#include <memory>
#include <string>
#include <fstream>

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
    bool initFromBuffer();
    void readClassFile(const std::string &classFilePath);
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
    ClassFile(const std::string& classFilePath);
    void hexDump();
    void processFile(const std::string& classFilePath);
    friend std::ostream& operator<<(std::ostream &os, const ClassFile &clazz);
};

#endif /* __CLASS_FILE_H */

// END OF FILE

