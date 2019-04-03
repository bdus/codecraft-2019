#pragma once
#include "utility/print.h"

//#define NDECHO //关闭echo
//#define NDEBUG //关闭断言
//#include <cassert>
#include <stdlib.h>

//#define assert(condition,msg) { if(!(condition)){ std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ")" << "\n" << msg << std::endl; } }

#define LOG(condition,format, ...) { if(!(condition)){ fprintf(stdout, format, ##__VA_ARGS__);  std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ")"  << std::endl;  } }
