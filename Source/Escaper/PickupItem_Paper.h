 

#pragma once

#include "GameInfo.h"
#include "PickupItem.h"
#include "PickupItem_Paper.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API APickupItem_Paper : public APickupItem
{
	GENERATED_BODY()
	
public:
	APickupItem_Paper();
	virtual void BeginPlay();
	virtual void EndPlay(EEndPlayReason::Type reason);
};
