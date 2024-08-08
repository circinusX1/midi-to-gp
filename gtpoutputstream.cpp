#include "gtpoutputstream.h"

const std::string GTPOutputStream::DEFAULT_TG_CHARSET = "UTF-8";
const std::string GTPOutputStream::DEFAULT_VERSION_CHARSET = "UTF-8";

GTPOutputStream::GTPOutputStream(const char* file):_filename(file)
{
}

GTPOutputStream::~GTPOutputStream()
{
}

void GTPOutputStream::_reopen()
{

#if 0
	size_t fpos = gpout.tellp();
	gpout.close();
	std::cout << "\n-------------------------------------------------------\n";
	
	FILE* pf = fopen(_filename.c_str(),"rb");
	FILE* pf2 = fopen("tux.gp5","rb");
	if(pf && pf2)
	{
		int count = 1;
		char a[4];
		char ascii[128] = {0};
		while(!feof(pf) )
		{
			uint8_t byte;
			uint8_t byte2;

			if(!fread(&byte, 1, 1, pf))
				break;
			fread(&byte2, 1, 1, pf2);		
			if(byte != byte2)
				printf("(%02X-%02X) ", byte, byte2);
			else
				printf("%02x ", byte, byte2);
			sprintf(a,"%c",byte>='A' && byte<='z' ? byte : '.');
			strcat(ascii,a);
			/*
			if(byte != byte2){
				fclose(pf);
				fclose(pf2);
				pf=pf2=nullptr;
				printf (" %s\n",ascii);
				memset(ascii,0,sizeof(ascii));
				raise(SIGTRAP);
				break;
			}
			*/
			if(count++%16==0){
				printf (" %s\n",ascii);
				memset(ascii,0,sizeof(ascii));
			}
			if(feof(pf))break;
		}
		if(pf)fclose(pf);
		if(pf2)fclose(pf2);
	}
	std::cout << "\n======================================================\n";
	gpout.open(_filename.c_str(), std::fstream::out | std::fstream::app); 
#endif 
	
}


