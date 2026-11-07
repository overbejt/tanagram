#ifndef __CPU_INFO
#define __CPU_INFO

#include "Tag.h"
#include "Tanagram.h"
#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

class CpuInfo {
  public:
    Tag tag;
    u1 tag_raw;
    std::vector<u1> info;
    CpuInfo();
    int getInfoSize() const;
    friend std::ostream& operator<<(std::ostream &os, const CpuInfo &cpu_info);
};

#endif /* __CPU_INFO */

// END OF FILE

