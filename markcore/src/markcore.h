﻿/***************************************************************************************************
LICENSE:
    Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
Author:liu.hao(33852613@163.com)
   
Time:2017-6

info:

***************************************************************************************************/

#ifndef __markcore
#define __markcore

//common
#include "mkheaders.h"

//3rdparty
#include "3rdparty/string_utils/string_utility.hpp"
//#include "3rdparty/string_utils/string_convert.hpp"
#include "3rdparty/cpptoml/cpptoml.h"

//utility
#include "utility/mkFormat.h"
#include "utility/mkString.h"
#include "utility/mkException.h"
#include "utility/mkTypeCast.h"
#include "utility/mkTrace.h"
#include "utility/mkLog.h"
#include "utility/mkOptionSwitch.h"
#include "utility/mkUniqueProfilePoint.h"

//print
#include "print/mkTablePrinter.h"
#include "print/mkLinenoise.h"

//thread
#include "thread/mkUniqueThread.h"
#include "thread/mkAddTimeoutForFunc.h"

//module
#include "module/mkModuleInstance.h"

#endif // __markcore
