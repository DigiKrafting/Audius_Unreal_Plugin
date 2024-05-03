/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#include "Audius_Track_Item_Widget.h"
#include "Components/TextBlock.h"

void UAudius_Track_Item_Widget::NativeOnListItemObjectSet(UObject* ListItemObject) {
	
	UTrackData* Item = Cast<UTrackData>(ListItemObject);

	FString Item_Display_Text = Item->Track_Title.Append(" by ").Append(Item->Track_Artist);
	
	Track_Item_Text->SetText(FText::FromString(Item_Display_Text));

}

