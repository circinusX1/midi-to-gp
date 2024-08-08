#ifndef GMCHANNELROUTERCONFIGURATOR_H
#define GMCHANNELROUTERCONFIGURATOR_H

#include <string>
#include <vector>
#include "gmchannelrouter.h"
#include "gmchannelroute.h"
#include "tgchannel.h"

class GMChannelRouterConfigurator
{
	
private:
	GMChannelRouter *router;
	
public:
	virtual ~GMChannelRouterConfigurator()
	{
		delete router;
	}
	
	GMChannelRouterConfigurator(GMChannelRouter *router);
	
	virtual void configureRouter(std::vector<TGChannel*> &channels);
	
private:
	std::vector<GMChannelRoute*> findCurrentRoutes(std::vector<TGChannel*> &channels);
	
	GMChannelRoute *findCurrentRoute(std::vector<GMChannelRoute*> &routes, TGChannel *channel);
	
	GMChannelRoute *findOrCreateCurrentRoute(std::vector<GMChannelRoute*> &routes, 
											 TGChannel *channel);
	
	int getIntegerChannelParameter(TGChannel *tgChannel, const std::string &key, int nullValue);
	
	TGChannelParameter *findChannelParameter(TGChannel *tgChannel, const std::string &key);
};

#endif // GMCHANNELROUTERCONFIGURATOR_H
