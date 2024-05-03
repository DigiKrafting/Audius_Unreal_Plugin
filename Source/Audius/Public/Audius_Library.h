/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Audius_API.h"
#include "Audius_Library.generated.h"

UCLASS()
class AUDIUS_API UAudius_Library : public UBlueprintFunctionLibrary {
	
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Audius API Object", Keywords = "Audius Music API Endpoint"), Category = "Audius")
	static class UAudius_API* Create_Audius_API_Object();

};
