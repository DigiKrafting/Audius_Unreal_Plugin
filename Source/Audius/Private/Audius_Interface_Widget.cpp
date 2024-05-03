/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

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