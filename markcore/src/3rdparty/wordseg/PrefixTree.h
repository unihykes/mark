//
//  PrefixTree.h
//  wordseg
//
//  Created by Windoze on 12-2-9.
//  Copyright (c) 2012 0d0a.com. All rights reserved.
//

#ifndef wordseg_PrefixTree_h
#define wordseg_PrefixTree_h

#include <wchar.h>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <iostream>
#include "utf8.h"
template<typename IteratorT>
inline void pu32(std::ostream &os, IteratorT from, IteratorT to)
{
    std::string s;
    utf8::unchecked::utf16to8(from, to, std::back_inserter(s));
    os << s << std::endl;
}

inline void pu32(std::ostream &os, const std::wstring &ws)
{
    pu32(os, ws.begin(), ws.end());
}


template<typename ContainerT>
inline void pc(std::ostream &os, const ContainerT &c)
{
    for (typename ContainerT::const_iterator i=c.begin(); i!=c.end(); ++i) {
        os << *i << ",";
    }
    os << std::endl;
}

struct path_node {
    size_t len;
    size_t wf;
    path_node(size_t len_=0, size_t wf_=0)
    : len(len_)
    , wf(wf_)
    {}
};

inline std::ostream &operator<<(std::ostream &os, const path_node &n)
{
    os << '(' << n.len << ',' << n.wf << ')';
    return os;
}

struct path_t
{
    typedef std::vector<path_node> container_t;
    typedef container_t::iterator iterator;
    typedef container_t::const_iterator const_iterator;
    typedef container_t::value_type value_type;
    
    path_t() : len_(0), slw(0) {
        nodes.reserve(100);
    }
    
    path_t *clone() {
        return new path_t(*this);
    }
    
    double weight;
    size_t len() const {
        return len_;
    }
    bool operator<(const path_t &rhs) const {
        return weight<rhs.weight;
    }
    size_t size() const { return nodes.size(); }
    iterator begin() { return nodes.begin(); }
    iterator end() { return nodes.end(); }
    const_iterator begin() const { return nodes.begin(); }
    const_iterator end() const { return nodes.end(); }
    void push_back(const value_type &v) {
        nodes.push_back(v);
        len_+=v.len;
        if(v.len==1) slw++;
    }
    container_t nodes;
    size_t len_;
    size_t slw;
};

typedef boost::shared_ptr<path_t> path_ptr;
typedef std::vector<path_ptr> paths_t;

inline std::ostream &operator<<(std::ostream &os, path_ptr p)
{
    pc(os, p->nodes);
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const paths_t &p)
{
    for (paths_t::const_iterator i=p.begin(); i!=p.end(); ++i) {
        for (path_t::const_iterator j=(*i)->begin(); j!=(*i)->end(); ++j) {
            os << *j;
        }
        os << std::endl;
    }
    return os;
}

// Compare shared_ptr
struct path_asc_cmp {
    bool operator()(path_ptr lhs, path_ptr rhs) const {
        return *lhs<*rhs;
    }
};

struct path_desc_cmp {
    bool operator()(path_ptr lhs, path_ptr rhs) const {
        return *rhs<*lhs;
    }
};

struct path_len_asc_cmp {
    bool operator()(path_ptr lhs, path_ptr rhs) const {
        return rhs->len()>lhs->len();
    }
};

struct path_len_desc_cmp {
    bool operator()(path_ptr lhs, path_ptr rhs) const {
        return rhs->len()<lhs->len();
    }
};

struct path_size_asc_cmp {
    bool operator()(path_ptr lhs, path_ptr rhs) const {
        return (lhs->size()==rhs->size()) ? lhs->slw<rhs->slw: lhs->size()<rhs->size();
        //return lhs->size()<rhs->size();
    }
};

struct path_size_desc_cmp {
    bool operator()(path_ptr lhs, path_ptr rhs) const {
        return (lhs->size()==rhs->size()) ? lhs->slw>rhs->slw: lhs->size()>rhs->size();
        //return rhs->size()>lhs->size();
    }
};

class PrefixTree
{
public:
    typedef std::vector<path_node> matches_t;

    struct matches_len_desc_cmp {
        bool operator()(const path_node lhs, path_node rhs) const {
            return rhs.len<lhs.len;
        }
    };

    template<typename IteratorT>
    void add_word(IteratorT from, IteratorT to, size_t wf=1)
    {
        internal_add_word(&get_roots(), from, to, wf);
    }
    template<typename IteratorT>
    size_t match_word(IteratorT from, IteratorT to) const
    {
        return internal_match_word(get_roots(), from, to);
    }
    template<typename IteratorT>
    void all_prefix(IteratorT from, IteratorT to, matches_t &matches) const
    {
        internal_all_prefix(&get_root(), from, to, matches);
    }
    
#if 0
    template<typename IteratorT>
    paths_t all_paths(IteratorT from, IteratorT to) const
    {
        paths_t output;
        path_t prefix;
        internal_all_paths(from, to, prefix, output);
        std::cout << "path number:" << output.size() << std::endl;
        return output;
    }
    
