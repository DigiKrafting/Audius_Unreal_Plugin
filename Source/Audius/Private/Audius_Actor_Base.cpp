/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#include "Audius_Actor_Base.h"
#include "Components/ListView.h"
#include "Audius_Track_Item_Widget.h"
#include "MediaSoundComponent.h"
#include "Audius_Interface_Widget.h"
#include "IMediaEventSink.h" 
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h" 
#include "Dom/JsonObject.h" 
#include "Audius_Player_Widget.h"
#include "UObject/ConstructorHelpers.h"

AAudius_Actor_Base::AAudius_Actor_Base() {

    Audius_Scene_Component = CreateDefaultSubobject<USceneComponent>(TEXT("Audius_Scene_Component"));

    RootComponent = Audius_Scene_Component;
    
    Audius_MediaSound_Component = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Audius_MediaSound_Component"));
    Audius_MediaSound_Component->SetupAttachment(Audius_Scene_Component);

    Audius_MediaPlayer = CreateDefaultSubobject<UMediaPlayer>(TEXT("Audius_MediaPlayer"));
    
    if (Audius_Player_Widget_Class == nullptr){
        
        ConstructorHelpers::FClassFinder<UAudius_Player_Widget> Audius_Player_Widget_Class_Object(TEXT("/Audius/Widgets/Audius_Actor_Display_Widget"));
        Audius_Player_Widget_Class = Audius_Player_Widget_Class_Object.Class;        

    }
    
    if (Audius_Interface_Widget_Class == nullptr){
        
        ConstructorHelpers::FClassFinder<UAudius_Interface_Widget> Audius_Interface_Widget_Class_Object(TEXT("/Audius/Widgets/Audius_Interface_Widget"));
        Audius_Interface_Widget_Class = Audius_Interface_Widget_Class_Object.Class;        

    }
    
}

void AAudius_Actor_Base::PreInitializeComponents() {
    
    Super::PreInitializeComponents();

}

void AAudius_Actor_Base::PostInitializeComponents() {

	Super::PostInitializeComponents();

    Items.Empty();

	if (Audius_Player_Widget_Class != nullptr) {

		Audius_Player_Widget = CreateWidget<UAudius_Player_Widget>(GetWorld(), Audius_Player_Widget_Class);

		if (Audius_Player_Widget != nullptr) {

			Audius_Player_Widget->Audius_Actor = this;

		}

	}

    if (Audius_MediaPlayer == nullptr) {
        
        Audius_MediaPlayer = NewObject<UMediaPlayer>(this, TEXT("Audius_MediaPlayer"));

    }
    
}

void AAudius_Actor_Base::BeginPlay() {
	
    Super::BeginPlay();

    Audius_MediaPlayer->PlayOnOpen = false;

    Audius_MediaPlayer->RegisterWithMediaModule();
    
    Audius_MediaSound_Component->SetMediaPlayer(Audius_MediaPlayer);

    Set_Volume(default_volume);
   
    Audius_MediaPlayer->OnMediaEvent().AddUObject(this, &AAudius_Actor_Base::HandleMediaPlayerEvent);
    
    Audius_API = NewObject<UAudius_API>(this, UAudius_API::StaticClass(), TEXT("Audius_API"));
    
    Audius_API->Endpoints_Data_Received.AddDynamic(this, &AAudius_Actor_Base::OnEndpoints_Data_Received);
    Audius_API->Tracks_Data_Received.AddDynamic(this, &AAudius_Actor_Base::OnTracks_Data_Received);
    Audius_API->Search_Data_Received.AddDynamic(this, &AAudius_Actor_Base::OnSearch_Tracks_Data_Received);
    
    if(!Audius_API_App_Name.IsEmpty()){
        Audius_API->Audius_API_App_Name = Audius_API_App_Name;
    }
    
    Audius_API->Endpoints();

    if (Audius_Actor_Type == EAudius_Actor_Type::Player) {

        Audius_Player_Widget->AddToPlayerScreen();

    }
    
    Audius_MediaPlayer->Close();

}

