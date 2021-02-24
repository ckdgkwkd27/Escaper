 

#pragma once

#include "GameInfo.h"
#include "ItemObject.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	bool AddItem(UItemObject* item);

	UFUNCTION(BlueprintCallable)
	bool FindItem(FText name);
		
public:
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<UItemObject*> DefaultItems;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TArray<UItemObject*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UItemObject* sample;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
