#include <vector>
#include <string>

class wordseg
{
public:
	wordseg();
	~wordseg();
	void load_dict(const char *fn);
	std::vector<std::string> segment(const char *s, int include_cjk_word, int include_cjk_ideogram);

private:
	void *impl;
};