// #################################################################################################################################################################################################
// API CALLS
// #################################################################################################################################################################################################

void AAudius_Actor_Base::Search(FString Search_Query) {

    Audius_API->Search(Search_Query);

    if(Search_Query.Contains("https://audius.co/") || Search_Query.Contains("https://www.audius.co/")) {

        Audius_Interface_Close();
        
    }
        
}

void AAudius_Actor_Base::Resolve(FString Audius_Url) {

    Audius_API->Resolve(Audius_Url);

}

void AAudius_Actor_Base::Trending(FString Trending_Genre, FString Trending_Time) {
    
    Audius_API->Trending(Trending_Genre, Trending_Time);

}

void AAudius_Actor_Base::Trending_Underground(int Trending_Underground_Offset, int Trending_Underground_Limit) {
    
    Audius_API->Trending_Underground(Trending_Underground_Offset, Trending_Underground_Limit);
    
}

// ##########################################################################################################################################################################################################################################
// EVENTS
// ##########################################################################################################################################################################################################################################

void AAudius_Actor_Base::OnEndpoints_Data_Received(const TArray<FString>& Endpoints_Data) {

    UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::OnEndpoints_Data_Received: %s"), *Endpoints_Data[0]);

    if(Audius_Default_Stream == EAudius_Default_Stream::Trending)
    {
        if(Audius_Trending_Genre == TEXT("All")){
            Audius_Trending_Genre = "";
        }

        FString Trending_Time = FString(TEXT(""));
    
        if(Audius_Trending_Time == EAudius_Trending_Time::Week) {
            Trending_Time = TEXT("week");
        }else if(Audius_Trending_Time == EAudius_Trending_Time::Month) {
            Trending_Time = TEXT("month");
        }else if(Audius_Trending_Time == EAudius_Trending_Time::Year) {
            Trending_Time = TEXT("year");
        }else if(Audius_Trending_Time == EAudius_Trending_Time::AllTime) {
            Trending_Time = TEXT("allTime");
        }

        Trending(Audius_Trending_Genre, Trending_Time);
        
    } else if(Audius_Default_Stream == EAudius_Default_Stream::Trending_Underground) {

        Trending_Underground(Audius_Trending_Underground_Offset, Audius_Trending_Underground_Limit);

    } else if(Audius_Default_Stream == EAudius_Default_Stream::Official_Playlist) {
        
        Resolve(Official_Playlist);

    } else {
        
        if (Audius_Default_Url != "") {

            Resolve(Audius_Default_Url);

        }

    }
    
}

void AAudius_Actor_Base::OnTracks_Data_Received(const TArray<FAudius_Track_Struct>& Tracks_Data) {

    if(Tracks_Data.Num() == 1) {

        Queue_Track(Tracks_Data[0]);

        Track_Index = Audius_Playlist_Tracks.Num() - 1;

        if (Audius_Auto_Play) {
            
            Queue_Play();
            
        }
        
    } else {

        Audius_Playlist_Tracks.Empty();            
    
        Items.Empty();

        for (const FAudius_Track_Struct& Track_Data : Tracks_Data) {

            Queue_Track(Track_Data);
        
            UTrackData* Item = NewObject<UTrackData>();

            Item->Track_Id = Track_Data.Track_Id;
            Item->Track_Title = Track_Data.Track_Title;
            Item->Track_Artist = Track_Data.Track_Artist;
            Item->Track_Stream_Url = Track_Data.Track_Stream_Url;
            Item->Track_Artwork_Url = Track_Data.Track_Artwork_Url;

            Items.Add(Item);

        }

        Track_Index = 0;
    
        if (Audius_Auto_Play) {
            
            Queue_Play();
            
        }
        
    }
    
}

