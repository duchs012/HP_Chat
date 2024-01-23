#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cctype>
#include <chrono>
#include <fstream>
#include <map>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/select.h>

using namespace std;

const int PORT = 4444;
const int BUFFER_SIZE = 1024;
const int MAX_CLIENTS = 10;

class UserAuthentication
{
private:
    string username;
    string password;

public:
    UserAuthentication();

    bool isUserRegistered(const string &checkUsername);

    bool registerUser(const string &enteredUsername, const string &enteredPassword);

    bool isLoggedIn(const string &enteredUsername, const string &enteredPassword);
};

class Client {
public:
    Client(int socket, const string& name, const string& roomName);

    int getSocket() const;

    const string& getName() const;

    const string& getRoomName() const;

private:
    int socket;
    string name;
    string roomName;
};

class Server {
public:
    Server();

    Client* findClientByName(const string& name);

    void handlePrivateMessage(const string& senderName, const string& receiverName, const string& message);

    void printColoredIP(const char* ipAddress);

    void start(int port);

private:
    int serverSocket;
    int clientSocket;
    int maxSocket;
    sockaddr_in serverAddr;
    vector<Client> clients;
    mutex clientsMutex;
    UserAuthentication auth;
    vector<int> clientSockets;
    fd_set readfds;

    bool handleRegistration(int clientSocket);
    bool handleLogin(int clientSocket);
    void handleAuthentication(int clientSocket, int option);

    string trim(const string& str);
    string receiveString(int clientSocket);
    void handleClient(int clientSocket, const string& clientName, const string& roomName);


};

#endif // SERVER_H