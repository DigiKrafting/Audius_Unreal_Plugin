/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#include "Actors/Audius_Actor_Player.h"

AAudius_Actor_Player::AAudius_Actor_Player() {
	
	Audius_Actor_Type = EAudius_Actor_Type::Player;

}

void AAudius_Actor_Player::PostInitializeComponents() {

	Super::PostInitializeComponents();

}