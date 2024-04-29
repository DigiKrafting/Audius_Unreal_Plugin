# Audius Unreal Engine Plugin
![banner.png](https://github.com/DigiKrafting/Audius_Unreal_Plugin/raw/main/screenshots/banner.png)

The Audius API is entirely free to use. Audius asks that you adhere to the guidelines in this doc [https://audiusproject.github.io/api-docs/#audius-api-docs](https://audiusproject.github.io/api-docs/#audius-api-docs) and always credit artists.

## Supported Engine Versions

* 5.0

\* *For other supported engine versions see* [https://github.com/DigiKrafting/Audius_Unreal_Plugin](https://github.com/DigiKrafting/Audius_Unreal_Plugin)
![main.png](https://github.com/DigiKrafting/Audius_Unreal_Plugin/raw/main/screenshots/main.png)

## Usage

Drag the [Audius_Player_Actor] into your level and configure options.

![actor.png](https://github.com/DigiKrafting/Audius_Unreal_Plugin/raw/main/screenshots/actor.png)

## C++ Usage

Add "Audius" to the PublicDependencyModuleNames in your *project*.Build.cs

```
PublicDependencyModuleNames.AddRange(new string[] {
    "Core",
    "CoreUObject",
    "Engine",
    "InputCore",
    "HeadMountedDisplay",
    "GameplayTags",
    "Audius"
});
```

```
#include "Audius_Actor_Base.h"
#include "Kismet/GameplayStatics.h" 
```

```
FTransform Audius_Actor_SpawnTransform(FRotator::ZeroRotator, FVector::ZeroVector);
AAudius_Actor_Base* Audius_Actor_Base = Cast<AAudius_Actor_Base>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AAudius_Actor_Base::StaticClass(), Audius_Actor_SpawnTransform));

if (Audius_Actor_Base != nullptr) {
	
	Audius_Actor_Base->Audius_Actor_Type = EAudius_Actor_Type::Player;
	Audius_Actor_Base->Audius_Queue_Ended_Action = EAudius_Queue_Ended_Action::Replay;
	Audius_Actor_Base->Audius_Default_Stream = EAudius_Default_Stream::Trending_Underground;
	Audius_Actor_Base->Audius_Auto_Play = false;
	
	UGameplayStatics::FinishSpawningActor(Audius_Actor_Base, Audius_Actor_SpawnTransform);
	
}
```


