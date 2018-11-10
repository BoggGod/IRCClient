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
#include <fstream>
#include <signal.h>
#include <cstdlib>
#include <map>
#include <algorithm>
#include "Thread.h"
#include "IRCClient.h"
#include "Vars.h"
#include <sstream>
#include <string>
#include <ctime>
#include <limits>
#include <cmath>
#include "Commands.h"
#include "Config.h"
#include <chrono>
#include <thread>
#include <iterator>
#include <vector>
#include "Functions.h"

using namespace Global;

volatile bool running;

std::string chan;
std::string lastusr;
std::map<std::string, int> bank;
std::map<std::string, int> luck;
std::map<std::string, std::pair<int, double>> loans;


//flavor texts
std::vector<std::pair<std::string, std::string>> insults;
std::vector<std::pair<std::string, std::string>> leaves;

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
    if (channel[0] != '#') {
        channel = "#" + channel;
    }
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

/*
void luck_decay()
{
    for (auto &u : loans)
    {
        loans[w] -= ((loans[w] / 100) * 10);
        
        if w 
    }
    
void interest()
{
}

void newday()
{
    luck_decay();
    interest();
}

void 
*/

/*std::string say(std::string response)
{
    std::string result;
    result = "PRIVMSG " + chan + " :" + response + "\r\n";
    return result;
}
*/

void refMap(/* void */)
{
    for (std::map<std::string, std::time_t>::iterator it=watchers.begin(); it!=watchers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            watchers.erase(it);
    }
        for (std::map<std::string, std::time_t>::iterator it=smokers.begin(); it!=smokers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            smokers.erase(it);
    }
        for (std::map<std::string, std::time_t>::iterator it=drinkers.begin(); it!=drinkers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            smokers.erase(it);
    }
    return;
}


void checktime(/* void */)
{
    if (currtime - daystart >= 86400)
        daystart = currtime;
    if (currtime - daystart >= 43200)
    {
        sixhcycle = currtime;
        refMap();
    }
    return;
}

        
    
void annoyed(IRCClient* client, std::string &mischief)
{
    std::string response = "is an elbow muncher.";
    mischief == lastusr ? ++annoyance : annoyance = 0;
    if (annoyance >= 6) {
        client->SendIRC("PRIVMSG " + chan + " :" + mischief + " " + response);
        annoyance = 0;
    }else{
        return;
    }
}

/* Not needed at the moment
void tests(IRCMessage message, IRCClient* client)
{
    std::string text = message.parameters.at(message.parameters.size() - 1);
    if ((text == "testing") || (text == "joined")) {
        //   client->SendIRC(say("testing"));
        client->SendIRC("PRIVMSG " + chan + " :that's inside: " + chan + "\r\n");
        client->SendIRC("PRIVMSG " + chan + " :that's inside: " + message.parameters.at(1) + "\r\n");
        client->SendIRC("PRIVMSG " + chan + " :that's inside: " + message.parameters.at(2) + "\r\n");
        client->SendIRC("PRIVMSG " + chan + " :that's inside: " + message.parameters.at(3) + "\r\n");
        client->SendIRC("PRIVMSG " + chan + " :that's inside: " + message.parameters.at(4) + "\r\n");
        
    }
    return;
}
*/

/* not needed at the moment
std::string convert()
{
    std:: string tocon = "convert successful";
    return tocon;
}
*/

void cmds(IRCMessage message, IRCClient* client)
{
    std::string text = message.parameters.at(message.parameters.size() - 1);
    if ((text[0] == '!') || (text[0] == '.'))
    {
        
        currtime = std::time(nullptr);
        checktime();
        std::string act = text.substr(1, text.find(" ") - 1);
        std::string inp = text.substr(text.find(" ") + 1);
        std::string chan = message.parameters.at(0);
        std::string usern = message.prefix.nick;
        annoyed(client, usern);
        lastusr = usern;
     // bool isChannel = usern[0] == '#';
     //  if (!isChannel) return;
        
        if (act == "shouldi") {
            ShouldiCommand* command = new ShouldiCommand();
            command->Execute(client, inp, usern, chan);
            delete command;
        }
        if (act == "setinfo")
        {
            SetinfoCommand* command = new SetinfoCommand();
            command->Execute(client, inp, usern, chan);
            delete command;
        }
        if (act == "d")
        {
            if (annoyance >= 6)
            {
                client->SendIRC("PRIVMSG " + chan + " :" + usern + "?\r\n");
                annoyance = 0;
            }else{
                    if (!inp.empty()) {
                        DiceCommand* command = new DiceCommand();
                        command->Execute(client, inp, usern, chan);
                        delete command;
                    }
                }
        }
        if (act == "ping") {
                if (annoyance == 6)
                    client->SendIRC("PRIVMSG " + chan + " :Leave me alone..\r\n");
                else
                    client->SendIRC("PRIVMSG " + chan + " :Pong!\r\n");
        }
        if (act == "choose") {
            ChooseCommand* command = new ChooseCommand();
            command->Execute(client, inp, usern, chan);
            delete command;
        }
        if (act == "shittaste") {
            DrinkinCommand* command = new DrinkinCommand();
            command->Execute(client, inp, usern, chan);
            delete command;
        }

        if (act == "drinkin") {
            DrinkinCommand* command = new DrinkinCommand();
            command->Execute(client, inp, usern, chan);
            delete command;
        }
        if (act == "smokin") {
            SmokinCommand* command = new SmokinCommand();
            command->Execute(client, inp, usern, chan);
            delete command;
        }
        if (act == "watchin") {
            WatchinCommand* command = new WatchinCommand();
            command->Execute(client, inp, usern, chan);
            delete command;
        }
        
        if (act == "namaste") {
            client->SendIRC("PRIVMSG " + chan + " :With the goodness inside, to always be thankful for what we have, and those around of us. To look forward with positive energy, for health and well-being. With this intention, EXU-POLOSION!");
        }
        //move this to enter a name when starting the program that is admin
        if ((act == "leave") && (usern == "/* not defined yet */")) {
            std::string response = "As you wish.";
            //client->SendIRC(say(response));
            //client->SendIRC(say("As you wish."));
            client->SendIRC("PRIVMSG " + chan + " :" + response + "\r\n");
            client ->SendIRC("PART " +  chan);
        }
    }
        //testing space
    
    return;
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
    char* host = BotConfig::Host;
    int port = BotConfig::Port;
    std::string nick(BotConfig::Nickname);
    std::string user(BotConfig::User);
    
    if (argc >= 4)
        nick = argv[3];
    if (argc >= 5)
        user = argv[4];
    sixhcycle = std::time(nullptr);
    daystart = std::time(nullptr);
    IRCClient client;
    client.HookIRCCommand("PRIVMSG", &cmds);
    // initialize userinfos from file
    writeMap(setinfos, setinfoFile);
    
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
                bool joined = false;
                while (client.Connected() && running) {
                    if (!joined) {
                        std::chrono::milliseconds timespan(10000);
                        std::this_thread::sleep_for(timespan);
                        joinCommand(BotConfig::Channel, &client);
                        joined = true;
                    }
                    client.ReceiveData();
                }
            }

            if (client.Connected())
                client.Disconnect();

            std::cout << "Disconnected." << std::endl;
        }
    }
}
