 

#pragma once

#include "GameInfo.h"
#include "Interactable.h"
#include "StartDoor.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API AStartDoor : public AInteractable
{
	GENERATED_BODY()
	
public:
	AStartDoor();
	
	virtual void Interact();
};