void AAudius_Actor_Base::OnSearch_Tracks_Data_Received(const TArray<FAudius_Track_Struct>& Tracks_Data) {
    
    Audius_Search_Tracks = Tracks_Data;

    Items.Empty();

    for (const FAudius_Track_Struct& Track_Data : Tracks_Data) {

        UTrackData* Item = NewObject<UTrackData>();

        Item->Track_Id = Track_Data.Track_Id;
        Item->Track_Title = Track_Data.Track_Title;
        Item->Track_Artist = Track_Data.Track_Artist;
        Item->Track_Stream_Url = Track_Data.Track_Stream_Url;
        Item->Track_Artwork_Url = Track_Data.Track_Artwork_Url;

        Items.Add(Item);

    }

    Audius_Search_List_View->SetListItems(Items);
   
}

// ##########################################################################################################################################################################################################################################
// QUEUE FUNCTIONS
// ##########################################################################################################################################################################################################################################

void AAudius_Actor_Base::Queue_Track(const FAudius_Track_Struct Track_Data) {

    Audius_Playlist_Tracks.Add(Track_Data);
 
}

void AAudius_Actor_Base::Queue_Insert(const FAudius_Track_Struct Track_Data, int32 Index) {

    if(Index < 0) {
        Index = 0;
    } else if(Index > Audius_Playlist_Tracks.Num() - 1){
        Index = Audius_Playlist_Tracks.Num() - 1;
    }
    
    Audius_Playlist_Tracks.Insert(Track_Data, Index);
    
}

void AAudius_Actor_Base::Queue_Next() {

    if(FPlatformTime::Seconds() - Queue_Buttons_Throttle_Last < Queue_Buttons_Throttle || !Queue_Buttons_Enabled){
        return;
    }
    
    Queue_Buttons_Throttle_Last = FPlatformTime::Seconds();
    
    int32 _tracks = Audius_Playlist_Tracks.Num();

    UE_LOG(LogTemp, Warning, TEXT("+++++++++++++++++ Queue_Next::Audius_Playlist_Tracks.Num(%i) +++++++++++++++++"), _tracks);

    if (Track_Index != -1 && Track_Index + 1 < _tracks) {

        Track_Index = Track_Index + 1;

        if (IsValid(Audius_MediaPlayer)) {
            
            UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::Next([%i][%s][ %s ])"), Track_Index, *Audius_Playlist_Tracks[Track_Index].Track_Title, *Audius_Playlist_Tracks[Track_Index].Track_Stream_Url);
            
            Queue_Play();
            
        }

    }

    UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::Queue_Next()[ }<- ]"));

}

void AAudius_Actor_Base::Queue_Previous() {

    if(FPlatformTime::Seconds() - Queue_Buttons_Throttle_Last < Queue_Buttons_Throttle || !Queue_Buttons_Enabled){
        return;
    }
    
    Queue_Buttons_Throttle_Last = FPlatformTime::Seconds();
    
    if (Track_Index != -1 && Track_Index - 1 >= 0) {

        Track_Index = Track_Index - 1;

        if (IsValid(Audius_MediaPlayer)) {

            UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::Previous([%i][%s][ %s ])"), Track_Index, *Audius_Playlist_Tracks[Track_Index].Track_Title, *Audius_Playlist_Tracks[Track_Index].Track_Stream_Url);

            Queue_Play();
            
        }

    }

    UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::Previous()[ }<- ]"));

}
void AAudius_Actor_Base::Queue_Play() {

    Audius_Auto_Play = true; // needed here so new requests in OnTracks_Data_Received will play
    
    if(Audius_MediaPlayer->IsPlaying() || Audius_MediaPlayer->IsPaused() || Audius_MediaPlayer->IsPreparing()) {

        Audius_MediaPlayer->Close();
        
    } else {
        
        //Audius_MediaPlayer->OpenUrl(*Audius_Playlist_Tracks[Track_Index].Track_Stream_Url);
        Audius_MediaPlayer->OpenUrl(*Audius_API->Track_Stream_Url(Audius_Playlist_Tracks[Track_Index]));

    }

}

void AAudius_Actor_Base::Queue_Play(int32 Index) {

    Track_Index = Index;

    Queue_Play();
    
}

