 

#pragma once

#include "GameInfo.h"
#include "Interactable.h"
#include "Closet.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API ACloset : public AInteractable
{
	GENERATED_BODY()
	
public:
	ACloset();
	virtual void BeginPlay();
	virtual void Interact();

private:
	UPROPERTY(Category = "Closet", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Closet;

	UPROPERTY(Category = "Closet", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftDoor;

	UPROPERTY(Category = "Closet", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool IsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool IsOpened;
};
