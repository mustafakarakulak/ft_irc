#include "Channel.hpp"


Channel::Channel(std::string name) { this->channelName = name; this->channelAdminSetted = 0;}

std::vector<Client> Channel::getClients() { return this->clients; }

std::string         Channel::getChannelName() { return this->channelName; }

void				Channel::addClient(Client client) { clients.push_back(client); }

int					Channel::getChannelAdminSetted() { return this->channelAdminSetted; }

void 				Channel::setClients(std::vector<Client> clients) { this->clients = clients;}

std::string         Channel::getTopic() { return topic; }

void                Channel::setTopic(std::string new_topic) { topic = new_topic; }

std::vector<Client> Channel::getChannelAdmins() { return channelAdmins; }

void				Channel::addAdmin(Client admin) { channelAdmins.push_back(admin); }

void 				Channel::setChannelAdmins(std::vector<Client> channelAdmins) { this->channelAdmins = channelAdmins;}

void Channel::removeAdmin(std::string nickname)
{
    std::vector<Client> clientss = getChannelAdmins();

    for(size_t i = 0; i< channelAdmins.size(); i++)
    {
        if (nickname == channelAdmins[i].getNickName())
        {
            channelAdmins.erase(channelAdmins.begin() + i);
            setChannelAdmins(channelAdmins); 
        }
    }
}


int Channel::isAdmin(std::string nickname)
{
    std::vector<Client> clientss = getChannelAdmins();

    for(size_t i = 0; i< clientss.size(); i++)
    {
        std::cout << clientss[i].getNickName() << std::endl;
        if (nickname == clientss[i].getNickName())
        {
        std::cout << clientss[i].getNickName() << std::endl;
            return 1;
        }

    }
    return 0;
}

Channel::~Channel() { }
