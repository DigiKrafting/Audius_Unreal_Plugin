/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

/*

The Audius API is entirely free to use. We ask that you adhere to the guidelines in this doc https://audiusproject.github.io/api-docs/#audius-api-docs and always credit artists.

*/

#include "Audius_API.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"

TArray<FString> UAudius_API::Genres = {
    TEXT("All"),
    TEXT("Acoustic"),
    TEXT("Alternative"),
    TEXT("Ambient"),
    TEXT("Audiobooks"),
    TEXT("Blues"),
    TEXT("Classical"),
    TEXT("Comedy"),
    TEXT("Country"),
    TEXT("Deep House"),
    TEXT("Devotional"),
    TEXT("Disco"),
    TEXT("Downtempo"),
    TEXT("Drum & Bass"),
    TEXT("Dubstep"),
    TEXT("Electro"),
    TEXT("Electronic"),
    TEXT("Experimental"),
    TEXT("Folk"),
    TEXT("Funk"),
    TEXT("Future Bass"),
    TEXT("Future House"),
    TEXT("Glitch Hop"),
    TEXT("Hardstyle"),
    TEXT("Hip-Hop/Rap"),
    TEXT("House"),
    TEXT("Hyperpop"),
    TEXT("Jazz"),
    TEXT("Jersey Club"),
    TEXT("Jungle"),
    TEXT("Kids"),
    TEXT("Latin"),
    TEXT("Lo-Fi"),
    TEXT("Metal"),
    TEXT("Moombahton"),
    TEXT("Podcasts"),
    TEXT("Pop"),
    TEXT("Progressive House"),
    TEXT("Punk"),
    TEXT("R&B/Soul"),
    TEXT("Reggae"),
    TEXT("Rock"),
    TEXT("Soundtrack"),
    TEXT("Spoken Word"),
    TEXT("Tech House"),
    TEXT("Techno"),
    TEXT("Trance"),
    TEXT("Trap"),
    TEXT("Tropical House"),
    TEXT("Vaporwave"),
    TEXT("World")
};

TArray<FString> UAudius_API::Official_Playlists = {
    TEXT("https://audius.co/Audius/playlist/hot-new-on-audius%F0%9F%94%A5"),
    TEXT("https://audius.co/Audius/playlist/audius-community-playlist"),
    TEXT("https://audius.co/Audius/playlist/official-audius-exclusives"),
    TEXT("https://audius.co/Audius/playlist/black-voices-8313")
};

