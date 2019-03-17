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
#include <cctype>
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
#include <cmath>
#include "Commands.h"
#include "Config.h"
#include <chrono>
#include <thread>
#include <iterator>
#include <vector>
#include "Functions.h"
#include <sys/resource.h>
#include <sys/time.h>

volatile bool running;

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

void joinCommand(std::string channel, IRCClient* client) //does work
{
    if (channel[0] != '#') {
        channel = "#" + channel;
    }
    client->SendIRC("JOIN " + channel);
    std::chrono::milliseconds timespan(1000);
    std::this_thread::sleep_for(timespan);
    std::string code = "\x01";
    std::string output = code + "ACTION" + " screams" + code;
    
    client->SendPrivMsg(channel, output);
}

void partCommand(std::string channel, IRCClient* client) //doesn't appear to work, just parts.
{
    if (channel[0] != '#')
        channel = "#" + channel;
    std::string code = "\x01";
    std::string output = code + "ACTION" + " screams";
    
    client->SendPrivMsg(channel, output);
    client->SendIRC("PART " + channel + "AHHHHHHHHHH");
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

std::string ParseYouTubeVideoId(std::string text) {
    std::string result = "";
    std::regex ytVideoId("(http(s|):|)\/\/(www\.|)yout(.*?)\/(embed\/|watch.*?v=|)([a-z_A-Z0-9\-]{11})");
    std::smatch matches;

    regex_search(text, matches, ytVideoId);
    if (matches.size() >= 7) {
        result = matches[6];
    }


    return result;

}

void cmds(IRCMessage message, IRCClient* client)
{
    client->Spamcheck();
    if (client->spamflag)
        return;
    std::string text = message.parameters.at(message.parameters.size() - 1);
	std::string chan = message.parameters.at(0);
	std::string usern = message.prefix.nick;
	//Checking for a youtube video anywhere in the message text
	std::string videoId = ParseYouTubeVideoId(text);
    
	if (videoId  != "") {
		YouTubeCommand ytCommand = YouTubeCommand();
		ytCommand.ParseVideoId(videoId, chan, client);

	}

    if ((text[0] == '!') || (text[0] == '.'))
    {
        //initilization of message processing
        client->Checktime();
        std::string act = "";
        std::string inp = "";
        if (text.find(" ") == text.npos)
        {
            try {
                act = text.substr(1);
                std::transform(act.begin(), act.end(), act.begin(),
                [](unsigned char c){ return std::tolower(c); }
                );
            }
                catch (const std::out_of_range& oor) {
                    act = "";
                }
        } else {
            act = text.substr(1, text.find(" ") - 1);
            std::transform(act.begin(), act.end(), act.begin(),
            [](unsigned char c){ return std::tolower(c); }
            );
            try {
                inp = text.substr(text.find(" ") + 1);
            }
            catch (const std::out_of_range& oor) {
                inp = "";
            }
        }
        std::string chan = message.parameters.at(0);
        std::string usern = message.prefix.nick;
        //std::string isChanstr = message.parameters[0];
        bool isChannel = chan[0] == '#';
        if (!isChannel)
            chan = usern;
        else
            client->lastuser = usern;
        //++client->annoyance;
        
        //selecting and processing called command
        if (act == "flavor") {
            FlavorCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "quote" || act == "record") {
            QuoteCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "shouldi") {
            ShouldiCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "setinfo")
        {
            SetinfoCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "desc")
        {
            DescCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "wah")
        {
            WahCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "cat")
        {
            CatCommand command;
            command.Execute(client, inp, usern, chan);
        }
        /*if (act == "wotd")
        {
            WotdCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "dyk")
        {
            DykCommand command;
            command.Execute(client, inp, usern, chan);
        }
        */
        if (act == "d")
        {/*
            if (annoyance >= 6)
            {
                client->SendIRC("PRIVMSG " + chan + " :" + usern + "?\r\n");
                annoyance = 0;
            }else{
                */
                    if (!inp.empty()) {
                        DiceCommand command;
                        command.Execute(client, inp, usern, chan);
                    }
        }
        if (act == "ping") {
                /*if (annoyance == 6)
                    client->SendIRC("PRIVMSG " + chan + " :Leave me alone..\r\n");
                else */
                    client->SendIRC("PRIVMSG " + chan + " :Pong!\r\n");
        }
        if (act == "sms") {
            SmsCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "cookie") {
            CookieCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "inventory") {
            InventoryCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "8ball") {
            EightBallCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "choose") {
            ChooseCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "shittaste") {
            ShittasteCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "readin") {
            ReadinCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "listenin") {
            ListeninCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "poopin") {
            PoopinCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "gamin" || act == "playin") {
            GaminCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "nommin" || act == "nomin") {
            NomminCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "bikin") {
            BikinCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "sleepin") {
            SleepinCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "drinkin") {
            DrinkinCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "smokin") {
            SmokinCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "watchin") {
            WatchinCommand command;
            command.Execute(client, inp, usern, chan);
        }
        if (act == "yt") {
            YouTubeCommand command;
            command.Execute(client, inp, usern, chan);
        }
		

        
        if (act == "namaste") {
            std::string theresponse = client->Response("namaste");
            client->SendPrivMsg(chan, theresponse);
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
    rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
    
    char* host = BotConfig::Host;
    int port = BotConfig::Port;
    
    std::string nick(BotConfig::Nickname);
    std::string user(BotConfig::User);
    std::string chan = BotConfig::Channel;
    std::string sms = "smsFile";
    std::string desc = "DescribeFile";
    std::string desc2 = "DescribeBackup";
    std::string set = "UserInfoMap";
    std::string set2 = "UserInfoBackup";
    std::string inv = "Inventories";
    std::string quote = "Quotes";
    std::string flavors = "Flavor_lines";
    
    if (argc >= 4)
        nick = argv[3];
    if (argc >= 5)
        user = argv[4];
    IRCClient client;
    client.HookIRCCommand("PRIVMSG", &cmds);
    // initialize userinfos from file
    client.InitData(sms, desc, set, inv, quote, flavors, set2, desc2); // load inventory via initdata -> inv.init
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