    template<typename IteratorT>
    path_t top_path(IteratorT from, IteratorT to) const
    {
        paths_t output=all_paths(from, to);
        if (output.empty()) {
            return path_t();
        }
        std::sort(output.begin(), output.end(), path_desc_cmp());
        return output[0];
    }
    
    template<typename IteratorT>
    paths_t top_n_path(IteratorT from, IteratorT to, size_t n) const
    {
        paths_t output=all_paths(from, to);
        if (output.empty()) {
            return output;
        }
        std::sort(output.begin(), output.end(), path_desc_cmp());
        if (output.size()<=n) {
            return output;
        }
        output.erase(output.begin()+n, output.end());
        return output;
    }
    
    template<typename IteratorT>
    void internal_all_paths(IteratorT from, IteratorT to, const path_t &prefix, paths_t &output) const
    {
        if (from==to) {
            output.push_back(prefix);
            return;
        }
        
        matches_t m;
        all_prefix(from, to, m);
        if (m.size()==0) {
            // Move 1 char forward
            m.push_back(path_node(1,1));
        }
        for (matches_t::const_iterator i=m.begin(); i!=m.end(); ++i) {
            path_t new_prefix(prefix);
            new_prefix.push_back(*i);
            IteratorT new_from=from;
            for(size_t n=0; n<i->len; ++n) {
                ++new_from;
            }
            internal_all_paths(new_from, to, new_prefix, output);
        }
        for (paths_t::iterator i=output.begin(); i!=output.end(); ++i) {
            calculate_path_weight(*i);
        }
    }
    
#else
    /**
     Find the best path
     TODO: n=5, need to be changable
     */
    template<typename IteratorT>
    path_t top_path(IteratorT from, IteratorT to) const
    {
        paths_t output;
        top_n_path(10, from, to, output);
        if (output.empty()) {
            return path_t();
        }
        return *output[0];
    }
    
    /**
     Find 'top' best paths
     */
    template<typename IteratorT>
    void top_n_path(size_t top, IteratorT from, IteratorT to, paths_t &output) const 
    {
        paths_t prefixes;
        paths_t new_prefixes;
        top_n_phrase(top, from, to, path_ptr(new path_t()), new_prefixes);
        while(1) {
            prefixes=new_prefixes;
            new_prefixes.clear();
            size_t not_end=0;
            for (paths_t::iterator i=prefixes.begin(); i!=prefixes.end(); ++i) {
                IteratorT new_from=from+(*i)->len();
                if (new_from!=to) {
                    // still some combinations are not ended
                    top_n_phrase(top, new_from, to, *i, new_prefixes);
                    not_end++;
                } else {
                    // One completed path
                    output.push_back(*i);
                    //std::cout << "XXX" <<output.size() << std::endl;
                }
            }
            //std::cout << "before " << output;
            std::sort(new_prefixes.begin(), new_prefixes.end(), path_len_desc_cmp());
            if (new_prefixes.size()>top) {
                new_prefixes.erase(new_prefixes.begin()+top, new_prefixes.end());
            }
            //std::cout << "after " << new_prefixes;
            if (not_end==0) {
                // All paths come to the end of input
                break;
            }
        }
        output.insert(output.end(), new_prefixes.begin(), new_prefixes.end());
        //std::cout << "XXX" <<output.size() << std::endl;
#if 1
        for (paths_t::iterator i=output.begin(); i!=output.end(); ++i) {
            calculate_path_weight(**i);
        }
        std::sort(output.begin(), output.end(), path_desc_cmp());
#else
        std::sort(output.begin(), output.end(), path_size_asc_cmp());
#endif
        if (output.size()>top) {
            output.erase(output.begin()+top, output.end());
        }
    }
#endif

private:
    struct prefix_tree_node;
    
    typedef prefix_tree_node *prefix_tree_node_ptr;
    typedef boost::unordered_map<wchar_t, prefix_tree_node_ptr> prefix_tree_map;
    
    struct prefix_tree_node
    {
        prefix_tree_map children;
        bool eow;   // End-of-word
        size_t wf;
        prefix_tree_node() : eow(false), wf(0) {
            children.max_load_factor(3);
        }
        ~prefix_tree_node()
        {
            for (prefix_tree_map::iterator i=children.begin(); i!=children.end(); ++i) {
                delete i->second;
            }
        }
    };
    