UAudius_API::UAudius_API(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

/*
https://audiusproject.github.io/api-docs/#get-track
*/

FAudius_Track_Struct UAudius_API::Track_Parse_Json(const TSharedPtr<FJsonObject> Track_Json_Object) {

    FAudius_Track_Struct Audius_Track_Data;

    const TSharedPtr<FJsonObject> _data_artwork = Track_Json_Object->GetObjectField(TEXT("artwork"));
    const TSharedPtr<FJsonObject> _data_user = Track_Json_Object->GetObjectField(TEXT("user"));
    const TSharedPtr<FJsonObject> _data_remix_of = Track_Json_Object->GetObjectField(TEXT("remix_of"));

    Audius_Track_Data.Api_Track_Data.artwork.url_150x150 = *_data_artwork->GetStringField(TEXT("150x150"));
    Audius_Track_Data.Api_Track_Data.artwork.url_480x480 = *_data_artwork->GetStringField(TEXT("480x480"));
    Audius_Track_Data.Api_Track_Data.artwork.url_1000x1000 = *_data_artwork->GetStringField(TEXT("1000x1000"));
    
    Audius_Track_Data.Api_Track_Data.description = Track_Json_Object->GetStringField(TEXT("description"));
    Audius_Track_Data.Api_Track_Data.genre = Track_Json_Object->GetStringField(TEXT("genre"));
    Audius_Track_Data.Api_Track_Data.id = Track_Json_Object->GetStringField(TEXT("id"));
    Audius_Track_Data.Api_Track_Data.track_cid = Track_Json_Object->GetStringField(TEXT("track_cid"));
    Audius_Track_Data.Api_Track_Data.mood = Track_Json_Object->GetStringField(TEXT("mood"));
    Audius_Track_Data.Api_Track_Data.release_date = Track_Json_Object->GetStringField(TEXT("release_date"));
    
    _data_remix_of->TryGetStringArrayField(TEXT("tracks"), Audius_Track_Data.Api_Track_Data.remix_of.tracks);

    Audius_Track_Data.Api_Track_Data.repost_count = Track_Json_Object->GetIntegerField(TEXT("repost_count"));
    Audius_Track_Data.Api_Track_Data.favorite_count = Track_Json_Object->GetIntegerField(TEXT("favorite_count"));
    
    Audius_Track_Data.Api_Track_Data.tags = Track_Json_Object->GetStringField(TEXT("tags"));
    Audius_Track_Data.Api_Track_Data.title = Track_Json_Object->GetStringField(TEXT("title"));
    
    Audius_Track_Data.Api_Track_Data.user.album_count = _data_user->GetIntegerField(TEXT("album_count"));
    Audius_Track_Data.Api_Track_Data.user.artist_pick_track_id = *_data_user->GetStringField(TEXT("artist_pick_track_id"));
    Audius_Track_Data.Api_Track_Data.user.bio = *_data_user->GetStringField(TEXT("bio"));

    const TSharedPtr<FJsonObject>* _data_user_cover_photo;

    if (_data_user->TryGetObjectField(TEXT("cover_photo"), _data_user_cover_photo)){

        Audius_Track_Data.Api_Track_Data.user.cover_photo.url_640x = *(*_data_user_cover_photo)->GetStringField(TEXT("640x"));
        Audius_Track_Data.Api_Track_Data.user.cover_photo.url_2000x = *(*_data_user_cover_photo)->GetStringField(TEXT("2000x"));
        
    }
        
    Audius_Track_Data.Api_Track_Data.user.followee_count = _data_user->GetIntegerField(TEXT("followee_count"));
    Audius_Track_Data.Api_Track_Data.user.follower_count = _data_user->GetIntegerField(TEXT("follower_count"));
    Audius_Track_Data.Api_Track_Data.user.handle = *_data_user->GetStringField(TEXT("handle"));
    Audius_Track_Data.Api_Track_Data.user.id = *_data_user->GetStringField(TEXT("id"));
    Audius_Track_Data.Api_Track_Data.user.is_verified = _data_user->GetBoolField(TEXT("is_verified"));
    Audius_Track_Data.Api_Track_Data.user.location = *_data_user->GetStringField(TEXT("location"));
    Audius_Track_Data.Api_Track_Data.user.name = *_data_user->GetStringField(TEXT("name"));
    Audius_Track_Data.Api_Track_Data.user.playlist_count = _data_user->GetIntegerField(TEXT("playlist_count"));

    const TSharedPtr<FJsonObject>* _data_user_profile_picture;

    if (_data_user->TryGetObjectField(TEXT("profile_picture"), _data_user_profile_picture)) {
        
        Audius_Track_Data.Api_Track_Data.user.profile_picture.url_150x150 = *(*_data_user_profile_picture)->GetStringField(TEXT("150x150"));
        Audius_Track_Data.Api_Track_Data.user.profile_picture.url_480x480 = *(*_data_user_profile_picture)->GetStringField(TEXT("480x480"));
        Audius_Track_Data.Api_Track_Data.user.profile_picture.url_1000x1000 = *(*_data_user_profile_picture)->GetStringField(TEXT("1000x1000"));

    }
    
    Audius_Track_Data.Api_Track_Data.user.repost_count = _data_user->GetIntegerField(TEXT("repost_count"));
    Audius_Track_Data.Api_Track_Data.user.track_count = _data_user->GetIntegerField(TEXT("track_count"));
    Audius_Track_Data.Api_Track_Data.user.is_deactivated = _data_user->GetBoolField(TEXT("is_deactivated"));
    Audius_Track_Data.Api_Track_Data.user.is_available = _data_user->GetBoolField(TEXT("is_available"));
    Audius_Track_Data.Api_Track_Data.user.erc_wallet = *_data_user->GetStringField(TEXT("erc_wallet"));
    Audius_Track_Data.Api_Track_Data.user.spl_wallet = *_data_user->GetStringField(TEXT("spl_wallet"));
    Audius_Track_Data.Api_Track_Data.user.supporter_count = _data_user->GetIntegerField(TEXT("supporter_count"));
    Audius_Track_Data.Api_Track_Data.user.supporting_count = _data_user->GetIntegerField(TEXT("supporting_count"));
    Audius_Track_Data.Api_Track_Data.user.total_audio_balance = _data_user->GetIntegerField(TEXT("total_audio_balance"));
    
    Audius_Track_Data.Api_Track_Data.duration = Track_Json_Object->GetNumberField(TEXT("duration"));
    Audius_Track_Data.Api_Track_Data.is_downloadable = Track_Json_Object->GetBoolField(TEXT("is_downloadable"));;
    Audius_Track_Data.Api_Track_Data.play_count = Track_Json_Object->GetNumberField(TEXT("play_count"));
    Audius_Track_Data.Api_Track_Data.permalink = Track_Json_Object->GetStringField(TEXT("permalink"));
    Audius_Track_Data.Api_Track_Data.is_streamable = Track_Json_Object->GetBoolField(TEXT("is_streamable"));
        
    Audius_Track_Data.Track_Id = Audius_Track_Data.Api_Track_Data.id;
    Audius_Track_Data.Track_Title = Audius_Track_Data.Api_Track_Data.title;
    Audius_Track_Data.Track_Artist = *Audius_Track_Data.Api_Track_Data.user.name;
    Audius_Track_Data.Track_Stream_Url = FString::Printf(TEXT("%s/v1/tracks/%s/stream?app_name=%s"), *Cache_Endpoints[Endpoint_Index], *Audius_Track_Data.Api_Track_Data.id, *FGenericPlatformHttp::UrlEncode(*Audius_API_App_Name));
    Audius_Track_Data.Track_Artwork_Url = *Audius_Track_Data.Api_Track_Data.artwork.url_480x480;
    
    return Audius_Track_Data;

}

TArray<FAudius_Track_Struct> UAudius_API::Tracks_Parse_Json(const TArray<TSharedPtr<FJsonValue>>*& Data_Json_Array) {
    
    TArray<FAudius_Track_Struct> Audius_Tracks_Data;

    for (const TSharedPtr<FJsonValue>& Track_Json : *Data_Json_Array) {

        FAudius_Track_Struct Audius_Track_Data = Track_Parse_Json(Track_Json->AsObject());

        if(Audius_Track_Data.Api_Track_Data.is_streamable) {

            Audius_Tracks_Data.Add(Audius_Track_Data);
            
        }
        
    }

    return Audius_Tracks_Data;
    
}

void UAudius_API::Endpoints() {
    
    FHttpModule& httpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = httpModule.CreateRequest();

    Request->SetURL(TEXT("https://api.audius.co"));
    Request->SetVerb("GET");
    Request->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Endpoints_Data);
    Request->ProcessRequest();
    
}

