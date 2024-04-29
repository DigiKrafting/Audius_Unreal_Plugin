/*

	Copyright 2024 Audius

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

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
