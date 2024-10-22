#include "../Server/Server.hpp"

void Server::Mode(int index, int id)
{
	if (commands.size() < 4)
	{
		clients[id].print("You should use like this: MODE channelName +o nickname\n");
		return;
	}
	if (commands[index + 1][0] != '#')
		clients[id].print("MODE: There is no # in the first character.\n");

	if(getChannelIndex(commands[index + 1]) == -1)
		clients[id].print("MODE: There is no channel for this name.\n");
	if (getClientIndex2(commands[index + 1],channels[getChannelIndex(commands[index + 1])].getChannelAdmins()) != -1)
	{
		clients[id].print("MODE: You are already admin in this channel.\n");
		return;
	}

	Channel *tmpChnl = &channels[getChannelIndex(commands[index + 1])];
	if (commands[index + 2] == "+o")
	{
		if (tmpChnl->isAdmin(clients[id].getNickName()) == 1)
		{
			tmpChnl->addAdmin(clients[getClientIndex(commands[index + 3])]);

    	    for (size_t j = 0; j < tmpChnl->getClients().size(); j++)
    	        tmpChnl->getClients()[j].print("MODE " + tmpChnl->getChannelName() + " +o " + commands[index + 3] + "\r\n");

    	    for (size_t k = 0; k < tmpChnl->getClients().size(); k++)
    	        if (tmpChnl->getClients()[k].getNickName() != clients[id].getNickName())
    	            clients[id].print("MODE " + tmpChnl->getChannelName() + " +o " + commands[index + 3] + "\r\n");
		}
		else
		{
			clients[id].print("MODE: You are not a admin to select a new admin.\n");

		}
	}
	else if(commands[index + 2] == "-o")
	{
        if (tmpChnl->isAdmin(clients[id].getNickName()) == 0)
        {
            clients[id].print("MODE: " + clients[id].getNickName() + " is not an admin.\n");
            return;
        }
		tmpChnl->removeAdmin(clients[id].getNickName());
		for (size_t j = 0; j < tmpChnl->getClients().size(); j++)
            tmpChnl->getClients()[j].print("MODE " + tmpChnl->getChannelName() + " -o " + commands[index + 3] + "\r\n");
        clients[id].print("MODE " + tmpChnl->getChannelName() + " -o " + commands[index + 3] + "\r\n");
	}
	else
    {
        clients[id].print("MODE: Invalid mode. Use +o to add an admin or -o to remove an admin.\n");
    }

}

