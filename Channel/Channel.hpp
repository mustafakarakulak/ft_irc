#pragma once

#include "../Client/Client.hpp"
#include <iostream>
#include <vector>

class Channel
{
    private:
        std::vector<Client> clients;
        std::string channelName;
		int			channelAdminSetted;
		std::vector<Client> channelAdmins;
		std::string topic;

    public:
        Channel(std::string name);

        std::vector<Client> getClients();
		std::vector<Client> getChannelAdmins();
        std::string         getChannelName();
        std::string         getTopic();

		int					getChannelAdminSetted();

		void				setClients(std::vector<Client> clients);
		void				addClient(Client client);
		void				addAdmin(Client admin);
        void                setTopic(std::string new_topi);
        void                removeAdmin(Client admin);

        ~Channel();

};