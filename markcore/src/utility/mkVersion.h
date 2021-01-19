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

#ifndef __mkVersion
#define __mkVersion

class MK_DLL_EXPORT mkVersion
{
public:
    mkVersion(unsigned int major, unsigned int minor, unsigned int patch);
    mkVersion(unsigned int version);
    
    const unsigned int& Get() const;
    unsigned int GetMajor() const;
    unsigned int GetMinor() const;
    unsigned int GetPatch() const;
    int Compare(const unsigned int& target) const;
    int Compare(const mkVersion& target) const;
    
private:
    const unsigned int _version;
};

#endif