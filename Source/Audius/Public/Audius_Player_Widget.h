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

#include "Audius_Player_Widget.generated.h"

class UTextBlock;
class UListView;
class UImage;
class USlider;
class UTrackData;
class AAudius_Actor_Base;

UCLASS()
class AUDIUS_API UAudius_Player_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	AAudius_Actor_Base* Audius_Actor;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Audius Interface", Keywords = "Audius, Music"), Category = "Audius")
	void Audius_Interface_Open();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Close Audius Interface", Keywords = "Audius, Music"), Category = "Audius")
	void Audius_Interface_Close();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Audius Volume", Keywords = "Audius, Music"), Category = "Audius")
	void Set_Volume(float volume);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Player Next", Keywords = "Audius Music Player"), Category = "Audius")
	void Next();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Player Previous", Keywords = "Audius Music Player"), Category = "Audius")
	void Previous();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Audius Player Pause", Keywords = "Audius Music Player"), Category = "Audius")
	void Pause();
	
	void Show_Pause_Icon();
	void Show_Play_Icon();

	UTextBlock* Audius_Widget_Text_Track_Combined;
	UTextBlock* Audius_Widget_Text_Track_Title;
	UTextBlock* Audius_Widget_Text_Track_Artist;

	UPROPERTY(meta = (BindWidget))
	USlider* Audius_Volume_Slider;

	UPROPERTY(meta = (BindWidget))
	UImage* Audius_Pause_Icon;

	UPROPERTY(meta = (BindWidget))
	UImage* Audius_Play_Icon;

	/** Maximum Length of Characters to display for Title/Artist */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audius")
	int32 Max_Text_Length = 40;

	void Update_Display_Text(FString Track_Title, FString Track_Artist);
	
protected:

	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

	void Update_Volume(float volume);


};
