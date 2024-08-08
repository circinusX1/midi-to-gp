#include "temps.h"
#include "gmchannelrouter.h"
#include "gmchannelroute.h"

GMChannelRouter::GMChannelRouter()
{
	this->midiChannels = std::vector<GMChannelRoute*>();
}

GMChannelRouter::~GMChannelRouter()
{
}

void GMChannelRouter::resetRoutes()
{
	this->midiChannels.clear();
}

void GMChannelRouter::removeRoute(GMChannelRoute *route)
{
	GMChannelRoute *existingRoute = this->getRoute(route->getChannelId());
	if (existingRoute != nullptr)
	{
		
		this->midiChannels.erase(ITER(midiChannels,existingRoute));
	}
}

GMChannelRoute *GMChannelRouter::getRoute(int channelId)
{
	std::vector<GMChannelRoute*>::const_iterator channelIt = 
			this->midiChannels.begin();
	while (channelIt != this->midiChannels.end())
	{
		GMChannelRoute *midiChannel = (GMChannelRoute*) *channelIt;
		if (midiChannel->getChannelId() == channelId)
		{
			return midiChannel;
		}
		channelIt++;
	}
	return nullptr;
}

void GMChannelRouter::configureRoutes(GMChannelRoute *route, bool percussionChannel)
{
	this->configureRoutesRecursively(route, percussionChannel);
}

void GMChannelRouter::configureRoutesRecursively(GMChannelRoute *route, bool percussionChannel)
{
	std::vector<GMChannelRoute*> conflictingRoutes;

	this->removeRoute(route);

	// Allways channel 9 for percussions
	if (percussionChannel)
	{
		route->setChannel1(PERCUSSION_CHANNEL);
		route->setChannel2(PERCUSSION_CHANNEL);
	}

	else
	{
		// Use custom routes 
		if (route->getChannel1() >= 0)
		{
			if (route->getChannel2() < 0)
			{
				route->setChannel2(route->getChannel1());
			}
			conflictingRoutes = findConflictingRoutes(route);
		}

		// Add default routes
		else
		{
			std::vector<int> freeChannels = getFreeChannels();
			if(freeChannels.size() > 0)
			{ 
				route->setChannel1(freeChannels[0]);
			}
			else{
				route->setChannel1(GMChannelRoute::NULL_VALUE);
			}
			
			if(freeChannels.size() > 1)
			{
				route->setChannel2(freeChannels[1]); 
			}else
			{
				route->setChannel2(route->getChannel1());
			}
		}
	}

	this->midiChannels.push_back(route);

	// Reconfigure conflicting routes
	if (!conflictingRoutes.empty())
	{
		for (auto conflictingRoute : conflictingRoutes)
		{
			conflictingRoute->setChannel1(GMChannelRoute::NULL_VALUE);
			conflictingRoute->setChannel2(GMChannelRoute::NULL_VALUE);
			configureRoutesRecursively(conflictingRoute, false);
		}
	}

	// Reconfigure orphan routes
	std::vector<GMChannelRoute*> orphanRoutes = findOrphanRoutes();
	for (auto orphanRoute : orphanRoutes)
	{
		if (!this->getFreeChannels().empty())
		{
			this->configureRoutesRecursively(orphanRoute, false);
		}
	}
}

std::vector<GMChannelRoute*> GMChannelRouter::findOrphanRoutes()
{
	std::vector<GMChannelRoute*> routes;
	for (auto route : this->midiChannels)
	{
		if (route->getChannel1() == GMChannelRoute::NULL_VALUE || 
				route->getChannel2() == GMChannelRoute::NULL_VALUE)
		{
			routes.push_back(route);
		}
	}
	return routes;
}

std::vector<GMChannelRoute*> GMChannelRouter::findConflictingRoutes(GMChannelRoute *gmChannelRoute)
{
	std::vector<GMChannelRoute*> routes;
	for (auto route : this->midiChannels)
	{
		if (! (*route==*gmChannelRoute))
		{
			if (route->getChannel1() == gmChannelRoute->getChannel1() || 
					route->getChannel1() == gmChannelRoute->getChannel2() || 
					route->getChannel2() == gmChannelRoute->getChannel1() || 
					route->getChannel2() == gmChannelRoute->getChannel2())
			{

				routes.push_back(route);
			}
		}
	}
	return routes;
}

std::vector<int> GMChannelRouter::getFreeChannels()
{
	return getFreeChannels(nullptr);
}

std::vector<int> GMChannelRouter::getFreeChannels(GMChannelRoute *forRoute)
{
	std::vector<int> freeChannels;

	for (int ch = 0 ; ch < MAX_CHANNELS ; ch++)
	{
		if (ch != PERCUSSION_CHANNEL)
		{
			bool isFreeChannel = true;

			for( auto& route : midiChannels)
			{
				if (forRoute == nullptr || !( *forRoute == *route ))
				{
					if (route->getChannel1() == ch || route->getChannel2() == ch)
					{
						isFreeChannel = false;
					}
				}
			}

			if (isFreeChannel)
			{
				freeChannels.push_back(ch);
			}
		}
	}
	return freeChannels;
}
