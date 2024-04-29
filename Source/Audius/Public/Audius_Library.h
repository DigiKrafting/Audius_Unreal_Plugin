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