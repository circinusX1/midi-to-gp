#include "tglyric.h"

const std::string TGLyric::REGEX = " ";

TGLyric::TGLyric()
{
	this->from = 1;
}

int TGLyric::getFrom()
{
	return this->from;
}

void TGLyric::setFrom(int from)
{
	this->from = from;
}

std::string& TGLyric::getLyrics()
{
	return this->lyrics;
}

void TGLyric::setLyrics(const std::string &lyrics)
{
	this->lyrics = lyrics;
}

size_t TGLyric::getLyricBeats(std::vector<std::string>& out )
{
	std::string lyrics = getLyrics();
	std::string acc;
	for(auto& a : lyrics){
		if(a== '\n' || a=='\r')
		{
			out.push_back(acc);
			acc.clear();
		}
		acc.append(1,a);
	}
	return out.size();
}

bool TGLyric::isEmpty()
{
	return (getLyrics().length() == 0);
}

