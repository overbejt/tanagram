#ifndef __ACCESS_FLAG
#define __ACCESS_FLAG

#include <iostream>
#include <utility>

enum class AccessFlag {
  ACC_PUBLIC    = 0x0001, /* Declared public; may be accessed from outside its package. */
  ACC_PRIVATE   = 0x0002, /* Declared private; usable only within the defining class. */
  ACC_PROTECTED = 0x0004, /* Declared protected; may be accessed within subclasses. */
  ACC_STATIC    = 0x0008, /* Declared protected; may be accessed within subclasses. */
  ACC_FINAL     = 0x0010, /* Declared final; never directly assigned to after object construction */
  ACC_VOLATILE  = 0x0040, /* Declared volatile; cannot be cached. */
  ACC_TRANSIENT = 0x0080, /* Declared transient; not written or read by a persistent object manager. */
  ACC_SYNTHETIC = 0x1000, /* Declared synthetic; not present in the source code. */
  ACC_ENUM      = 0x4000  /* Declared as an element of an enum. */
};

inline std::ostream& operator<<(std::ostream &os, const AccessFlag &flag) {
  switch (flag) {
    case AccessFlag::ACC_PUBLIC: return os << "ACC_PUBLIC";
    case AccessFlag::ACC_PRIVATE: return os << "ACC_PRIVATE";
    case AccessFlag::ACC_PROTECTED: return os << "ACC_PROTECTED";
    case AccessFlag::ACC_STATIC: return os << "ACC_STATIC";
    case AccessFlag::ACC_FINAL: return os << "ACC_FINAL";
    case AccessFlag::ACC_VOLATILE: return os << "ACC_VOLATILE";
    case AccessFlag::ACC_TRANSIENT: return os << "ACC_TRANSIENT";
    case AccessFlag::ACC_SYNTHETIC: return os << "ACC_SYNTHETIC";
    case AccessFlag::ACC_ENUM: return os << "ACC_ENUM";
    default: return os << "UNKNOWN";
  }
};  // End of the overloaded << operator for the Tag class

#endif /* __ACCESS_FLAG */

// END OF FILE

