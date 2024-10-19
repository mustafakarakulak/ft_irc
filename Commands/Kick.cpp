#include "../Server/Server.hpp"


// kick Pragma Go coding in Pascal!
// kick #a museker
void    Server::Kick(int index, int id)
{
	(void)index;
	if (commands.size() < 3)
	{
		clients[id].print("You should use like this: KICK #channelName nickName\n");
		return;
	}

	int	channel_index = getChannelIndex(commands[1]);
    std::string message = "";

    if (channel_index == -1)
		clients[id].print("KICK: There is no one or channel for this name.\n");
    else
	{
		int	client_index = getClientIndex2(commands[2], channels[channel_index].getClients());
    	if (client_index == -1)
		{
			clients[id].print("KICK: There is no one or channel for this name.\n");
			return;
		}
		if (isInChannel(channels[channel_index].getChannelAdmins(), clients[id].getNickName()) == -1)
		{
			clients[id].print("KICK: You are not a admin for " + channels[channel_index].getChannelName() + ".\n");
			return;
		}
		for (size_t i = 3; i < this->commands.size(); i++)
    	{
        	message += commands[i];
        	message += " ";
    	}
		std::vector<Client> c_clients = channels[channel_index].getClients();
		for (size_t i = 0; i < c_clients.size(); i++)
			c_clients[i].print("KICK " + channels[channel_index].getChannelName() + " " + c_clients[client_index].getNickName() + " " +  message + "\r\n");
		c_clients.erase(c_clients.begin() + client_index);
		channels[channel_index].setClients(c_clients);
	}
}