void UAudius_API::Endpoints_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {

    if (bWasSuccessful) {

        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
        FJsonSerializer::Deserialize(JsonReader, JsonObject);

        if(JsonObject->TryGetStringArrayField(TEXT("data"), Cache_Endpoints)) {
            
            if (Endpoints_Data_Received.IsBound()) {
            
                Endpoints_Data_Received.Broadcast(Cache_Endpoints);
            
            }

        }
        
    } else {
        
        if (Endpoints_Data_Error.IsBound()) {
            
            Endpoints_Data_Error.Broadcast(Response->GetURL());
            
        }
        
    }

}

FString UAudius_API::Endpoint_Node_Replace(FString Audius_Api_Url) {

    if(Endpoint_Index < Cache_Endpoints.Num()){
        Endpoint_Index = Endpoint_Index + 1;
    } else {
        Endpoint_Index = 0;  
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Audius_API::Endpoint_Node_Replace::Current_URL::[%s]"), *Audius_Api_Url);
            
    int32 Query_Start_Index = Audius_Api_Url.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromStart, 8); // skip "https://"
    FString Url_Query = Audius_Api_Url.RightChop(Query_Start_Index);

    UE_LOG(LogTemp, Warning, TEXT("Audius_API::Endpoint_Node_Replace:Url_Query::[%s]"), *Url_Query);

    const FString New_Node_Url = FString::Printf(TEXT("%s%s"), *Cache_Endpoints[Endpoint_Index], *Url_Query);
            
    UE_LOG(LogTemp, Warning, TEXT("Audius_API::Endpoint_Node_Replace:New_Url::[%s]"), *New_Node_Url);
    
    return New_Node_Url;
        
}

