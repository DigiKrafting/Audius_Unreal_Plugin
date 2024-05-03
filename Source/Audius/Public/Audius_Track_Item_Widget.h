/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

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

