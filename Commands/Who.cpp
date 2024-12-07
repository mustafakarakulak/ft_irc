#include "../Server/Server.hpp"
#include "../Commands/ValidationUtils.hpp"
#include "../Commands/NumericReplies.hpp"

void Server::Who(size_t j, int id)
{
    (void)j;
    
    if (!ValidationUtils::validateCommandFormat(commands, 2)) {
        clients[id].print(ERR_NEEDMOREPARAMS(clients[id].getNickName(), "WHO"));
        return;
    }

    std::string channelName = commands[1];
    if (!ValidationUtils::validateChannelName(channelName)) {
        clients[id].print(ERR_NOSUCHCHANNEL(clients[id].getNickName(), channelName));
        return;
    }

    int channelIndex = getChannelIndex(channelName);
    if (channelIndex == -1) {
        clients[id].print(ERR_NOSUCHCHANNEL(clients[id].getNickName(), channelName));
        return;
    }

    std::vector<Client> channelClients = channels[channelIndex].getClients();
    for (size_t i = 0; i < channelClients.size(); i++)
    {
        clients[id].print("Nick: " + channelClients[i].getNickName() + "\n");
    }
    
    clients[id].print(":" + clients[id].getIp() + " 315 " + commands[1] + " :End of WHO list\r\n");
}