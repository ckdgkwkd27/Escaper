 

#pragma once

#include "GameInfo.h"
#include "Interactable.h"
#include "UIPassword.h"
#include "UIPlayerHUD.h"
#include "DigitalPassword.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API ADigitalPassword : public AInteractable
{
	GENERATED_BODY()
	
public:
	ADigitalPassword();
	virtual void BeginPlay();
	virtual void Interact();
	virtual void Tick(float DeltaTime);

private:
	UPROPERTY()
	UUIPlayerHUD* userHUD;

	UPROPERTY()
	TSubclassOf<UUIPassword> WidgetClass;

	UPROPERTY()
	UUIPassword* userWidget;

	UPROPERTY()
	AUserController* uc;

	UPROPERTY()
	AUserPlayer* up;
};
