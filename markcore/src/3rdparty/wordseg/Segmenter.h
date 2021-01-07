//
//  Segmenter.h
//  wordseg
//
//  Created by Windoze on 12-2-7.
//  Copyright (c) 2012 0d0a.com. All rights reserved.
//

#ifndef wordseg_Segmenter_h
#define wordseg_Segmenter_h

#include <wchar.h>
#include <string>
#include <vector>
#include <istream>
#include "PrefixTree.h"

class Segmenter_impl;
class Segmenter
{
public:
    typedef std::vector<std::wstring> wsegments_t;
    typedef std::vector<std::string> segments_t;
    
    Segmenter();
    ~Segmenter();

    void add_word(const std::wstring &word);
    void load_dict(std::wistream &is);
    wsegments_t segment(const std::wstring& str, bool include_cjk_words=true, bool include_cjk_ideograms=true) const;
    wsegments_t operator()(const std::wstring& str, bool include_cjk_words=true, bool include_cjk_ideograms=true) const
    {
        return segment(str, include_cjk_words, include_cjk_ideograms);
    }
    
    void add_word(const std::string &word);
    void load_dict(const char *file);
    void load_dict(std::istream &is);
    segments_t segment(const std::string& str, bool include_cjk_words=true, bool include_cjk_ideograms=true) const;
    segments_t operator()(const std::string& str, bool include_cjk_words=true, bool include_cjk_ideograms=true) const
    {
        return segment(str, include_cjk_words, include_cjk_ideograms);
    }
    
    //PrefixTree &dict();

private:
    void break_CJK(const std::wstring& str, Segmenter::wsegments_t &seg, bool include_cjk_words=true, bool include_cjk_ideograms=true) const;

    Segmenter_impl *impl;
};

#endif
