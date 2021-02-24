 

#pragma once

#include "GameInfo.h"
#include "UserPlayer.h"
#include "UserController.h"
#include "InventoryComponent.h"
#include "UIPlayerHUD.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class ESCAPER_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	UPROPERTY(Category = "Box", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	UPROPERTY()
	AUserPlayer* userPlayer;

	UPROPERTY()
	AUserController* userController;

	UPROPERTY()
	UUIPlayerHUD* playerHUD;

	UPROPERTY()
	UInventoryComponent* Inventory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() {}
	void CallLog();
};
