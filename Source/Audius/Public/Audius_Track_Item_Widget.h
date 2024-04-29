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
#include "Blueprint/IUserObjectListEntry.h"
#include "Audius_Track_Item_Widget.generated.h"

UCLASS()
class  UTrackData : public UObject {

	GENERATED_BODY()

public:

	FString Track_Id;
	FString Track_Title;
	FString Track_Artist;
	FString Track_Artwork_Url;
	FString Track_Stream_Url;

};

UCLASS(Abstract)
class UAudius_Track_Item_Widget : public UUserWidget, public IUserObjectListEntry
{

private:

	GENERATED_BODY()

protected:

	// IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	// IUserObjectListEntry

//	UPROPERTY(meta = (BindWidget))
//	class UImage* IconImage;

	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* Text_Track_Title;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Track_Item_Text;

};

