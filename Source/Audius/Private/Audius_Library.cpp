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

#include "Audius_Library.h"

// #################################################################################################################################################################################################
// HELPER FUNCTIONS
// #################################################################################################################################################################################################

class UAudius_API* UAudius_Library::Create_Audius_API_Object() {
	
	UAudius_API* _Audius_API = NewObject<UAudius_API>(UAudius_API::StaticClass(), TEXT("Audius_API"));

	return _Audius_API;

}
