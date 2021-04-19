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

Time:2018-8

info:

***************************************************************************************************/

#ifndef __boostString
#define __boostString

class MK_DLL_EXPORT boostStringHelper
{
public:

    // Case Conversion
    static std::string to_upper_copy(const string& src); 
    static void to_upper(string& src); 
/*
    to_lower_copy() 
    to_lower()
    
    //Trimming
    trim_left_copy_if() 
    trim_left_if() 
    trim_left_copy() 
    trim_left()
    
    trim_right_copy_if() 
    trim_right_if() 
    trim_right_copy() 
    trim_right()
    
    trim_copy_if() 
    trim_if() 
    trim_copy() 
    trim()
    
    //Predicates
    starts_with() 
    istarts_with()
    ends_with() 
    iends_with()
    contains() 
    icontains()
    equals() 
    iequals()
    lexicographical_compare() 
    ilexicographical_compare()
    all()
    
    //Find algorithms
    find_first() 
    ifind_first()
    find_last() 
    ifind_last()
    find_nth() 
    ifind_nth()
    find_head()
    find_tail()
    find_token()
    find_regex()
    find()
    
    //Erase/Replace
    replace_first() 
    replace_first_copy() 
    ireplace_first() 
    ireplace_first_copy() 
    erase_first() 
    erase_first_copy() 
    ierase_first() 
    ierase_first_copy()

    replace_last() 
    replace_last_copy() 
    ireplace_last() 
    ireplace_last_copy() 
    erase_last() 
    erase_last_copy() 
    ierase_last() 
    ierase_last_copy()

    replace_nth() 
    replace_nth_copy() 
    ireplace_nth() 
    ireplace_nth_copy() 
    erase_nth() 
    erase_nth_copy() 
    ierase_nth() 
    ierase_nth_copy()

    replace_all() 
    replace_all_copy() 
    ireplace_all() 
    ireplace_all_copy() 
    erase_all() 
    erase_all_copy() 
    ierase_all() 
    ierase_all_copy()

    replace_head() 
    replace_head_copy() 
    erase_head() 
    erase_head_copy() 

    replace_tail() 
    replace_tail_copy() 
    erase_tail() 
    erase_tail_copy() 

    replace_regex() 
    replace_regex_copy() 
    erase_regex() 
    erase_regex_copy() 

    replace_all_regex() 
    replace_all_regex_copy() 
    erase_all_regex() 
    erase_all_regex_copy() 

    find_format() 
    find_format_copy() 
    find_format_all() 
    find_format_all_copy()()

    //Split
    find_all() 
    ifind_all() 
    find_all_regex()
    split() 
    split_regex()
    iter_find()
    iter_split()

    // Join
    join()
    join_if()
*/
};


class MK_DLL_EXPORT boostStringFinder
{
public:
/*
    //Search for the first match of the string in an input	
    first_finder()
    
    //Search for the last match of the string in an input	
    last_finder()
    
    //Search for the nth (zero-indexed) match of the string in an input	
    nth_finder()
    
    //Retrieve the head of an input	
    head_finder()
    
    //Retrieve the tail of an input	
    tail_finder()
    
    //Search for a matching token in an input	
    token_finder()
    
    //Do no search, always returns the given range	
    range_finder()
    
    //Search for a substring matching the given regex	
    regex_finder()
*/
};

class MK_DLL_EXPORT boostStringFormatter
{
public:
/*
    //Constant formatter. Always return the specified string	
    const_formatter()
    
    //Identity formatter. Return unmodified input input	
    identity_formatter()
    
    //Null formatter. Always return an empty string	
    empty_formatter()
    
    //Regex formatter. Format regex match using the specification in the format string	
    regex_formatter()
*/
};

class MK_DLL_EXPORT boostStringIterator
{
public:
/*
    //Iterates through matching substrings in the input	
    find_iterator
    
    //Iterates through gaps between matching substrings in the input	
    split_iterator
*/
};

class MK_DLL_EXPORT boostStringClassification
{
public:
/*
    Generic ctype mask based classification	
    is_classified()
    
    Recognize spaces	
    is_space()
    
    Recognize alphanumeric characters	
    is_alnum()
    
    Recognize letters	
    is_alpha()
    
    Recognize control characters	
    is_cntrl()
    
    Recognize decimal digits	
    is_digit()
    
    Recognize graphical characters	
    is_graph()
    
    Recognize lower case characters	
    is_lower()
    
    Recognize printable characters	
    is_print()
    
    Recognize punctuation characters	
    is_punct()
    
    Recognize uppercase characters	
    is_upper()
    
    Recognize hexadecimal digits	
    is_xdigit()
    
    Recognize any of a sequence of characters	
    is_any_of()
    
    Recognize characters inside a min..max range	
    is_from_range()
*/
};

#endif //__mkString
