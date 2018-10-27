/*
 * Copyright (C) 2011 Fredi Machado <https://github.com/fredimachado>
 * IRCClient is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * http://www.gnu.org/licenses/lgpl.html 
 */
#include <time.h>
#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <map>
#include <algorithm>
#include "Thread.h"
#include "IRCClient.h"
#include <sstream>
#include <string>
#include <ctime>
#include <limits>

volatile bool running;
int cnt = 0;
std::string lastusr;
std::map<std::string, std::time_t> smokers;
std::map<std::string, std::time_t> chefs;
std::map<std::string, std::time_t> drinkers;
std::map<std::string, std::time_t> poppers;
std::map<std::string, std::time_t> watchers;
std::map<std::string, std::time_t> listeners;


void signalHandler(int signal)
{
    running = false;
}

class ConsoleCommandHandler
{
public:
    bool AddCommand(std::string name, int argCount, void (*handler)(std::string /*params*/, IRCClient* /*client*/))
    {
        CommandEntry entry;
        entry.argCount = argCount;
        entry.handler = handler;
        std::transform(name.begin(), name.end(), name.begin(), towlower);
        _commands.insert(std::pair<std::string, CommandEntry>(name, entry));
        return true;
    }

    void ParseCommand(std::string command, IRCClient* client)
    {
        if (_commands.empty())
        {
            std::cout << "No commands available." << std::endl;
            return;
        }

        if (command[0] == '/')
            command = command.substr(1); // Remove the slash

        std::string name = command.substr(0, command.find(" "));
        std::string args = command.substr(command.find(" ") + 1);
        int argCount = std::count(args.begin(), args.end(), ' ');

        std::transform(name.begin(), name.end(), name.begin(), towlower);

        std::map<std::string, CommandEntry>::const_iterator itr = _commands.find(name);
        if (itr == _commands.end())
        {
            std::cout << "Command not found." << std::endl;
            return;
        }

        if (++argCount < itr->second.argCount)
        {
            std::cout << "Insuficient arguments." << std::endl;
            return;
        }

        (*(itr->second.handler))(args, client);
    }

private:
    struct CommandEntry
    {
        int argCount;
        void (*handler)(std::string /*arguments*/, IRCClient* /*client*/);
    };

    std::map<std::string, CommandEntry> _commands;
};

ConsoleCommandHandler commandHandler;

void msgCommand(std::string arguments, IRCClient* client)
{
    std::string to = arguments.substr(0, arguments.find(" "));
    std::string text = arguments.substr(arguments.find(" ") + 1);

    std::cout << "To " + to + ": " + text << std::endl;
    client->SendIRC("PRIVMSG " + to + " :" + text);
};

void joinCommand(std::string channel, IRCClient* client)
{
    if (channel[0] != '#')
        channel = "#" + channel;

    client->SendIRC("JOIN " + channel);
}

void partCommand(std::string channel, IRCClient* client)
{
    if (channel[0] != '#')
        channel = "#" + channel;

    client->SendIRC("PART " + channel);
}

void ctcpCommand(std::string arguments, IRCClient* client)
{
    std::string to = arguments.substr(0, arguments.find(" "));
    std::string text = arguments.substr(arguments.find(" ") + 1);

    std::transform(text.begin(), text.end(), text.begin(), towupper);

    client->SendIRC("PRIVMSG " + to + " :\001" + text + "\001");
}