    template<typename IteratorT>
    void internal_add_word(prefix_tree_map *roots, IteratorT from, IteratorT to, size_t wf)
    {
        while (from!=to)
        {
            bool new_word=false;
            wchar_t c=*from;
            if (roots->find(c)==roots->end()) {
                prefix_tree_node_ptr p=prefix_tree_node_ptr(new prefix_tree_node());
                p->eow=false;
                (*roots)[c]=p;
                new_word=true;
            }
            from++;
            if (from==to) {
                // This is the last letter
                (*roots)[c]->eow=true;
                (*roots)[c]->wf+=wf;
                if(new_word) {
                    // word_count only increases when this is a new word
                    word_count++;
                }
                // added_count increases 'wf' time even word exists
                added_count+=wf;
                return;
            }
            roots=&((*roots)[c]->children);
        }
    }

    template<typename IteratorT>
    size_t internal_match_word(const prefix_tree_map &roots, IteratorT from, IteratorT to) const
    {
        if (from==to) {
            return 0;
        }
        wchar_t c=*from;
        prefix_tree_map::const_iterator it=roots.find(c);
        if (it==roots.end()) {
            return 0;
        }
        // There is the char
        size_t len=0;
        if (it->second->eow) {
            // And this char is end-of-word, mark a match
            len=1;
        }
        from++;
        size_t n=internal_match_word(it->second->children, from, to);
        if (n>0) {
            n+=1;
        }
        if (n>len) {
            len=n;
        }
        return len;
    }

    /**
     Find all matched word in dict
     */
    template<typename IteratorT>
    void internal_all_prefix(const prefix_tree_node *root, IteratorT from, IteratorT to, matches_t &matches) const
    {
        size_t len=0;
        matches.reserve(matches.size()+100);
        while (from!=to) {
            prefix_tree_map::const_iterator it=root->children.find(*from);
            if (it==root->children.end()) {
                // Word not found
                return;
            }
            ++len;
            root=it->second;
            if (root->eow) {
                matches.push_back(path_node(len, root->wf+1));  // known word
            }
            ++from;
        }
    }
    
    /**
     Look forward for 'max_step' times, find all possible matches, pick 'top' longest prefixes, insert them into output
     */
    template<typename IteratorT>
    void internal_top_n_phrase(size_t top, size_t max_step, IteratorT from, IteratorT to, path_ptr prefix, paths_t &output) const
    {
        //std::cout << "enter internal_top_n_phrase\n";
        if (max_step==0 || from==to) {
            // ended
            output.push_back(path_ptr(prefix->clone()));
            //std::cout << "exit internal_top_n_phrase\n";
            return;
        }
        matches_t m;
        // Find all matched words in dict
        all_prefix(from, to, m);
        std::sort(m.begin(), m.end(), matches_len_desc_cmp());
        //std::cout << "X1XXXX " << m.size() << std::endl;
        //std::cout << "Matches "; pc(std::cout, m);
        if (m.size()==0) {
            // Move 1 char forward
            m.push_back(path_node(1,1));
        }
        paths_t raw_output;
        // For each matched prefix, look forward for max_step times,
        for (matches_t::const_iterator i=m.begin(); i!=m.end(); ++i) {
            //std::cout << "X1X1XXX " << i->len << std::endl;
            path_ptr new_prefix(prefix->clone());
            new_prefix->push_back(*i);
            IteratorT new_from=from+i->len;
            //pu32(std::cout, new_from, to);
            internal_top_n_phrase(top, max_step-1, new_from, to, new_prefix, raw_output);
        }
        // We now have at max top^2 new prefixes, pick "top" prefixes and discard others
        //std::sort(raw_output.begin(), raw_output.end(), path_len_desc_cmp());
        //std::cout << "X2X " << raw_output.size() << std::endl;
        output.insert(output.end(),
                      raw_output.begin(),
                      (top>raw_output.size() ? raw_output.end() : raw_output.begin()+top));
        //std::cout << "X3X " << output.size() << std::endl;
        //std::cout << "exit internal_top_n_phrase\n";
    }

    /**
     Look forward for 'max_step' times, find all possible matches, pick 'top' longest prefixes, insert them into output
     TODO: variable MAX_LOOK_AHEAD
     */
    template<typename IteratorT>
    void top_n_phrase(size_t top, IteratorT from, IteratorT to, path_ptr prefix, paths_t &output) const
    {
        const size_t MAX_LOOK_AHEAD=5;
        internal_top_n_phrase(top, MAX_LOOK_AHEAD, from, to, prefix, output);
    }

    /**
     calculate probobality for a path, based on word count and word freq
     */
    void calculate_path_weight(path_t &p) const;

    prefix_tree_map &get_roots() {
        return root.children;
    }
    
    prefix_tree_node &get_root() {
        return root;
    }
    
    const prefix_tree_map &get_roots() const {
        return root.children;
    }
    
    const prefix_tree_node &get_root() const {
        return root;
    }
    
    prefix_tree_node root;
    size_t word_count;
    size_t added_count;
};

#endif
