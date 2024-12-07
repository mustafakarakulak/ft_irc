#include "../Server/Server.hpp"
#include "../Commands/ValidationUtils.hpp"
#include "../Commands/NumericReplies.hpp"

void Server::Mode(size_t j, int id)
{
    // En az 2 parametre gerekli (kanal adı ve mod)
    if (!ValidationUtils::validateCommandFormat(commands, 2)) {
        clients[id].print(ERR_NEEDMOREPARAMS(clients[id].getNickName(), "MODE"));
        return;
    }

    std::string channelName = commands[j + 1];
    if (!ValidationUtils::validateChannelName(channelName)) {
        clients[id].print(ERR_NOSUCHCHANNEL(clients[id].getNickName(), channelName));
        return;
    }

    int channelIndex = getChannelIndex(channelName);
    if (channelIndex == -1) {
        clients[id].print(ERR_NOSUCHCHANNEL(clients[id].getNickName(), channelName));
        return;
    }

    Channel* channel = &channels[channelIndex];

    // MODE #channel b gibi durumlar için
    if (commands.size() == 3) {
        std::string mode = commands[j + 2];
        if (mode == "b") {
            // Ban listesi boş olduğu için direkt end mesajı
            clients[id].print(":" + serverName + " 368 " + clients[id].getNickName() + 
                            " " + channelName + " :End of channel ban list\r\n");
            return;
        }
    }

    // MODE #channel +o/-o nick için
    if (commands.size() >= 4) {
        if (!ValidationUtils::validateAdminPrivileges(*channel, clients[id].getNickName())) {
            clients[id].print(ERR_CHANOPRIVSNEEDED(clients[id].getNickName(), channelName));
            return;
        }

        std::string mode = commands[j + 2];
        std::string targetNick = commands[j + 3];
        int targetIndex = getClientIndex(targetNick);

        if (targetIndex == -1) {
            clients[id].print(ERR_NOSUCHNICK(clients[id].getNickName(), targetNick));
            return;
        }

        if (mode == "+o") {
            if (channel->isAdmin(clients[targetIndex].getNickName())) {
                clients[id].print(ERR_USERONCHANNEL(clients[id].getNickName(), targetNick, channelName));
                return;
            }

            channel->addAdmin(clients[targetIndex]);
            std::string modeMessage = ":" + clients[id].getNickName() + " MODE " + 
                                    channel->getChannelName() + " +o " + targetNick + "\r\n";
            
            std::vector<Client> channelClients = channel->getClients();
            for (size_t i = 0; i < channelClients.size(); i++) {
                channelClients[i].print(modeMessage);
            }
        }
        else if (mode == "-o") {
            if (!channel->isAdmin(clients[targetIndex].getNickName())) {
                clients[id].print(ERR_NOTONCHANNEL(clients[id].getNickName(), channelName));
                return;
            }

            if (channel->isAdmin(clients[targetIndex].getNickName()) && 
                clients[id].getNickName() != targetNick) {
                clients[id].print("482 " + clients[id].getNickName() + " " + channelName + 
                                " :Cannot deop another operator\r\n");
                return;
            }

            channel->removeAdmin(clients[targetIndex].getNickName());
            std::string modeMessage = ":" + clients[id].getNickName() + " MODE " + 
                                    channel->getChannelName() + " -o " + targetNick + "\r\n";
            
            std::vector<Client> channelClients = channel->getClients();
            for (size_t i = 0; i < channelClients.size(); i++) {
                channelClients[i].print(modeMessage);
            }
        }
    }
}