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

#include <iostream>
#include <algorithm>
#include "IRCSocket.h"
#include "IRCClient.h"
#include "IRCHandler.h"

std::vector<std::string> split(std::string const& text, char sep)
{
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

void IRCClient::InitData(const std::string &sms, const std::string &d,
const std::string &set, const std::string &inv, const std::string &q,
const std::string &flav, const std::string &set2, const std::string &d2)
{
    this->last_post = std::time(nullptr);
    this->smsFile = sms;
    this->descFile = d;
    this->descFile2 = d2;
    this->setFile = set;
    this->setFile = set2;
    this->invFile = inv;
    this->quotes = q;
    this->flavFile = flav;
    writeMap(this->setMap, this->setFile);
    writeMap(this->setMap2, this->setFile2);
    writeMap(this->descMap, this->descFile);
    writeMap(this->descMap2, this->descFile2);
    fileToSmsMap(this->smsMap, this->smsFile);
    LoadFlav(this->flavs, this->flavFile);
    LoadInv(this->invMap, this->invFile);
    LoadVec(this->wotds, this->wotdsFile);
    LoadVec(this->dyks, this->dyksFile);
    LoadVec(this->wahs, this->wahsFile);
    LoadVec(this->treasure, this->quotes);
    this->sixhcycle = std::time(nullptr);
    this->daystart = std::time(nullptr);
}

std::string IRCClient::Response(const std::string &c)
{
    srand(time(0));
    int i = (rand() % this->flavs[c].size());
    return this->flavs[c][i];
}

void IRCClient::RefMap(/* void */)
{
    std::time_t currtime = std::time(nullptr);
    for (auto &m : this->flavMap) {
        for (auto &m2 : m.second) {
            if (currtime - m2.second >= 43200)
                m.second.erase(m2.first);
        }
    }
}

void IRCClient::Checktime(/* void */)
{
    std::time_t currtime = std::time(nullptr);
    if (currtime - this->daystart >= 86400)
        this->daystart = currtime;
    if (currtime - this->sixhcycle >= 43200) //43200
    {
        sixhcycle = currtime;
        this->RefMap();
    }
    return;
}

void IRCClient::Spamcheck(/* void */)
{
    std::time_t current_time = std::time(nullptr);
    std::time_t time_passed = current_time - this->last_post;
    if (time_passed < 1)
        this->spamflag = true;
    else
        this->spamflag = false;
    this->last_post = current_time;
}


bool IRCClient::InitSocket()
{
    return _socket.Init();
}

bool IRCClient::Connect(char* host, int port)
{
    return _socket.Connect(host, port);
}

void IRCClient::Disconnect()
{
    _socket.Disconnect();
}

bool IRCClient::SendIRC(std::string data)
{
    data.append("\n");
    return _socket.SendData(data.c_str());
}

bool IRCClient::SendPrivMsg(std::string destination, std::string data)
{
    std::string message = "PRIVMSG " + destination + " :" + data;
    return this->SendIRC(message);
}

bool IRCClient::Login(std::string nick, std::string user, std::string password)
{
    _nick = nick;
    _user = user;

    if (SendIRC("HELLO"))
    {
        if (!password.empty() && !SendIRC("PASS "+password))
            return false;
        if (SendIRC("NICK " + nick))
            if (SendIRC("USER " + user + " 8 * :Cpp IRC Client"))
                return true;
    }

    return false;
}

void IRCClient::ReceiveData()
{
    std::string buffer = _socket.ReceiveData();

    std::string line;
    std::istringstream iss(buffer);
    while(getline(iss, line))
    {
        if (line.find("\r") != std::string::npos)
            line = line.substr(0, line.size() - 1);
        Parse(line);
    }
}

void IRCClient::Parse(std::string data)
{
    std::string original(data);
    IRCCommandPrefix cmdPrefix;

    // if command has prefix
    if (data.substr(0, 1) == ":")
    {
        cmdPrefix.Parse(data);
        data = data.substr(data.find(" ") + 1);
    }

    std::string command = data.substr(0, data.find(" "));
    std::transform(command.begin(), command.end(), command.begin(), towupper);
    if (data.find(" ") != std::string::npos)
        data = data.substr(data.find(" ") + 1);
    else
        data = "";

    std::vector<std::string> parameters;

    if (data != "")
    {
        if (data.substr(0, 1) == ":")
            parameters.push_back(data.substr(1));
        else
        {
            size_t pos1 = 0, pos2;
            while ((pos2 = data.find(" ", pos1)) != std::string::npos)
            {
                parameters.push_back(data.substr(pos1, pos2 - pos1));
                pos1 = pos2 + 1;
                if (data.substr(pos1, 1) == ":")
                {
                    parameters.push_back(data.substr(pos1 + 1));
                    break;
                }
            }
            if (parameters.empty())
                parameters.push_back(data);
        }
    }

    if (command == "ERROR")
    {
        std::cout << original << std::endl;
        Disconnect();
        return;
    }

    if (command == "PING")
    {
        std::cout << "Ping? Pong!" << std::endl;
        SendIRC("PONG :" + parameters.at(0));
        return;
    }

    IRCMessage ircMessage(command, cmdPrefix, parameters);

    // Default handler
    int commandIndex = GetCommandHandler(command);
    if (commandIndex < NUM_IRC_CMDS)
    {
        IRCCommandHandler& cmdHandler = ircCommandTable[commandIndex];
        (this->*cmdHandler.handler)(ircMessage);
    }
    else if (_debug)
        std::cout << original << std::endl;

    // Try to call hook (if any matches)
    CallHook(command, ircMessage);
}

void IRCClient::HookIRCCommand(std::string command, void (*function)(IRCMessage /*message*/, IRCClient* /*client*/))
{
    IRCCommandHook hook;

    hook.command = command;
    hook.function = function;

    _hooks.push_back(hook);
}

void IRCClient::CallHook(std::string command, IRCMessage message)
{
    if (_hooks.empty())
        return;

    for (std::list<IRCCommandHook>::const_iterator itr = _hooks.begin(); itr != _hooks.end(); ++itr)
    {
        if (itr->command == command)
        {
            (*(itr->function))(message, this);
            break;
        }
    }
}