void UAudius_API::Endpoint_Next_Node() {
       
    if(Endpoint_Index + 1 < Cache_Endpoints.Num()){

        Endpoint_Index = Endpoint_Index + 1;

    } else {

        Endpoint_Index = 0;
        
    }
        
}

FString UAudius_API::Track_Stream_Url(FAudius_Track_Struct Audius_Track_Data) {

    FString Audius_Stream_Url = FString::Printf(TEXT("%s/v1/tracks/%s/stream?app_name=%s"), *Cache_Endpoints[Endpoint_Index], *Audius_Track_Data.Api_Track_Data.id, *FGenericPlatformHttp::UrlEncode(*Audius_API_App_Name));

    UE_LOG(LogTemp, Warning, TEXT("Audius_API::Track_Stream_Url::[%s]"), *Audius_Stream_Url);

    return Audius_Stream_Url;
        
}

FString UAudius_API::Validate_Data(FString Data_Json_String) {
    
    Data_Json_String = Data_Json_String.Replace(TEXT(": null"), TEXT(": \"\""));

    return Data_Json_String;
        
}

void UAudius_API::Resolve(FString audius_url) {

    FHttpModule& httpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = httpModule.CreateRequest();

    FString _request_url = FString::Printf(TEXT("%s/v1/resolve?url=%s&app_name=%s"), *Cache_Endpoints[Endpoint_Index], *audius_url, *FGenericPlatformHttp::UrlEncode(*Audius_API_App_Name));

    UE_LOG(LogTemp, Warning, TEXT("Audius_API::Resolve::[%s]"), *_request_url);
    
    Request->SetURL(_request_url);
    Request->SetVerb("GET");
    Request->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Resolve_Data);
    Request->ProcessRequest();
    
}

