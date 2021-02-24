 

#pragma once

#include "GameInfo.h"
#include "UserController.h"
#include "UIPickupItem.h"
#include "Weapon.h"
#include "InteractClue.h"
#include "ItemObject.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

UENUM()
enum class ItemType : uint8 {
	WEAPON,
	ITEM
};

UCLASS()
class ESCAPER_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ItemType Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* Particle;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUIPickupItem> pickupUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UUIPickupItem* pickupUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> WeaponClass; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AInteractClue> ClueClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AWeapon* weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AInteractClue* interactClue;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemObject> ItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UItemObject* inventory_item;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void showUI();
	void deleteUI();

	TSubclassOf<AWeapon> GetWeaponClass() const {
		if (Type == ItemType::WEAPON)
			return WeaponClass;
		else
			return NULL;
	}

	ItemType GetType() const {
		return Type;
	}

	FText GetItemName() const {
		return Type == ItemType::WEAPON ? weapon->GetTitle() : interactClue->GetTitle();
	}

	UItemObject* GetItemObject() const {
		return inventory_item;
	}
};
