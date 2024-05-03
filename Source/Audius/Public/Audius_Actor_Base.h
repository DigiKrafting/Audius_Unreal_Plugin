/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MediaPlayer.h"
#include "Audius_API.h"
#include "Templates/SharedPointer.h"
#include "Audius_Actor_Base.generated.h"

class UMediaPlayer;
class UMediaSoundComponent;
class UAudius_Player_Widget;
class UAnimMontage;
class UAudius_Interface_Widget;
class UListView;
class UTrackData;
class FJsonObject;
class UAudius_Track_Item_Widget;

UENUM()
enum class EAudius_Actor_Type : uint32 {
	Player,
	Custom
};

UENUM()
enum class EAudius_Default_Stream : uint32 {
	Trending,
	Trending_Underground,
	Official_Playlist,
	Default_Audius_Url
};

UENUM()
enum class EAudius_Queue_Ended_Action : uint32 {
	Replay,
	Custom
};

UENUM()
enum class EAudius_Trending_Time : uint32 {
	Week,
	Month,
	Year,
	AllTime
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQueue_Track_Ended, const FAudius_Track_Struct&, Tracks_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQueue_Track_Playing, const FAudius_Track_Struct&, Tracks_Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQueue_Ended);

UCLASS()
class AUDIUS_API AAudius_Actor_Base : public AActor {
	
	GENERATED_BODY()

public:

	AAudius_Actor_Base();

	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FQueue_Track_Ended Queue_Track_Ended;

	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FQueue_Track_Playing Queue_Track_Playing;
	
	UPROPERTY(BlueprintAssignable, Category = "Audius|Events")
	FQueue_Ended Queue_Ended;

	/** Your app name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "API App Name", Keywords = "Audius"), Category = "Audius");
	FString Audius_API_App_Name = FString("Audius Unreal Plugin");

	/** Actor Type - Use Custom no player widget to be displayed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Actor Type", Keywords = "Audius"), Category = "Audius");
	EAudius_Actor_Type Audius_Actor_Type = EAudius_Actor_Type::Player;

	/** Start playing music on begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Auto Play", Keywords = "Audius auto play"), Category = "Audius");
	bool Audius_Auto_Play = true;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Queue Ended Action", Keywords = "Audius"), Category = "Audius");
	EAudius_Queue_Ended_Action Audius_Queue_Ended_Action = EAudius_Queue_Ended_Action::Replay;

	/** Default music stream to use */	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Default Music Stream", Keywords = "Audius"), Category = "Audius");
	EAudius_Default_Stream Audius_Default_Stream = EAudius_Default_Stream::Trending;

	/** Official Playlists */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Official Playlist", Keywords = "Audius", GetOptions = "GetOfficialPlaylistOptions"), Category = "Audius");
	FString Official_Playlist = TEXT("https://audius.co/Audius/playlist/hot-new-on-audius%F0%9F%94%A5");

	UFUNCTION(CallInEditor)
	TArray<FString> GetOfficialPlaylistOptions() const {
		
		return UAudius_API::Official_Playlists;
		
	}

	/** Default Audius link to play. Set [Default Music Stream] to [Default_Audius_Url] to use*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audius", meta = (DisplayName = "Default Audius Url", Keywords = "Audius Default Url"), Category = "Audius")
	FString Audius_Default_Url = FString("https://audius.co/Audius/playlist/hot-new-on-audius%F0%9F%94%A5");
	
	/** Filter trending to a specified genre */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Trending Genre", Keywords = "Audius", GetOptions = "GetGenreOptions"), Category = "Audius|Trending");
	FString Audius_Trending_Genre = TEXT("All");

	UFUNCTION(CallInEditor)
	TArray<FString> GetGenreOptions() const {
		
		return UAudius_API::Genres;
		
	}

	/** Calculate trending over a specified time range */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Trending Time", Keywords = "Audius"), Category = "Audius|Trending");
	EAudius_Trending_Time Audius_Trending_Time;

	/** The number of items to skip. Useful for pagination (page number * limit) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Trending Underground Offset", Keywords = "Audius"), Category = "Audius|Trending Underground");
	int32 Audius_Trending_Underground_Offset = 0;
	
	/** The number of items to fetch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Trending Underground Limit", Keywords = "Audius"), Category = "Audius|Trending Underground");
	int32 Audius_Trending_Underground_Limit = 100;

	/** Key binding to display Audius Interface */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Enable M Key Binding", Keywords = "Audius"), Category = "Audius");
	bool Enable_M_Key_Binding = true;	

