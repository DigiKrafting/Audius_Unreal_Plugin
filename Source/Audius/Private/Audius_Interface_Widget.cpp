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

#include "Audius_Interface_Widget.h"
#include "Audius_Track_Item_Widget.h"
#include "Audius_Actor_Base.h"

void UAudius_Interface_Widget::NativeOnInitialized() {
	
	Super::NativeOnInitialized();

}

void UAudius_Interface_Widget::NativeConstruct() {

    Super::NativeConstruct();

    Audius_Actor->Audius_Search_List_View = Audius_Search_List_View;

}

void UAudius_Interface_Widget::Search(FString Search_Query) {

    Audius_Actor->Search(Search_Query);

}

void UAudius_Interface_Widget::Search_List_Item_Click(UObject* Item) {

    Audius_Actor->Search_List_Item_Click(Item);

    Audius_Interface_Close();
    
}

void UAudius_Interface_Widget::Resolve(FString Audius_Url) {

    Audius_Actor->Resolve(Audius_Url);

}

void UAudius_Interface_Widget::Audius_Interface_Close() {
    
    Audius_Actor->Audius_Interface_Close();

}