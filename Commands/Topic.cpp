#include "../Server/Server.hpp"

void    Server::Topic(int index, int id)
{
    int is_exist = 0;

    if (commands[index + 1][0] != '#')
		clients[id].print("TOPIC: There is no # in the first character.\n");

    for (size_t j = 0; j < channels.size(); j++)
    {
        if (commands[index + 1] == channels[j].getChannelName())
        {
			if (isInChannel(channels[j].getChannelAdmins(), clients[id].getNickName()) == -1)
			{
				clients[id].print("TOPIC: You are not a admin for " + channels[j].getChannelName() + ".\n");
				return;
			}
            if (commands[index + 1] == channels[j].getChannelName() && isInChannel(channels[j].getClients(), clients[id].getNickName()) != -1)
            {
                is_exist = 1;
                for (size_t k = 0; k < channels[j].getClients().size(); k++)
                {
                    if (commands.size() > 2)
                        channels[j].getClients()[k].print("TOPIC " + commands[index + 1] + " :" + commands[index + 2] + "\r\n");
                    else
                        clients[id].print("TOPIC: Enter topic name.\n");
                }
            } 
        }
    }
    if (is_exist == 0)
        clients[id].print("TOPIC: Channel not found.\n");
}