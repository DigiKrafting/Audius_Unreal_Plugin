/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#include "Audius_Library.h"

// #################################################################################################################################################################################################
// HELPER FUNCTIONS
// #################################################################################################################################################################################################

class UAudius_API* UAudius_Library::Create_Audius_API_Object() {
	
	UAudius_API* _Audius_API = NewObject<UAudius_API>(UAudius_API::StaticClass(), TEXT("Audius_API"));

	return _Audius_API;

}
