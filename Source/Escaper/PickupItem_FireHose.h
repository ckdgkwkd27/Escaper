 

#pragma once

#include "GameInfo.h"
#include "PickupItem.h"
#include "PickupItem_FireHose.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API APickupItem_FireHose : public APickupItem
{
	GENERATED_BODY()
	
public:
	APickupItem_FireHose();
	virtual void BeginPlay();
	virtual void EndPlay(EEndPlayReason::Type reason);

};
