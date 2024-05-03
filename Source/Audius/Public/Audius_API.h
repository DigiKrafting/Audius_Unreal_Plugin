/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

/*

The Audius API is entirely free to use. We ask that you adhere to the guidelines in this doc https://audiusproject.github.io/api-docs/#audius-api-docs and always credit artists.

*/

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h" 
#include "Audius_API.generated.h"

USTRUCT(BlueprintType)
struct FAudius_Track_Artwork_Struct {

    GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString url_150x150;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString url_480x480;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString url_1000x1000;

};

USTRUCT(BlueprintType)
struct FAudius_Track_Remix_Of_Struct {

    GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    TArray<FString> tracks;

};

USTRUCT(BlueprintType)
struct FAudius_Track_User_Cover_Photo_Struct {

    GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString url_640x;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString url_2000x;

};

USTRUCT(BlueprintType)
struct FAudius_Track_User_Profile_Picture_Struct {

    GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString url_150x150;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString url_480x480;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString url_1000x1000;

};

USTRUCT(BlueprintType)
struct FAudius_Track_User_Struct {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
	int32 album_count;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString artist_pick_track_id;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString bio;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FAudius_Track_User_Cover_Photo_Struct cover_photo;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 followee_count;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 follower_count;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString handle;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString id;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    bool is_verified;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString location;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString name;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 playlist_count;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FAudius_Track_User_Profile_Picture_Struct profile_picture;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 repost_count;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 track_count;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    bool is_deactivated;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    bool is_available;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString erc_wallet;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString spl_wallet;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 supporter_count;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 supporting_count;

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 total_audio_balance;

};

/*
https://audiusproject.github.io/api-docs/#get-track
*/

USTRUCT(BlueprintType)
struct FAudius_Api_Track_Struct {
	
    GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FAudius_Track_Artwork_Struct artwork;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString description;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString genre;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString id;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString track_cid;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString mood;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString release_date;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FAudius_Track_Remix_Of_Struct remix_of;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 repost_count;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 favorite_count;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
	int32 total_play_count;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString tags;
    UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString title;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FAudius_Track_User_Struct user;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 duration;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    bool is_downloadable;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    int32 play_count;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    FString permalink;
	UPROPERTY(BlueprintReadOnly, Category = "Audius|Track|API")
    bool is_streamable;
	
};

USTRUCT(BlueprintType)
struct FAudius_Track_Struct {

    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(BlueprintReadOnly, Category = "Audius|Track")
    FAudius_Api_Track_Struct Api_Track_Data;

    UPROPERTY(BlueprintReadOnly, Category = "Audius|Track")
    FString Track_Id;

    UPROPERTY(BlueprintReadOnly, Category = "Audius|Track")
    FString Track_Title;

    UPROPERTY(BlueprintReadOnly, Category = "Audius|Track")
    FString Track_Artist;

    UPROPERTY(BlueprintReadOnly, Category = "Audius|Track")
    FString Track_Artwork_Url;

    UPROPERTY(BlueprintReadOnly, Category = "Audius|Track")
    FString Track_Stream_Url;

};

// EVENT DELEGATES

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndpoints_Data_Received, const TArray<FString>&, Endpoints_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndpoints_Data_Error, const FString, Audius_Api_Url);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResolve_Data_Error, const FString, Audius_Api_Url);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrack_Data_Received, const FAudius_Track_Struct&, Track_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrack_Data_Error, const FString, Audius_Api_Url);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlaylist_Tracks_Data_Received, const TArray<FAudius_Track_Struct>&, Tracks_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlaylist_Tracks_Data_Error, const FString, Audius_Api_Url);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearch_Data_Received, const TArray<FAudius_Track_Struct>&, Tracks_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearch_Data_Error, const FString, Audius_Api_Url);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrending_Data_Received, const TArray<FAudius_Track_Struct>&, Tracks_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrending_Data_Error, const FString, Audius_Api_Url);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrending_Underground_Data_Received, const TArray<FAudius_Track_Struct>&, Tracks_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrending_Underground_Data_Error, const FString, Audius_Api_Url);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTracks_Data_Received, const TArray<FAudius_Track_Struct>&, Tracks_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTracks_Data_Error, const FString, Audius_Api_Url);

/** ROOT AUDIUS API CLASS **/
UCLASS(BlueprintType)
class AUDIUS_API UAudius_API : public UObject {

	GENERATED_UCLASS_BODY()

public:

	/** Your app name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "API App Name", Keywords = "Audius"), Category = "Audius|API");
	FString Audius_API_App_Name = FString("Audius Unreal Plugin");
	
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FEndpoints_Data_Received Endpoints_Data_Received;
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FEndpoints_Data_Error Endpoints_Data_Error;

	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FResolve_Data_Error Resolve_Data_Error;
	
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FTrack_Data_Received Track_Data_Received;
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FTrack_Data_Error Track_Data_Error;
	
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FPlaylist_Tracks_Data_Received Playlist_Tracks_Data_Received;
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FPlaylist_Tracks_Data_Error Playlist_Tracks_Data_Error;

	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FSearch_Data_Received Search_Data_Received;
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FSearch_Data_Error Search_Data_Error;
    
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FTrending_Data_Received Trending_Data_Received;
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FTrending_Data_Error Trending_Data_Error;

	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FTrending_Underground_Data_Received Trending_Underground_Data_Received;
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FTrending_Underground_Data_Error Trending_Underground_Data_Error;
	
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FTracks_Data_Received Tracks_Data_Received;
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FTracks_Data_Error Tracks_Data_Error;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Endpoints", Keywords = "Audius Music API Endpoint"), Category = "Audius")
	void Endpoints();

	FString Endpoint_Node_Replace(FString Audius_Api_Url);
	void Endpoint_Next_Node();
	FString Track_Stream_Url(FAudius_Track_Struct Audius_Track_Data);
	FString Validate_Data(FString Data_Json_String);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Resolve", Keywords = "Audius Music API Endpoint"), Category = "Audius")
	void Resolve(FString audius_url);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Search", Keywords = "Audius Music API Search"), Category = "Audius")
	void Search(FString search_query);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Trending", Keywords = "Audius Music API Trending"), Category = "Audius")
    void Trending(FString trending_genre, FString trending_time /** week|month|year|allTime */);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Trending Underground", Keywords = "Audius Music API Trending Underground"), Category = "Audius")
	void Trending_Underground(int offset, int limit);

	static TArray<FString> Genres;
	static TArray<FString> Official_Playlists;
	
private:

	UPROPERTY();
	TArray<FString> Cache_Endpoints;
	UPROPERTY();
	int Endpoint_Index = 0;
	UPROPERTY();
	int Resolve_Data_Retry_Index = 0;
	UPROPERTY();
	int Search_Data_Retry_Index = 0;
	UPROPERTY();
	int Playlist_Data_Retry_Index = 0;
	UPROPERTY();
	int Trending_Data_Retry_Index = 0;
	UPROPERTY();
	int Trending_Underground_Data_Retry_Index = 0;
	UPROPERTY();
	int Data_Retry_Tries = 3;
	
	FAudius_Track_Struct Track_Parse_Json(const TSharedPtr<FJsonObject> Track_Json_Object);
	TArray<FAudius_Track_Struct> Tracks_Parse_Json(const TArray<TSharedPtr<FJsonValue>>*& Data_Json_Array);

	void Endpoints_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void Resolve_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void Playlist_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void Search_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void Trending_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void Trending_Underground_Data(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
};
