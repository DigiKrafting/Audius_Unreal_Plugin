/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

#pragma once

#include "Modules/ModuleManager.h"

class FAudiusModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
