/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Audius_Interface_Widget.generated.h"

class UTextBlock;
class UListView;
class UTrackData;
class UMediaSoundComponent;
class AAudius_Actor_Base;

UCLASS()
class AUDIUS_API UAudius_Interface_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	AAudius_Actor_Base* Audius_Actor;

	UPROPERTY(meta = (BindWidget))
	UListView* Audius_Search_List_View;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Search", Keywords = "Audius, Music"), Category = "Audius")
		void Search(FString Search_Query);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Search List Item Click", Keywords = "Audius Media Player Event Track Update"), Category = "Audius")
		void Search_List_Item_Click(UObject* Item);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Resolve", Keywords = "Audius Media Player"), Category = "Audius")
		void Resolve(FString Audius_Url);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Close Audius Interface", Keywords = "Audius, Music"), Category = "Audius")
		void Audius_Interface_Close();

protected:

	virtual void NativeOnInitialized();
	virtual void NativeConstruct();
	
};
