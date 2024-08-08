#ifndef GMCHANNELROUTE_H
#define GMCHANNELROUTE_H

#include <string>

class GMChannelRoute
{

public:
	static const std::string PARAMETER_GM_CHANNEL_1;
	static const std::string PARAMETER_GM_CHANNEL_2;
	static constexpr int NULL_VALUE = -1;

private:
	int channelId = 0;
	int channel1 = 0;
	int channel2 = 0;

public:
	GMChannelRoute(int channelId);
	bool operator==(const GMChannelRoute& o)
	{
		return channelId==o.channelId && channel1==o.channel1 && channel2==o.channel2;
	}
	virtual int getChannelId();
	virtual int getChannel1();
	virtual void setChannel1(int channel1);
	virtual int getChannel2();
	virtual void setChannel2(int channel2);
};

#endif // GMCHANNELROUTE_H