	/** Override with a custom [UMediaPlayer] */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audius|Media")
	UMediaPlayer* Audius_MediaPlayer;

	/** Override with a custom [UMediaSoundComponent] */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audius|Media")
	UMediaSoundComponent* Audius_MediaSound_Component;

	/** Override with a custom [UAudius_Player_Widget] */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audius|Widget", meta = (BindWidget))
	TSubclassOf<UAudius_Player_Widget> Audius_Player_Widget_Class;

	UAudius_Player_Widget* Audius_Player_Widget;

	/** Override with a custom [UAudius_Interface_Widget] */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audius|Widget", meta = (BindWidget))
	TSubclassOf<UAudius_Interface_Widget> Audius_Interface_Widget_Class;

	UAudius_Interface_Widget* Audius_Interface_Widget = nullptr;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Audius Interface", Keywords = "Audius, Music"), Category = "Audius")
	void Audius_Interface_Open();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Close Audius Interface", Keywords = "Audius, Music"), Category = "Audius")
	void Audius_Interface_Close();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Interface Visible", Keywords = "Audius, Music"), Category = "Audius")
	bool Audius_Interface_Visible();
	
	void Trending(FString Trending_Genre, FString Trending_Time /** week|month|year|allTime */);
	void Trending_Underground(int Trending_Underground_Offset, int Trending_Underground_Limit);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Play Audius Link", Keywords = "Audius Music Play"), Category = "Audius")
	void Resolve(FString Audius_Url);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Search (Audius)", Keywords = "Audius Music Search"), Category = "Audius")
	void Search(FString Search_Query);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Audius Volume", Keywords = "Audius Music Search"), Category = "Audius")
	void Set_Volume(float Volume);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Track_Update (Audius)", Keywords = "Audius Media Player Event Track Update"), Category = "Audius")
	void Track_Update();
	
	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Search List Item Click", Keywords = "Audius Music Search Track"), Category = "Audius")
	void Search_List_Item_Click(UObject* Item);

	UPROPERTY()
	TArray<FAudius_Track_Struct> Audius_Playlist_Tracks;
	UPROPERTY()
	TArray<FAudius_Track_Struct> Audius_Search_Tracks;

	UPROPERTY()
	TArray<UTrackData*> Items;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audius|Widget")
	UListView* Audius_Search_List_View;

	/** Default Volume */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audius|Audio")
	float default_volume = 0.40f;
	
	void HandleMediaPlayerEvent(EMediaEvent Event);
	
	void Queue_Play();
	void Queue_Play(int32 Index);
	void Queue_Remove(int32 Index);
	void Queue_Stop();
	void Queue_Pause();
	void Queue_Next();
	void Queue_Previous();

	UFUNCTION()
		void OnEndpoints_Data_Received(const TArray<FString>& Endpoints_Data);
	UFUNCTION()
		void OnTracks_Data_Received(const TArray<FAudius_Track_Struct>& Tracks_Data);
	UFUNCTION()
		void OnSearch_Tracks_Data_Received(const TArray<FAudius_Track_Struct>& Tracks_Data);
		
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	UPROPERTY()
	int Track_Try_Next_Node_Index = 0;
	UPROPERTY()
	int Track_Try_Next_Node_Tries = 3;

	UPROPERTY()
	UAudius_API* Audius_API;
	
private:

	UPROPERTY()
	TArray<FString> Cache_Endpoints;
	UPROPERTY()
	int32 Endpoint_Index = 0;
	UPROPERTY()
	int32 Track_Index = 0;
	
	UFUNCTION()
	void Queue_Track(const FAudius_Track_Struct Track_Data);
	UFUNCTION()
	void Queue_Insert(FAudius_Track_Struct Track_Data, int32 Index);

	//UPROPERTY()
	//bool bIsPaused = false;

	UPROPERTY()
	USceneComponent* Audius_Scene_Component;

	UPROPERTY()
	double Queue_Buttons_Throttle = 0.8;
	UPROPERTY()
	double Queue_Buttons_Throttle_Last = 0.0;
	UPROPERTY()
	bool Queue_Buttons_Enabled = false;
	UPROPERTY()
	bool Queue_Play_Wait_Enabled = false;
	
};
