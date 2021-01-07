#include <fstream>
#include "Segmenter.h"
#include "wordseg.h"

wordseg::wordseg()
{
	impl=new Segmenter();
}

wordseg::~wordseg()
{
	delete (Segmenter *)impl;
}

void wordseg::load_dict(const char *fn)
{
	((Segmenter *)impl)->load_dict(fn);
}

std::vector<std::string> wordseg::segment(const char *s, int include_cjk_word, int include_cjk_ideogram)
{
	std::string str(s);
	return ((Segmenter *)impl)->segment(str, (bool)include_cjk_word, (bool)include_cjk_ideogram);
}

