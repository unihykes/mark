//
//  Segmenter.cpp
//  wordseg
//
//  Created by Windoze on 12-2-7.
//  Copyright (c) 2012 0d0a.com. All rights reserved.
//
#include <list>
#include <istream>
#include <fstream>
#include <unicode/utypes.h>
#include <unicode/normalizer2.h>
#include "utf8.h"
#include "PrefixTree.h"
#include "Segmenter.h"
#include "CharType.h"

using namespace std;
using namespace boost;

class Segmenter_impl
{
public:
    typedef list<size_t> seg_t;
    typedef utf8::unchecked::iterator<string::const_iterator> u8_iterator;
    
    Segmenter_impl()
    : errorCode(U_ZERO_ERROR)
    , norm2(Normalizer2::getInstance(NULL, "nfkc", UNORM2_DECOMPOSE, errorCode))
    {}

    void add_word(const wstring &word, size_t wf=1)
    {
        if(word.empty())
            return;
        dict.add_word(word.begin(), word.end(),wf);
    }
    
    void add_word(const string &word, size_t wf=1)
    {
        if(word.empty())
            return;
        dict.add_word(
                      u8_iterator(word.begin()),
                      u8_iterator(word.end()),
                      wf);
    }

    void load_dict(wistream &is)
    {
        load_mp_dict(is);
    }

    void load_dict(istream &is)
    {
        load_mp_dict(is);
    }

    void load_mp_dict(wistream &is)
    {
        wstring line;
        while (is) {
            getline(is, line);
            size_t pos=line.find(L'\t');
            //wcout << line << endl;
            if (pos==string::npos) {
                // Invalid line
                continue;
            }
            size_t wf=wcstol(line.c_str(), NULL, 10);
            wstring s(line.begin()+pos+1, line.end());
            //wcout << L"[" << wf << L"]" << s << endl;
            dict.add_word(s.begin(), s.end(), wf);
        }
    }

    void load_mp_dict(istream &is)
    {
        string line;
        while (is) {
            getline(is, line);
            size_t pos=line.find('\t');
            //cout << line << endl;
            if (pos==string::npos) {
                // Invalid line
                continue;
            }
            size_t wf=strtol(line.c_str(), NULL, 10);
            string s(line.begin()+pos+1, line.end());
            //cout << "[" << wf << "]" << s << endl;
            dict.add_word(
                u8_iterator(s.begin()),
                u8_iterator(s.end()),
                wf);
        }
    }

    const Normalizer2 *normalizer() const
    {
        return norm2;
    }

    void segment(seg_t &s, const string &str) const
    {
        //segment(s, u8_iterator(str.begin()), u8_iterator(str.end()));
        wstring ws;
        utf8::unchecked::utf8to16(str.begin(), str.end(), back_inserter(ws));
        segment(s, ws);
    }

    void segment(seg_t &s, const wstring &str) const
    {
        segment(s, str.begin(), str.end());
    }

    template<typename IteratorT>
    void segment(seg_t &s, IteratorT from, IteratorT to) const
    {
        segment_max_prob(s, from, to);
    }

    template<typename IteratorT>
    void segment_max_prob(seg_t &s, IteratorT from, IteratorT to) const
    {
        path_t p=dict.top_path(from, to);
        for (path_t::iterator i=p.begin(); i!=p.end(); ++i) {
            s.push_back(i->len);
        }
    }

    PrefixTree dict;
    UErrorCode errorCode;
    const Normalizer2 *norm2;
};

Segmenter::Segmenter()
: impl(new Segmenter_impl)
{}

Segmenter::~Segmenter()
{
    delete impl;
}

void Segmenter::add_word(const std::wstring &word)
{
    impl->add_word(word);
}

void Segmenter::load_dict(std::wistream &is)
{
    impl->load_dict(is);
}

