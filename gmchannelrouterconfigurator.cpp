#include "gmchannelrouterconfigurator.h"

GMChannelRouterConfigurator::GMChannelRouterConfigurator(GMChannelRouter *router)
{
	this->router = router;
}

void GMChannelRouterConfigurator::configureRouter(std::vector<TGChannel*> &channels)
{
	std::vector<GMChannelRoute*> routes = this->findCurrentRoutes(channels);

	this->router->resetRoutes();
	for (auto channel : channels)
	{
		this->router->configureRoutes(this->findOrCreateCurrentRoute(routes, channel), 
									  channel->isPercussionChannel());
	}

	for (auto channel : channels)
	{
		int channel1 = this->getIntegerChannelParameter(channel,
														GMChannelRoute::PARAMETER_GM_CHANNEL_1,
														GMChannelRoute::NULL_VALUE);
		int channel2 = this->getIntegerChannelParameter(channel,
														GMChannelRoute::PARAMETER_GM_CHANNEL_2,
														GMChannelRoute::NULL_VALUE);
		if (channel1 >= 0)
		{
			GMChannelRoute *route = this->router->getRoute(channel->getChannelId());
			if (route == nullptr)
			{
				route = new GMChannelRoute(channel->getChannelId());
			}
			route->setChannel1(channel1);
			route->setChannel2(channel2);

			this->router->configureRoutes(route, channel->isPercussionChannel());
		}
	}
}

std::vector<GMChannelRoute*> GMChannelRouterConfigurator::findCurrentRoutes(
		std::vector<TGChannel*> &channels)
{
	std::vector<GMChannelRoute*> routes;
	for (auto channel : channels)
	{
		GMChannelRoute *route = this->router->getRoute(channel->getChannelId());
		if (route != nullptr)
		{
			routes.push_back(route);
		}
	}
	return routes;
}

GMChannelRoute *GMChannelRouterConfigurator::findCurrentRoute(
		std::vector<GMChannelRoute*> &routes, TGChannel *channel)
{
	for (auto route : routes)
	{
		if (route->getChannelId() == channel->getChannelId())
		{
			return route;
		}
	}
	return nullptr;
}

GMChannelRoute *GMChannelRouterConfigurator::findOrCreateCurrentRoute(
		std::vector<GMChannelRoute*> &routes, TGChannel *channel)
{
	GMChannelRoute *cmChannelRoute = findCurrentRoute(routes, channel);
	if (cmChannelRoute == nullptr)
	{
		cmChannelRoute = new GMChannelRoute(channel->getChannelId());
	}
	return cmChannelRoute;
}

int GMChannelRouterConfigurator::getIntegerChannelParameter(TGChannel *tgChannel, 
															const std::string &key, int nullValue)
{
	TGChannelParameter *tgChannelParameter = findChannelParameter(tgChannel, key);
	if (tgChannelParameter != nullptr && tgChannelParameter->getValue() != "")
	{
		return std::stoi(tgChannelParameter->getValue());
	}
	return nullValue;
}

TGChannelParameter *GMChannelRouterConfigurator::findChannelParameter(TGChannel *tgChannel, 
																	  const std::string &key)
{
	for(auto& parameter :tgChannel->getParameters())
	{
		if (parameter->getKey() == key)
		{
			return parameter;
		}
	}
	return nullptr;
}