void UAudius_API::Resolve_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {

    if (bWasSuccessful) {

        //UE_LOG(LogTemp, Warning, TEXT("Audius_API::Resolve_Data::[%s]"), *Response->GetContentAsString());

        FString Request_Content = Validate_Data(Response->GetContentAsString());
        
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Request_Content);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);
        
        bool is_playlist = Request->GetURL().Contains(FString("/playlist/"));

        if (is_playlist == false) {

            const TSharedPtr<FJsonObject>* API_Data_Json;

            if (JsonObject->TryGetObjectField(TEXT("data"), API_Data_Json)) {
              
                FAudius_Track_Struct Audius_Track_Data = Track_Parse_Json(*API_Data_Json);
                
                if (Track_Data_Received.IsBound()) {

                    Track_Data_Received.Broadcast(Audius_Track_Data);

                }

                if (Tracks_Data_Received.IsBound()) {
                    
                    TArray<FAudius_Track_Struct> Audius_Tracks_Data;

                    Audius_Tracks_Data.Add(Audius_Track_Data);

                    Tracks_Data_Received.Broadcast(Audius_Tracks_Data);

                }
                
            }

        } else {

            const TArray<TSharedPtr<FJsonValue>>* API_Data_Json;

            if (JsonObject->TryGetArrayField(TEXT("data"), API_Data_Json)) {

                TSharedPtr<FJsonValue> Playlist_Json = (*API_Data_Json)[0];

                const TSharedPtr<FJsonObject> Data_Playlist_Object = Playlist_Json->AsObject();

                FString _playlist_url = FString::Printf(TEXT("%s/v1/playlists/%s/tracks?app_name=%s"), *Cache_Endpoints[Endpoint_Index], *Data_Playlist_Object->GetStringField(TEXT("id")), *FGenericPlatformHttp::UrlEncode(*Audius_API_App_Name));

                FHttpModule& httpModule = FHttpModule::Get();
                TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request_Playlist = httpModule.CreateRequest();
                Request_Playlist->SetURL(_playlist_url);
                Request_Playlist->SetVerb("GET");
                Request_Playlist->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Playlist_Data);
                Request_Playlist->ProcessRequest();

            }

        }

        Resolve_Data_Retry_Index = 0;
        
    } else {
        
        if(Resolve_Data_Retry_Index + 1 < Data_Retry_Tries) {

            Resolve_Data_Retry_Index = Resolve_Data_Retry_Index + 1;
            
            FString Next_Node_Url = Endpoint_Node_Replace(Response->GetURL());
            
            FHttpModule& httpModule = FHttpModule::Get();
            TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request_Retry = httpModule.CreateRequest();
            Request_Retry->SetURL(Next_Node_Url);
            Request_Retry->SetVerb("GET");
            Request_Retry->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Resolve_Data);
            Request_Retry->ProcessRequest();
            
        } else {
            
            Resolve_Data_Retry_Index = 0;

            if (Resolve_Data_Error.IsBound()) {
            
                Resolve_Data_Error.Broadcast(Response->GetURL());
            
            }

            if (Tracks_Data_Error.IsBound()) {

                Tracks_Data_Error.Broadcast(Response->GetURL());

            }
            
        }

    }

}

void UAudius_API::Playlist_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {

    if (bWasSuccessful) {

        //UE_LOG(LogTemp, Warning, TEXT("Audius_API::Playlist_Data::[%s]"), *Response->GetContentAsString());

        FString Request_Content = Validate_Data(Response->GetContentAsString());
        
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Request_Content);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);

        const TArray<TSharedPtr<FJsonValue>>* Data_Json_Array;

        if (JsonObject->TryGetArrayField(TEXT("data"), Data_Json_Array)) {

            TArray<FAudius_Track_Struct> Audius_Tracks_Data = Tracks_Parse_Json(Data_Json_Array);
            
            if (Playlist_Tracks_Data_Received.IsBound()) {

                Playlist_Tracks_Data_Received.Broadcast(Audius_Tracks_Data);

            }

            if (Tracks_Data_Received.IsBound()) {

                Tracks_Data_Received.Broadcast(Audius_Tracks_Data);

            }
            
        }
        
        Playlist_Data_Retry_Index = 0;

    } else {
           
        if(Playlist_Data_Retry_Index + 1 < Data_Retry_Tries) {
            
            Playlist_Data_Retry_Index = Playlist_Data_Retry_Index + 1;
            
            FString Next_Node_Url = Endpoint_Node_Replace(Response->GetURL());
            
            FHttpModule& httpModule = FHttpModule::Get();
            TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request_Retry = httpModule.CreateRequest();
            Request_Retry->SetURL(Next_Node_Url);
            Request_Retry->SetVerb("GET");
            Request_Retry->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Playlist_Data);
            Request_Retry->ProcessRequest();

        } else {
            
            Playlist_Data_Retry_Index = 0;

            if (Playlist_Tracks_Data_Error.IsBound()) {
            
                Playlist_Tracks_Data_Error.Broadcast(Response->GetURL());
            
            }

            if (Tracks_Data_Error.IsBound()) {

                Tracks_Data_Error.Broadcast(Response->GetURL());

            }
            
        }
        
    }

}

