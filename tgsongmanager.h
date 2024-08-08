#ifndef TGSONGMANAGER_H
#define TGSONGMANAGER_H

#include <vector>
#include "tgstring.h"

struct Tuning{};


typedef std::vector<std::vector<int> >   vvector;

class TGSongManager
{
	int dummy;
public:
	TGSongManager(){
		dummy=0;
	}
	constexpr static  short MAX_CHANNELS = 16;
	
	static const vvector DEFAULT_TUNING_VALUES;
	
	
	static TGString* newString(int number,int value){
		TGString *string = new TGString;
		string->number=(number);
		string->value=(value);
		return string;
	}

	
	static size_t createPercussionStrings(int stringCount, 
										  std::vector<TGString*>& sv) {
		return createStrings(stringCount, sv, nullptr);
	}
	
	static size_t  createStrings(int stringCount, 
								 std::vector<TGString*>& sv,
								 const vvector* tunning = nullptr) 
	{
		if( tunning != nullptr ) 
		{
			for(auto& a : *tunning) 
			{
				if( stringCount == (int)a.size() ) 
				{
					int n=1;
					for(auto& b : a)
					{
						sv.push_back(new TGString(n, b));
						++n;
					}
					break;
				}
			}
		}
		
		if( sv.empty() ) {
			for(int i = 1;i <= stringCount; i++){
				sv.push_back(new TGString(i, 0));
			}
		}
		return sv.size();
	}
	
	static size_t createDefaultInstrumentStrings(int stringCount,
												 std::vector<TGString*>& sv) 
	{
		return createStrings(stringCount, sv, &DEFAULT_TUNING_VALUES);
	}
	
};

#endif // TGSONGMANAGER_H
