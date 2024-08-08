#ifndef GMCHANNELROUTER_H
#define GMCHANNELROUTER_H

#include <vector>

class GMChannelRoute;
class GMChannelRouter
{

public:
	static constexpr short MAX_CHANNELS = 16;
	static constexpr short PERCUSSION_CHANNEL = 9;

private:
	std::vector<GMChannelRoute*> midiChannels;

public:
	GMChannelRouter();
	virtual ~GMChannelRouter();

	virtual void resetRoutes();
	virtual void removeRoute(GMChannelRoute *route);
	virtual GMChannelRoute *getRoute(int channelId);
	virtual void configureRoutes(GMChannelRoute *route, bool percussionChannel);
	virtual void configureRoutesRecursively(GMChannelRoute *route, 
											bool percussionChannel);
	virtual std::vector<GMChannelRoute*> findOrphanRoutes();
	virtual std::vector<GMChannelRoute*> 
			findConflictingRoutes(GMChannelRoute *gmChannelRoute);
	virtual std::vector<int> getFreeChannels();
	virtual std::vector<int> getFreeChannels(GMChannelRoute *forRoute);
};


#endif // GMCHANNELROUTER_H
