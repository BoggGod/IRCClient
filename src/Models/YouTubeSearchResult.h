#pragma once
#ifndef _YouTubeSearchResult_H
#define _YouTubeSearchResult_H

#include <string>


class YouTubeSearchResult
{
public:
    std::string VideoId;
    std::string VideoTitle;
    std::string Author;
    std::string ViewCount;
    std::string PublishedAt;

    YouTubeSearchResult();
    ~YouTubeSearchResult();
    YouTubeSearchResult(std::string videoId, std::string videoTitle);
};

#endif