/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#pragma once

#include "Audius_Actor_Base.h"

#include "Audius_Actor_Player.generated.h"

UCLASS()
class AUDIUS_API AAudius_Actor_Player : public AAudius_Actor_Base
{

	GENERATED_BODY()

public:

	AAudius_Actor_Player();

protected:

	virtual void PostInitializeComponents();

};