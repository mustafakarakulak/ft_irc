#include "../Server/Server.hpp"

void Server::Mode(int index, int id)
{
    clients[id].print("MODE: test here.\n");
    if (static_cast<int>(commands.size()) < index + 2)
    {
        clients[id].print("MODE: Not enough arguments.\n");
        return;
    }

    std::string channelName = commands[index + 1];
    std::string mode = commands[index + 2];

    // Kanalın var olup olmadığını kontrol et
    Channel* channel = nullptr;
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i].getChannelName() == channelName)
        {
            channel = &channels[i];
            break;
        }
    }

    if (!channel)
    {
        clients[id].print("MODE: Channel does not exist.\n");
        return;
    }

    // Kullanıcının kanalda olup olmadığını kontrol et
    if (!isInChannel(channel->getClients(), clients[id].getNickName()))
    {
        clients[id].print("MODE: You are not in this channel.\n");
        return;
    }

    // Modu uygula (örnek olarak +o ve -o)
    if (mode[0] == '+' || mode[0] == '-')
    {
        if (mode[1] == 'o') // Operatör modunu kontrol et
        {
            std::string targetNick = commands[index + 3];
            if (mode[0] == '+')
            {
                // Kullanıcıyı operatör yap
                channel->addAdmin(clients[getClientIndex(targetNick)]);
                std::string message = ":" + clients[id].getNickName() + " MODE " + channelName + " +o " + targetNick + "\r\n";
                for (size_t j = 0; j < channel->getClients().size(); j++)
                {
                    channel->getClients()[j].print(message);
                }
            }
            else if (mode[0] == '-')
            {
                // Kullanıcının operatörlüğünü al
                channel->removeAdmin(clients[getClientIndex(targetNick)]);
                std::string message = ":" + clients[id].getNickName() + " MODE " + channelName + " -o " + targetNick + "\r\n";
                for (size_t j = 0; j < channel->getClients().size(); j++)
                {
                    channel->getClients()[j].print(message);
                }
            }
        }
        else
        {
            clients[id].print("MODE: Invalid mode.\n");
        }
    }
    else
    {
        clients[id].print("MODE: Modes must start with '+' or '-'.\n");
    }
}
