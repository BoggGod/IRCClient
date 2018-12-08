#ifndef _YouTubeCommand_H
#define _YouTubeCommand_H

#include "Command.h" 
#include "Api/YouTubeApi.h"

class YouTubeCommand : Command
{

public:
	YouTubeCommand();
	~YouTubeCommand();
	void ParseVideoId(std::string videoId, std::string msgSender, IRCClient* client);
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