void AAudius_Actor_Base::Queue_Remove(int32 Index) {

    Audius_Playlist_Tracks.RemoveAt(Index);    

    if(Index == Track_Index) {
        
        Queue_Play();
        
    } else if(Index < Track_Index){
        
        Track_Index = Track_Index - 1;
        
    }
        
}

void AAudius_Actor_Base::Queue_Stop() {

    Audius_MediaPlayer->Pause();

    Audius_Playlist_Tracks.Empty();    

    Audius_MediaPlayer->Close();
    
    Track_Index = 0;

}

void AAudius_Actor_Base::Queue_Pause() {
    
    if (Audius_MediaPlayer->IsPaused()) {
        
        //bIsPaused = false;

        Audius_MediaPlayer->Play();

    } else if (Audius_MediaPlayer->IsPlaying()) {
        
        //bIsPaused = true;

        Audius_MediaPlayer->Pause();

    } else {
        
        if (!Audius_MediaPlayer->IsPreparing()) {
            
            Queue_Play();
            
        }
        
    }

}

void AAudius_Actor_Base::HandleMediaPlayerEvent(EMediaEvent Event) {

    switch (Event) {
        
        case EMediaEvent::MediaConnecting:

            Queue_Buttons_Enabled = false;
        
        break;
        case EMediaEvent::MediaClosed:

            UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::HandleMediaPlayerEvent([ EMediaEvent::MediaClosed ])"));
            
            Queue_Buttons_Enabled = false;

            if(Audius_Playlist_Tracks.Num() && Track_Index < Audius_Playlist_Tracks.Num()) {

                Audius_MediaPlayer->OpenUrl(*Audius_API->Track_Stream_Url(Audius_Playlist_Tracks[Track_Index]));

            }
        
        break;
        
        case EMediaEvent::MediaBuffering:

            UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::HandleMediaPlayerEvent([ EMediaEvent::MediaBuffering ])"));

            Audius_Player_Widget->Show_Pause_Icon();

            Queue_Buttons_Enabled = true;

            Track_Update();
        
        break;
        case EMediaEvent::MediaOpened:

            UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::HandleMediaPlayerEvent([ EMediaEvent::MediaOpened ])"));

            if(!Audius_MediaPlayer->IsPlaying() || !Audius_MediaPlayer->IsPaused() || !Audius_MediaPlayer->IsPreparing()) {
                Audius_MediaPlayer->Play();
            } else {
                Audius_MediaPlayer->Close();
            }
        
        break;    
        case EMediaEvent::MediaOpenFailed:

            // failed to stream track 
            // try another node
                
            {  
               
                FString Current_Track_Url = Audius_Playlist_Tracks[Track_Index].Track_Stream_Url;

                Track_Try_Next_Node_Index = Track_Try_Next_Node_Index + 1;

                if(Track_Try_Next_Node_Index < Track_Try_Next_Node_Tries) {
                   
                   // Audius_Playlist_Tracks[Track_Index].Track_Stream_Url = Audius_API->Track_Next_Node(Audius_Playlist_Tracks[Track_Index]);
                    
                   /* if(Audius_MediaPlayer->OpenUrl(*Audius_Playlist_Tracks[Track_Index].Track_Stream_Url)) {
    
                        Track_Update();
       
                    }*/
                    Audius_API->Endpoint_Next_Node();
                    
                    Queue_Play();
                    
                    break;
                        
                }

                Audius_Playlist_Tracks.RemoveAt(Track_Index);

            }
               
        case EMediaEvent::PlaybackEndReached:

            UE_LOG(LogTemp, Warning, TEXT("AAudius_Actor_Base::HandleMediaPlayerEvent([ EMediaEvent::PlaybackEndReached ])"));
                
            if (Queue_Track_Ended.IsBound()){
                Queue_Track_Ended.Broadcast(Audius_Playlist_Tracks[Track_Index]);
            }

            if(Track_Try_Next_Node_Index == Track_Try_Next_Node_Tries) {

                Track_Try_Next_Node_Index = 0;

                /*if(Audius_MediaPlayer->OpenUrl(*Audius_Playlist_Tracks[Track_Index].Track_Stream_Url)) {
        
                    Track_Update();
           
                }*/

                Queue_Play();
                        
            } else if (Track_Index + 1 < Audius_Playlist_Tracks.Num()) {

                Track_Index = Track_Index + 1;
                    
                Audius_MediaPlayer->Close();
                
            } else {

                if(Audius_Queue_Ended_Action == EAudius_Queue_Ended_Action::Replay) {
                    
                    Track_Index = 0;
                    
                    Audius_MediaPlayer->Close();
                    
                }
                
                if (Queue_Ended.IsBound()){
                    Queue_Ended.Broadcast();
                }
                    
            }

        break;
        case EMediaEvent::PlaybackResumed:

            Audius_Player_Widget->Show_Pause_Icon();

        break;
        case EMediaEvent::PlaybackSuspended:

            Audius_Player_Widget->Show_Play_Icon();

        break;
        default:
        break;
        
    }

}

