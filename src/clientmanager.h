#pragma once

#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#include <vector>
#include <algorithm>
#include "rapidcsv.h"
#include "client.h"
#include "logger.h"

class ClientManager
{
public:
    ClientManager();
    void LogClient(const std::string& login, const std::string& password);
    void LogOut();
    void AddClient(Client client);
    Client& GetCurClient();
    std::vector<Client> GetClientsList();

private:
    std::vector<Client> clientsList;
    Client currentClient;

};

#endif // CLIENTMANAGER_H
