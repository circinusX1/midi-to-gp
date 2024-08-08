#include "gmchannelroute.h"

const std::string GMChannelRoute::PARAMETER_GM_CHANNEL_1 = "gm-channel-1";
const std::string GMChannelRoute::PARAMETER_GM_CHANNEL_2 = "gm-channel-2";

GMChannelRoute::GMChannelRoute(int channelId)
{
	this->channelId = channelId;
	this->channel1 = NULL_VALUE;
	this->channel2 = NULL_VALUE;
}

int GMChannelRoute::getChannelId()
{
	return this->channelId;
}

int GMChannelRoute::getChannel1()
{
	return this->channel1;
}

void GMChannelRoute::setChannel1(int channel1)
{
	this->channel1 = channel1;
}

int GMChannelRoute::getChannel2()
{
	return this->channel2;
}

void GMChannelRoute::setChannel2(int channel2)
{
	this->channel2 = channel2;
}