// ##########################################################################################################################################################################################################################################
// WIDGET INTERACTIONS
// ##########################################################################################################################################################################################################################################

void AAudius_Actor_Base::Audius_Interface_Open() {

    if (Audius_Interface_Widget_Class != nullptr) {

        Audius_Interface_Widget = CreateWidget<UAudius_Interface_Widget>(GetWorld(), Audius_Interface_Widget_Class);

        if (Audius_Interface_Widget != nullptr) {

            Audius_Interface_Widget->Audius_Actor = this;

            //Interface_Widget_AddToPlayerScreen_Override
            
            Audius_Interface_Widget->AddToPlayerScreen();
            
            APlayerController* player_controller =UGameplayStatics::GetPlayerController(GetWorld(), 0);
            
            player_controller->SetShowMouseCursor(true);
            player_controller->SetIgnoreMoveInput(true);
            player_controller->SetIgnoreLookInput(true);
            player_controller->SetInputMode(FInputModeUIOnly());

        }

    }

}

void AAudius_Actor_Base::Audius_Interface_Close() {
    
    Audius_Interface_Widget->RemoveFromParent();
    Audius_Interface_Widget = nullptr;
    
    APlayerController* player_controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    player_controller->SetShowMouseCursor(false);
    player_controller->SetIgnoreMoveInput(false);
    player_controller->SetIgnoreLookInput(false);
    player_controller->SetInputMode(FInputModeGameOnly());

}

bool AAudius_Actor_Base::Audius_Interface_Visible() {

    if(Audius_Interface_Widget!=nullptr) {
        return true;
    } else {
        return false;
    }
    
}

void AAudius_Actor_Base::Set_Volume(float Volume) {

    if (IsValid(Audius_MediaSound_Component)) {
        
        Audius_MediaSound_Component->SetVolumeMultiplier(Volume);
        
    }
    
}

void AAudius_Actor_Base::Track_Update() {

    FAudius_Track_Struct Audius_Playlist_Track = Audius_Playlist_Tracks[Track_Index];
    
    if (Audius_Actor_Type == EAudius_Actor_Type::Player) {

        Audius_Player_Widget->Update_Display_Text(Audius_Playlist_Track.Track_Title, Audius_Playlist_Track.Track_Artist);

    }

    if (Queue_Track_Playing.IsBound()){
        Queue_Track_Playing.Broadcast(Audius_Playlist_Track);
    }
    
}

// ######################################################################################################################################################################################

void AAudius_Actor_Base::Search_List_Item_Click(UObject* Item) {

    int32 Selected_Track_Index = Audius_Search_List_View->GetIndexForItem(Item);

    if (Selected_Track_Index != -1) {

        //Queue_Stop();

        Queue_Track(Audius_Search_Tracks[Selected_Track_Index]);

        Track_Index = Audius_Playlist_Tracks.Num() - 1;
        
        Queue_Play();
        
    }

}

// ######################################################################################################################################################################################
