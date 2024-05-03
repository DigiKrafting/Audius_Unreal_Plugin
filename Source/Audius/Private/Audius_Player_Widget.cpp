/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#include "Audius_Player_Widget.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/Image.h"
#include "Audius_Track_Item_Widget.h"
#include "Audius_Actor_Base.h"

void UAudius_Player_Widget::NativeOnInitialized() {
	
	Super::NativeOnInitialized();
    
}

void UAudius_Player_Widget::NativeConstruct() {

    Super::NativeConstruct();

    Audius_Widget_Text_Track_Combined = (UTextBlock*)this->GetWidgetFromName(*FString("Audius_Track_Combined"));
    Audius_Widget_Text_Track_Title = (UTextBlock*)this->GetWidgetFromName(*FString("Audius_Track_Title"));
    Audius_Widget_Text_Track_Artist = (UTextBlock*)this->GetWidgetFromName(*FString("Audius_Track_Artist"));
    
    if (Audius_Actor != nullptr) {
                
        Audius_Volume_Slider->SetValue(Audius_Actor->default_volume);

    }

}

void UAudius_Player_Widget::Update_Display_Text(FString Track_Title, FString Track_Artist) {

    if (Audius_Widget_Text_Track_Combined != nullptr) {

        Audius_Widget_Text_Track_Combined->SetText(FText::FromString(FString::Printf(TEXT("%s by %s"), *Track_Title, *Track_Artist)));
        
    } else {
        
        FString Display_Track_Title = FString(TEXT(""));
        FString Display_Track_Artist = FString(TEXT(""));

        if(Track_Title.Len()>=Max_Text_Length){
            Display_Track_Title = Track_Title.Left(Max_Text_Length).Append(TEXT("..."));
        } else {
            Display_Track_Title = Track_Title;
        }

        if(Track_Artist.Len()>=Max_Text_Length){
            Display_Track_Artist = Track_Artist.Left(Max_Text_Length).Append(TEXT("..."));
        } else {
            Display_Track_Artist = Track_Artist;
        }
        
        Audius_Widget_Text_Track_Title->SetText(FText::FromString(Display_Track_Title));
        Audius_Widget_Text_Track_Artist->SetText(FText::FromString(Display_Track_Artist));
        
    }
    
}

void UAudius_Player_Widget::Update_Volume(float volume) {
    
    if (Audius_Volume_Slider != nullptr) {

        Audius_Volume_Slider->SetValue(volume);

    }

}

void UAudius_Player_Widget::Set_Volume(float volume) {

    Audius_Actor->Set_Volume(volume);

}

void UAudius_Player_Widget::Next() {

    Audius_Actor->Queue_Next();

}

void UAudius_Player_Widget::Previous() {

    Audius_Actor->Queue_Previous();

}

void UAudius_Player_Widget::Pause() {

    Audius_Actor->Queue_Pause();
   
}

void UAudius_Player_Widget::Show_Pause_Icon() {

    Audius_Play_Icon->SetVisibility(ESlateVisibility::Hidden);
    Audius_Pause_Icon->SetVisibility(ESlateVisibility::Visible);
        
}

void UAudius_Player_Widget::Show_Play_Icon() {

    Audius_Pause_Icon->SetVisibility(ESlateVisibility::Hidden);
    Audius_Play_Icon->SetVisibility(ESlateVisibility::Visible);

}

void UAudius_Player_Widget::Audius_Interface_Open() {

    Audius_Actor->Audius_Interface_Open();

}

void UAudius_Player_Widget::Audius_Interface_Close() {

    Audius_Actor->Audius_Interface_Close();

}