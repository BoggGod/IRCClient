#include "YouTubeCommand.h"
std::string GetMessageForChat(YouTubeSearchResult result){
	std::string message = "https://youtu.be/" + result.VideoId + " [" + result.VideoTitle + "] date[" + result.PublishedAt + "] views[" + result.ViewCount + "] author[" + result.Author + "]";
	return message;	
}


void YouTubeCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
	YouTubeApi ytApi = YouTubeApi();

	ytApi.SearchYouTube(input).then([client, channel](YouTubeSearchResult result) {
		    std::string message = GetMessageForChat(result);
			client->SendPrivMsg(channel, message);

	 });
}

void YouTubeCommand::ParseVideoId(std::string videoId, std::string msgSender, IRCClient* client){
	YouTubeApi ytApi;
	ytApi.LookupByYouTubeId(videoId).then([client, msgSender](YouTubeSearchResult result) {
		if (result.VideoTitle != "")
		{
			std::string message = GetMessageForChat(result);
			client->SendPrivMsg(msgSender, message);
		}
	});
	
}



YouTubeCommand::YouTubeCommand()
{
}


YouTubeCommand::~YouTubeCommand()
{
}