void UAudius_API::Search(FString search_query) {
    
    search_query = search_query.Replace(TEXT("http://"),TEXT("https://"));

    if(!search_query.StartsWith("https://audius.co/") && !search_query.StartsWith("https://www.audius.co/") && !search_query.StartsWith("audius.co/") && !search_query.StartsWith("www.audius.co/")){

        FHttpModule& httpModule = FHttpModule::Get();
        TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = httpModule.CreateRequest();

        FString _request_url = FString::Printf(TEXT("%s/v1/tracks/search?query=%s&app_name=%s"), *Cache_Endpoints[Endpoint_Index], *FGenericPlatformHttp::UrlEncode(*search_query), *FGenericPlatformHttp::UrlEncode(*Audius_API_App_Name));

        UE_LOG(LogTemp, Warning, TEXT("Audius_API::Search::[%s]"), *_request_url);

        Request->SetURL(_request_url);
        Request->SetVerb("GET");
        Request->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Search_Data);
        Request->ProcessRequest();
    
    } else {

        if(search_query.StartsWith("audius.co/")) {
            search_query = FString::Printf(TEXT("https://%s"), *search_query);
        } else if(search_query.StartsWith("www.audius.co/")) {
            search_query = FString::Printf(TEXT("https://%s"), *search_query);
        }
        
        Resolve(search_query);
        
    }

}

void UAudius_API::Search_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {

    if (bWasSuccessful) {

        //UE_LOG(LogTemp, Warning, TEXT("Audius_API::Search_Data::[%s]"), *Response->GetContentAsString());

        FString Request_Content = Validate_Data(Response->GetContentAsString());
        
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Request_Content);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);

        const TArray<TSharedPtr<FJsonValue>>* Data_Json_Array;

        if (JsonObject->TryGetArrayField(TEXT("data"), Data_Json_Array)) {

            TArray<FAudius_Track_Struct> Audius_Tracks_Data = Tracks_Parse_Json(Data_Json_Array);

            if (Search_Data_Received.IsBound()) {

                Search_Data_Received.Broadcast(Audius_Tracks_Data);

            }
            
        }

        Search_Data_Retry_Index = 0;
        
    } else {
           
        if(Search_Data_Retry_Index + 1 < Data_Retry_Tries) {
            
            Search_Data_Retry_Index = Search_Data_Retry_Index + 1;
            
            FString Next_Node_Url = Endpoint_Node_Replace(Response->GetURL());
            
            FHttpModule& httpModule = FHttpModule::Get();
            TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request_Retry = httpModule.CreateRequest();
            Request_Retry->SetURL(Next_Node_Url);
            Request_Retry->SetVerb("GET");
            Request_Retry->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Search_Data);
            Request_Retry->ProcessRequest();

        } else {
            
            Search_Data_Retry_Index = 0;

            if (Search_Data_Error.IsBound()) {
            
                Search_Data_Error.Broadcast(Response->GetURL());
            
            }
        
        }
        
    }

}

void UAudius_API::Trending(FString trending_genre, FString trending_time /** week|month|year|allTime */) {

    FHttpModule& httpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = httpModule.CreateRequest();

    FString _request_url = FString::Printf(TEXT("%s/v1/tracks/trending?genre=%s&time=%s&app_name=%s"), *Cache_Endpoints[Endpoint_Index], *FGenericPlatformHttp::UrlEncode(*trending_genre), *trending_time, *FGenericPlatformHttp::UrlEncode(*Audius_API_App_Name));

    UE_LOG(LogTemp, Warning, TEXT("Audius_API::Trending::[%s]"), *_request_url);

    Request->SetURL(_request_url);
    Request->SetVerb("GET");
    Request->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Trending_Data);
    Request->ProcessRequest();

}