Segmenter::wsegments_t Segmenter::segment(const wstring& str, bool include_cjk_words, bool include_cjk_ideograms) const
{
    Segmenter::wsegments_t phrases;
    wstring ph;
    CharType last_ct=CT_UNKNOWN;
    UnicodeString decomp;
    for(wstring::const_iterator i=str.begin(); i!=str.end(); ++i) {
        wchar_t c=*i;
        CharType ct=get_char_type(c);
        if (ct==CT_MARKER) {
            // Ignore markers
            continue;
        }
        if (ct!=last_ct)
        {
            // We have a new phrase, push into phrases
            if(!ph.empty()) {
                //wcout << "phrase " << ph << endl;
                if (last_ct==CT_CJK) {
                    // Last phrase is in CJK, do word segmentation
                    break_CJK(ph, phrases, include_cjk_words, include_cjk_ideograms);
                } else if (last_ct==CT_LATIN) {
                    // Latin
                    // TODO: Stemming
                    phrases.push_back(ph);
                } else if (last_ct==CT_NUMBER) {
                    // number
                    phrases.push_back(ph);
                }
            }
            last_ct=ct;
            ph.clear();
        }
        // Add char into ph if it's a letter or number
        if (ct==CT_CJK) {
            ph.push_back(c);
        } else if (ct==CT_LATIN || ct==CT_NUMBER) {
            // process latin letters, to NFKD, ignore markers, the to lower
            if (impl->normalizer()->getDecomposition(c, decomp))
            {
                // c has a decomposition form
                for(int32_t i=0; i<decomp.length(); ++i)
                {
                    UChar dc=decomp[i];
                    if (is_latin(dc) || is_number(dc)) {
                        ph.push_back(u_tolower(dc));
                    }
                    // FIXME: handle something like "3/4"(u00BE), which should be broken into 2 phrases "3" and "4" instead of "34"
                }
            } else {
                // FIXME: shouldn't be here, for anything unknown
                ph.push_back(u_tolower(c));
            }
        }
    }
    // last phrase
    if(!ph.empty()) {
        //wcout << "phrase " << ph << endl;
        if (last_ct==CT_CJK) {
            // Last phrase is in CJK, do word segmentation
            break_CJK(ph, phrases, include_cjk_words, include_cjk_ideograms);
        } else if (last_ct==CT_LATIN) {
            // Latin
            // TODO: Stemming
            phrases.push_back(ph);
        } else if (last_ct==CT_NUMBER) {
            // number
            phrases.push_back(ph);
        }
    }
    return phrases;
}

void Segmenter::add_word(const std::string &word)
{
    wstring w;
    utf8::unchecked::utf8to16(word.begin(), word.end(), back_inserter(w));
    add_word(w);
}

void Segmenter::load_dict(std::istream &is)
{
    impl->load_dict(is);
}

Segmenter::segments_t Segmenter::segment(const std::string& str, bool include_cjk_words, bool include_cjk_ideograms) const
{
    wstring w;
    utf8::unchecked::utf8to16(str.begin(), str.end(), back_inserter(w));
    Segmenter::wsegments_t wseg=segment(w, include_cjk_words, include_cjk_ideograms);
    Segmenter::segments_t seg(wseg.size());
    for(Segmenter::wsegments_t::const_iterator i=wseg.begin(); i!=wseg.end(); ++i)
    {
        utf8::unchecked::utf16to8(i->begin(), i->end(), back_inserter(seg[i-wseg.begin()]));
    }
    return seg;
}

void Segmenter::load_dict(const char *file)
{
    std::ifstream is(file);
    load_dict(is);
}

/*
PrefixTree &Segmenter::dict()
{
    return impl->dict;
}
 */

// Assume input str contains *only* CJK ideograms, no punctuation
void Segmenter::break_CJK(const std::wstring& str, Segmenter::wsegments_t &seg, bool include_cjk_words, bool include_cjk_ideograms) const
{
    //cout << "BCJK--";
    //pu32(cout, str);
    Segmenter_impl::seg_t s;
    impl->segment(s, str);
    
    if (include_cjk_words)
    {
        std::wstring::const_iterator pos=str.begin();
        for (Segmenter_impl::seg_t::iterator i=s.begin(); i!=s.end(); ++i) {
            seg.push_back(wstring(pos, pos+*i));
            pos+=*i;
        }
    }
    // TODO: Find a better way to handle this
    if (include_cjk_ideograms) {
        // Store every single ideogram
        for (wstring::const_iterator i=str.begin(); i!=str.end(); ++i) {
            seg.push_back(wstring(1, *i));
        }
    }
}
