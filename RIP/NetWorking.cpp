#include "NetWorking.h"

NetWorking::NetWorking()
{

}

void NetWorking::begin()
{
	memset(netWork, 0, sizeof(netWork));
}

void NetWorking::setNet(NetWork *Network)
{
	memcpy(netWork, Network, sizeof(netWork));
}

void NetWorking::getNet(NetWork *Network)
{
	Network = netWork;
}