void UAudius_API::Trending_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {

    if (bWasSuccessful) {

        //UE_LOG(LogTemp, Warning, TEXT("Audius_API::Trending_Data::[%s]"), *Response->GetContentAsString());

        FString Request_Content = Validate_Data(Response->GetContentAsString());
        
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Request_Content);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);

        const TArray<TSharedPtr<FJsonValue>>* Data_Json_Array;

        if (JsonObject->TryGetArrayField(TEXT("data"), Data_Json_Array)) {

            TArray<FAudius_Track_Struct> Audius_Tracks_Data = Tracks_Parse_Json(Data_Json_Array);

            if (Trending_Data_Received.IsBound()) {

                Trending_Data_Received.Broadcast(Audius_Tracks_Data);

            }
            
            if (Tracks_Data_Received.IsBound()) {

                Tracks_Data_Received.Broadcast(Audius_Tracks_Data);

            }
            
        }

        Trending_Data_Retry_Index = 0;
        
    } else {
           
        if(Trending_Data_Retry_Index + 1 < Data_Retry_Tries) {
            
            Trending_Data_Retry_Index = Trending_Data_Retry_Index + 1;
            
            FString Next_Node_Url = Endpoint_Node_Replace(Response->GetURL());        
            
            FHttpModule& httpModule = FHttpModule::Get();
            TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request_Retry = httpModule.CreateRequest();
            Request_Retry->SetURL(Next_Node_Url);
            Request_Retry->SetVerb("GET");
            Request_Retry->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Trending_Data);
            Request_Retry->ProcessRequest();

        } else {
            
            Trending_Data_Retry_Index = 0;

            if (Trending_Data_Error.IsBound()) {
            
                Trending_Data_Error.Broadcast(Response->GetURL());
            
            }

            if (Tracks_Data_Error.IsBound()) {

                Tracks_Data_Error.Broadcast(Response->GetURL());

            }
            
        }
        
    }
    
}

void UAudius_API::Trending_Underground(int Trending_Underground_Offset = 0, int Trending_Underground_Limit = 100) {
        
    FHttpModule& httpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = httpModule.CreateRequest();
    
    FString _request_url = FString::Printf(TEXT("%s/v1/tracks/trending/underground?offset=%i&limit=%i&app_name=%s"), *Cache_Endpoints[Endpoint_Index], Trending_Underground_Offset, Trending_Underground_Limit, *FGenericPlatformHttp::UrlEncode(*Audius_API_App_Name));

    UE_LOG(LogTemp, Warning, TEXT("Audius_API::Trending_Underground::[%s]"), *_request_url);

    Request->SetURL(_request_url);
    Request->SetVerb("GET");
    Request->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Trending_Underground_Data);
    Request->ProcessRequest();

}

void UAudius_API::Trending_Underground_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {

    if (bWasSuccessful) {

        //UE_LOG(LogTemp, Warning, TEXT("Audius_API::Trending_Underground_Data::[%s]"), *Response->GetContentAsString());

        FString Request_Content = Validate_Data(Response->GetContentAsString());
        
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Request_Content);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);

        const TArray<TSharedPtr<FJsonValue>>* Data_Json_Array;

        if (JsonObject->TryGetArrayField(TEXT("data"), Data_Json_Array)) {

            TArray<FAudius_Track_Struct> Audius_Tracks_Data = Tracks_Parse_Json(Data_Json_Array);

            if (Trending_Underground_Data_Received.IsBound()) {

                Trending_Underground_Data_Received.Broadcast(Audius_Tracks_Data);

            }
            
            if (Tracks_Data_Received.IsBound()) {

                Tracks_Data_Received.Broadcast(Audius_Tracks_Data);

            }
            
        }

        Trending_Underground_Data_Retry_Index = 0;
        
    } else {
           
        if(Trending_Underground_Data_Retry_Index + 1 < Data_Retry_Tries) {
            
            Trending_Underground_Data_Retry_Index = Trending_Underground_Data_Retry_Index + 1;
            
            FString Next_Node_Url = Endpoint_Node_Replace(Response->GetURL());
           
            FHttpModule& httpModule = FHttpModule::Get();
            TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request_Retry = httpModule.CreateRequest();
            Request_Retry->SetURL(Next_Node_Url);
            Request_Retry->SetVerb("GET");
            Request_Retry->OnProcessRequestComplete().BindUObject(this, &UAudius_API::Trending_Underground_Data);
            Request_Retry->ProcessRequest();
            
        } else {
            
            Trending_Underground_Data_Retry_Index = 0;

            if (Trending_Underground_Data_Error.IsBound()) {
            
                Trending_Underground_Data_Error.Broadcast(Response->GetURL());
            
            }

            if (Tracks_Data_Error.IsBound()) {

                Tracks_Data_Error.Broadcast(Response->GetURL());

            }
            
        }

    }
    
}