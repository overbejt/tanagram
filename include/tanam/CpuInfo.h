#ifndef _CPU_INFO
#define _CPU_INFO

#include "Tag.h"
#include "Tanam.h"
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

#endif /* _CPU_INFO */

// END OF FILE

