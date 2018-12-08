#include "YouTubeSearchResult.h"

YouTubeSearchResult::~YouTubeSearchResult()
{
}

YouTubeSearchResult::YouTubeSearchResult() 
{
}

YouTubeSearchResult::YouTubeSearchResult(std::string videoId, std::string videoTitle) : VideoId(videoId), VideoTitle(videoTitle), Author(""), ViewCount(0), PublishedAt("")
{

}