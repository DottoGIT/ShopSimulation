#include "clientmanager.h"

ClientManager::ClientManager()
    : currentClient{Client("not logged", "-", "-", "-")} {}

Client& ClientManager::GetCurClient()
{
    return currentClient;
}

void ClientManager::LogClient(const std::string& login, const std::string& password)
{
    for (const auto& client: clientsList)
    {
        if ((client.GetLogin() == login) && client.GetPassword() == password){
            currentClient = client;
            Logger::Info("<clientManager.h> Klient " + client.GetLogin() + " zalogowal sie");
            return;
        }
    }
    Logger::Warning("<clientManager.h> Wprowadzono niepoprawne dane logoawania");
}

void ClientManager::LogOut()
{
    Logger::Info("<clientManager.h> Klient " + currentClient.GetLogin() + " wylogowal sie");
    currentClient = Client("not logged", "-", "-", "-");
}

void ClientManager::AddClient(Client client)
{
    clientsList.push_back(client);
    Logger::Info("<clientManager.h> Dodano klienta " + client.GetLogin() + " do bazy");
}

std::vector<Client> ClientManager::GetClientsList()
{
    return clientsList;
}




