#pragma once
#include "utility/print.h"

//#define _ECHOOFF
//#define NDECHO //关闭echo
//#define NDEBUG //关闭断言
#include <cassert>
#include <stdlib.h>


#define LOG(condition,format, ...) { if(!(condition)){ fprintf(stdout, format, ##__VA_ARGS__);  std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ")"  << std::endl;  } }
