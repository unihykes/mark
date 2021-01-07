#include <math.h>
#include "PrefixTree.h"

/*
path_t *path_t::the_empty_path=0;

path_t *path_t::empty_path() {
    // WARNING: Thread safety
    if (path_t::the_empty_path==0) {
        path_t::the_empty_path=new path_t();
    }
    return path_t::the_empty_path;
}
 */

void PrefixTree::calculate_path_weight(path_t &p) const
{
    // we just calc freq for now
    double n_plus_m = word_count + added_count;
    int n=0;
    for (path_t::iterator i=p.begin(); i!=p.end(); ++i) {
        p.weight += log(double(i->wf));
        n++;
    }
    p.weight-=log(n_plus_m)*n;
}