void cmds(IRCMessage message, IRCClient* client)
{
    std::string text = message.parameters.at(message.parameters.size() - 1);
    std::string act;
    if (text[0] == '!')
    {
        std::string act = text.substr(1, text.find(" ") - 1);
        std::string inp = text.substr(text.find(" ") + 1);
        std::string usern = message.prefix.nick;
        if (lastusr == usern)
            ++cnt;
        else
            cnt = 0;
        lastusr = usern;
        if (act == "d")
        {
            if (cnt == 6)
            {
                client->SendIRC("PRIVMSG #mtv :" + usern + ", don't you have your own dice?\r\n");
            }else{
                std::string s = text.substr(3);
                std::stringstream trans(s);
                int x = 0;
                trans >> x;
                if (trans.fail())
                {
                    trans.clear();
                    trans.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    client->SendIRC("PRIVMSG #mtv :" + usern + ", fuck you.\r\n");
                    return;
                }
                if (!trans.fail()) 
                {
                    srand(time(0));
                    int result = (1+(rand()%x));
                    std::string conv = std::to_string(result);
                    client->SendIRC("PRIVMSG #mtv :" + usern + " has rolled a " + conv + ".\r\n");
                    if (result == 420) {
                        client->SendIRC("PRIVMSG #mtv :FOUR TWENTY blaze it fgt! I might be just take a liking to you\r\n");
                    }
                }
            }
        }
        if (act == "ping") {
                if (cnt == 6)
                    client->SendIRC("PRIVMSG #mtv :Leave me alone..\r\n");
                else
                    client->SendIRC("PRIVMSG #mtv :Pong!\r\n");
        }
        if (act == "choose") {
            std::string answer;
            std::string option1 = inp.substr(0, inp.find("or") - 1);
            std::string option2 = inp.substr(inp.find("or") + 3);
                
            srand(time(0));
            int i = (rand()%2);
            if (i == 0)
                answer = option1;
            else
                answer = option2;
            if (cnt == 6)
                client->SendIRC("PRIVMSG #mtv :" + answer + " and eat your elbow.");
            else
                client->SendIRC("PRIVMSG #mtv :" + answer + ".\r\n");
        }
        if (act == "shouldi") {
            std::string answer;
            srand(time(0));
            int i = (rand()%2);
            if (i == 0)
                answer = "Yes.";
            else
                answer = "No.";
            client ->SendIRC("PRIVMSG #mtv :" + answer + "\r\n");
        }
        if (act == "drinkin") {
            std::time_t currtime = std::time(nullptr);
            drinkers.insert(std::pair<std::string, std::time_t>(usern, currtime));
            std::string out;
            std::stringstream trans;
            for (std::map<std::string, std::time_t>::iterator it=drinkers.begin(); it!=drinkers.end(); ++it)
            {
                if (!(it->second < currtime-43200))
                {
                    if (it != std::prev(drinkers.end()))
                        out += it->first + ", ";
                    else 
                        out += it->first + ".";
                }else{
                drinkers.erase(it);
                }
            }
            client ->SendIRC("PRIVMSG #mtv :Another round for " + out + " Cheers!\r\n");
        }
        if (act == "smokin") {
            std::time_t currtime = std::time(nullptr);
            smokers.insert(std::pair<std::string, std::time_t>(usern, currtime));
            std::string out;
            std::stringstream trans;
            for (std::map<std::string, std::time_t>::iterator it=smokers.begin(); it!=smokers.end(); ++it)
            {
                if (!(it->second < currtime-43200))
                {
                    if (it != std::prev(smokers.end()))
                        out += it->first + ", ";
                    else 
                        out += it->first + ".";
                }else{
                smokers.erase(it);
                }
            }
            client ->SendIRC("PRIVMSG #mtv :Another toke for " + out + "\r\n");
        }
        if (act == "watchin") {
            std::time_t currtime = std::time(nullptr);
            watchers.insert(std::pair<std::string, std::time_t>(usern, currtime));
            std::string out;
            for (std::map<std::string, std::time_t>::iterator it=watchers.begin(); it!=watchers.end(); ++it)
            {
                if (!(it->second < currtime-43200))
                {
                    if (watchers.size() == 1)
                        out = it->first + "is ";
                    else if (watchers.size() == 2) {
                        if (it != std::prev(watchers.end()))
                            out = it->first + " and ";
                        else
                            out += it->first + " are";
                    }else{
                    if (it == std::prev(watchers.end(), 2))
                        out += it->first + " and ";
                    if (it == std::prev(watchers.end()))
                        out += it->first + " are";
                    else
                        out += it->first + ", ";
                    }
                }else{
                    watchers.erase(it);
                }
            }
            std::size_t found = inp.find("anime");
            if (found != std::string::npos) {
                client ->SendIRC("PRIVMSG #mtv :" + usern + " is staring into the glassy 2d eyes.\n\r");
            }else{
                client ->SendIRC("PRIVMSG #mtv :" + usern + " turned on the flickerbox.");
            }
            client ->SendIRC("PRIVMSG #mtv :" + out + " watching stuff, probably nothing good.\n\r.");
        }
        return;
    }
}


ThreadReturn inputThread(void* client)
{
    std::string command;

    commandHandler.AddCommand("msg", 2, &msgCommand);
    commandHandler.AddCommand("join", 1, &joinCommand);
    commandHandler.AddCommand("part", 1, &partCommand);
    commandHandler.AddCommand("ctcp", 2, &ctcpCommand);

    while(true)
    {
        getline(std::cin, command);
        if (command == "")
            continue;

        if (command[0] == '/')
            commandHandler.ParseCommand(command, (IRCClient*)client);
        else
            ((IRCClient*)client)->SendIRC(command);

        if (command == "quit")
            break;
    }

#ifdef _WIN32
    _endthread();
#else
    pthread_exit(NULL);
#endif
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Insuficient parameters: host port [nick] [user]" << std::endl;
        return 1;
    }
    char* host = argv[1];
    int port = atoi(argv[2]);
    std::string nick("MyIRCClient");
    std::string user("IRCClient");

    if (argc >= 4)
        nick = argv[3];
    if (argc >= 5)
        user = argv[4];

    IRCClient client;
    client.HookIRCCommand("PRIVMSG", &cmds);

    client.Debug(true);

    // Start the input thread
    Thread thread;
    thread.Start(&inputThread, &client);

    if (client.InitSocket())
    {
        std::cout << "Socket initialized. Connecting..." << std::endl;

        if (client.Connect(host, port))
        {
            std::cout << "Connected. Loggin in..." << std::endl;

            if (client.Login(nick, user))
            {
                std::cout << "Logged." << std::endl;

                running = true;
                signal(SIGINT, signalHandler);

                while (client.Connected() && running)
                    client.ReceiveData();
            }

            if (client.Connected())
                client.Disconnect();

            std::cout << "Disconnected." << std::endl;
        }
    }
}
