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
#include <sstream>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include"mkBase64.h"



bool 
mkBase64::Base64Encode(const std::string& input, std::string* output) 
{
	typedef boost::archive::iterators::base64_from_binary<
        boost::archive::iterators::transform_width<string::const_iterator, 6, 8> > Base64EncodeIterator;
	stringstream result;
	copy(Base64EncodeIterator(input.begin()), Base64EncodeIterator(input.end()), ostream_iterator<char>(result));
	size_t equal_count = (3 - input.length() % 3) % 3;
	for (size_t i = 0; i < equal_count; i++) {
		result.put('=');
	}
	*output = result.str();
	return output->empty() == false;
}
 
bool 
mkBase64::Base64Decode(const std::string& input, std::string* output) 
{
	typedef boost::archive::iterators::transform_width<
        boost::archive::iterators::binary_from_base64<std::string::const_iterator>, 8, 6> Base64DecodeIterator;
	std::stringstream result;
	try {
		copy(Base64DecodeIterator(input.begin()), Base64DecodeIterator(input.end()), ostream_iterator<char>(result));
	}
	catch (...) {
		return false;
	}
	*output = result.str();
	return output->empty() == false;
}