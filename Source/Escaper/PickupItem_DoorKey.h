 

#pragma once

#include "GameInfo.h"
#include "PickupItem.h"
#include "PickupItem_DoorKey.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API APickupItem_DoorKey : public APickupItem
{
	GENERATED_BODY()
	
public:
	APickupItem_DoorKey();
	virtual void BeginPlay();
	virtual void EndPlay(EEndPlayReason::Type reason);
};
