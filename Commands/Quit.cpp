#include "../Server/Server.hpp"

void Server::Quit(size_t j, int id)
{
    (void)j;
    std::string quitMessage = ":" + clients[id].getNickName() + "!" + 
                            clients[id].getUserName() + "@" + 
                            clients[id].getIp() + " QUIT :Leaving\r\n";

    // Tüm kanallardaki işlemler
    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end();) {
        int clientIndex = isInChannel(it->getClients(), clients[id].getNickName());
        if (clientIndex != -1) {
            std::vector<Client> channelClients = it->getClients();
            for (size_t k = 0; k < channelClients.size(); k++) {
                if (channelClients[k].getNickName() != clients[id].getNickName()) {
                    channelClients[k].print(quitMessage);
                }
            }
            
            channelClients.erase(channelClients.begin() + clientIndex);
            it->setClients(channelClients);
            
            if (channelClients.empty()) {
                it = channels.erase(it);
                continue;
            }
        }
        ++it;
    }
    
    clients[id].setLoggedIn(false);
    clients[id].setRegistered(false);
    clients[id].setNickOK(false);
    clients[id].setUserOK(false);
    clients[id].setPassOK(false);
}