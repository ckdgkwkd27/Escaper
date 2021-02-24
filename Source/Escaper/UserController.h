 

#pragma once

#include "GameInfo.h"
#include "EscaperGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "UserController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API AUserController : public APlayerController
{
	GENERATED_BODY()

public:
	AUserController();


protected:
	virtual void BeginPlay();
	
};
