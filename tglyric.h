#ifndef TGLYRIC_H
#define TGLYRIC_H

#include <vector>
#include <string>

class TGLyric
{
	
private:
	static const std::string REGEX;
	int from = 0;
	std::string lyrics;
	
public:
	TGLyric();
	int getFrom();
	void setFrom(int from);
	std::string& getLyrics();
	void setLyrics(const std::string &lyrics);
	size_t getLyricBeats(std::vector<std::string>& out );
	bool isEmpty();
};

#endif // TGLYRIC_H
