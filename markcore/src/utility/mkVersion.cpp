/***************************************************************************************************
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

Time:2021-1

info:

***************************************************************************************************/

#include <mkheaders.h>
#include "mkVersion.h"

mkVersion::mkVersion(unsigned int major, unsigned int minor, unsigned int patch)
    : _version(((major&0x000000FF)<<24) | ((minor&0x00000FFF)<<12) | ((patch & 0x00000FFF)))
{
}

mkVersion::mkVersion(unsigned int version)
    : _version(version)
{
}

const unsigned int&
mkVersion::Get() const
{
    return _version;
}

unsigned int
mkVersion::GetMajor() const
{
    return ((_version >> 24) & 0x000000FF);
}

unsigned int
mkVersion::GetMinor() const
{
    return ((_version >> 12) & 0x00000FFF);
}

unsigned int 
mkVersion::GetPatch() const
{
    return (_version & 0x00000FFF);
}

int 
mkVersion::Compare(const unsigned int& target) const
{
    if (_version < target) {
        return -1;
    }
    else if (_version > target)  {
        return 1;
    }
    else {
        return 0;
    }
}

int 
mkVersion::Compare(const mkVersion& target) const
{
    return Compare(target.Get());
}
