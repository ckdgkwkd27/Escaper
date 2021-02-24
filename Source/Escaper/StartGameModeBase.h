 

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API AStartGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AStartGameModeBase();
	virtual void BeginPlay();

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> StartLevelWidgetClass;

	UPROPERTY()
	class UUserWidget* StartLevelWidget;
};
