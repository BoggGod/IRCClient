#pragma once
#ifndef _YouTubeApi_H
#define _YouTubeApi_H

#include <string>
#include <iostream>
#include <cpprest/http_client.h>
#include "Models/YouTubeSearchResult.h"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

class YouTubeApi
{
private:
    std::string FormatViewCountNumber(std::string viewCount) {
        int insertPosition = viewCount.length() - 3;
        while (insertPosition > 0) {
            viewCount.insert(insertPosition, ",");
            insertPosition -= 3;
        }

        return viewCount;
    }
public:
    YouTubeApi();
    ~YouTubeApi();
    pplx::task<YouTubeSearchResult> SearchYouTube(std::string query);
    void PopulateYouTubeResultFromSnippetJSON(web::json::array itemsJson, YouTubeSearchResult* searchResult);
    pplx::task<YouTubeSearchResult> LookupByYouTubeId(std::string videoId);
};

#endif