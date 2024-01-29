#include "server.h"

void Server::handleClientOffline(int clientSocket, const std::string &clientName)
{
    std::cerr << "Client " << clientName << " offline!" << std::endl;

    // Locks the clients vector to ensure thread safety
    std::lock_guard<std::mutex> guard(clientsMutex);

    // Removes the disconnected client from the clients vector
    clients.erase(std::remove_if(clients.begin(), clients.end(), [clientSocket](const Client &client)
                                 { return client.getSocket() == clientSocket; }),
                  clients.end());

    close(clientSocket);
}