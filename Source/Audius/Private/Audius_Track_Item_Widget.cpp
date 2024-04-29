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

#include "Audius_Track_Item_Widget.h"
#include "Components/TextBlock.h"

void UAudius_Track_Item_Widget::NativeOnListItemObjectSet(UObject* ListItemObject) {
	
	UTrackData* Item = Cast<UTrackData>(ListItemObject);

	FString Item_Display_Text = Item->Track_Title.Append(" by ").Append(Item->Track_Artist);
	
	Track_Item_Text->SetText(FText::FromString(Item_Display_Text));

}

