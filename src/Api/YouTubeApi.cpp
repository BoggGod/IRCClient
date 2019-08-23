#include "YouTubeApi.h"
#include <cpprest/filestream.h>
#include <cpprest/oauth2.h>


using namespace utility;                    
using namespace web;                        
using namespace web::http;                  
using namespace web::http::client;          
using namespace concurrency::streams;       
using namespace pplx;
YouTubeApi::YouTubeApi()
{
}


YouTubeApi::~YouTubeApi()
{
}

std::string API_KEY = "";
task<http_response> GetYouTubeVideoResponse(std::string videoId){
	 http_client client(U("https://www.googleapis.com/youtube/v3"));

    uri_builder builder(U("/videos"));
    builder.append_query(U("key"), utility::conversions::to_string_t(API_KEY));
    builder.append_query(U("part"), U("snippet,contentDetails,statistics"));
    builder.append_query(U("id"), utility::conversions::to_string_t(videoId));

    return client.request(methods::GET, builder.to_string());
	
	
}

task<YouTubeSearchResult> YouTubeApi::LookupByYouTubeId(std::string videoId) {
    YouTubeSearchResult* result = new YouTubeSearchResult();
    return GetYouTubeVideoResponse(videoId).then([result](http_response response)
    {
        printf("Received response status code:%u\n", response.status_code());
        return response.extract_json();
	}).then([=](web::json::value jsonValue) {
		web::json::object& obj = jsonValue.as_object();

        auto itemsJson = obj["items"].as_array();
        if (itemsJson.size() == 0) {
            return *result;
        }
        this->PopulateYouTubeResultFromSnippetJSON(itemsJson, result);
        result->VideoId = utility::conversions::to_utf8string(videoId);
        result->ViewCount = FormatViewCountNumber(utility::conversions::to_utf8string(itemsJson[0]["statistics"]["viewCount"].as_string()));


        return *result;
    });
    
}

task<YouTubeSearchResult> YouTubeApi::SearchYouTube(std::string query) {
    YouTubeSearchResult* result = new YouTubeSearchResult();
    pplx::task<YouTubeSearchResult> searchRequest;
         http_client client(U("https://www.googleapis.com/youtube/v3"));

        uri_builder builder(U("/search"));
        builder.append_query(U("key"), utility::conversions::to_string_t(API_KEY));
        builder.append_query(U("part"), U("snippet"));
        builder.append_query(U("type"), U("video"));
        builder.append_query(U("q"), utility::conversions::to_string_t(query));
        try {
             searchRequest = client.request(methods::GET, builder.to_string()).then([result](http_response response)
            {
                int responseCode =  response.status_code();
                printf("Received response status code:%u\n", responseCode);
                if(responseCode != 200){
                    cancel_current_task();
                }

                return response.extract_json();
            }).then([=](web::json::value jsonValue) {
                web::json::object& obj = jsonValue.as_object();
                auto items = obj["items"];

                if (items.size() == 0) {
                    cancel_current_task();
                }
                    
                auto itemsArray = items.as_array();


                this->PopulateYouTubeResultFromSnippetJSON(itemsArray, result);
                string_t videoId = itemsArray[0]["id"]["videoId"].as_string();
                result->VideoId = utility::conversions::to_utf8string(videoId);
                return result->VideoId;
            }).then([=](std::string videoId) {
                if (videoId != "") {
					return GetYouTubeVideoResponse(videoId);
                }
                else {
                    throw std::exception();
                }
            }).then([=](http_response responseDos)
            {
                printf("Received response status code:%u\n", responseDos.status_code());
                return responseDos.extract_json();
            }).then([=](web::json::value jsonValue) {
                web::json::object& obj = jsonValue.as_object();
                auto itemsJson = obj["items"].as_array();
                result->ViewCount = FormatViewCountNumber(utility::conversions::to_utf8string(itemsJson[0]["statistics"]["viewCount"].as_string()));
                return *result;
            });

        }
        catch (std::exception ex) {
            return searchRequest;
        }
        return searchRequest;
}

void YouTubeApi::PopulateYouTubeResultFromSnippetJSON(web::json::array itemsJson, YouTubeSearchResult* searchResult) {
    string_t videoTitle = itemsJson[0]["snippet"]["title"].as_string();
    string_t author = itemsJson[0]["snippet"]["channelTitle"].as_string();
    string_t publishedAt = itemsJson[0]["snippet"]["publishedAt"].as_string();

    searchResult->VideoTitle = utility::conversions::to_utf8string(videoTitle);
    searchResult->Author = utility::conversions::to_utf8string(author);
    searchResult->PublishedAt = utility::conversions::to_utf8string(publishedAt).substr(0, 10);
}
