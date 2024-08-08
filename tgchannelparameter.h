#ifndef TGCHANNELPARAMETER_H
#define TGCHANNELPARAMETER_H

#include <string>


class TGChannelParameter {
public:
	
	std::string key;
	std::string value;
	
	TGChannelParameter(){
	}
	
	const std::string& getKey()const {
		return this->key;
	}
	
	void setKey(const std::string& key) {
		this->key = key;
	}
	
	const std::string getValue()const{
		return this->value;
	}
	
	void setValue(const std::string& value) {
		this->value = value;
	}
	
	void copyFrom(const TGChannelParameter* channelParameter){
		this->setKey(channelParameter->getKey());
		this->setValue(channelParameter->getValue());
	}
	
	TGChannelParameter* clone(){
		TGChannelParameter* tgChannelParameter = new TGChannelParameter();
		tgChannelParameter->copyFrom(this);
		return tgChannelParameter;
	}
};


#endif // TGCHANNELPARAMETER_H

