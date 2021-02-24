 

#pragma once

#include "Interactable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API ADoor : public AInteractable
{
	GENERATED_BODY()
	
public:
	// Inherited via AInteractable
	ADoor();
	virtual void BeginPlay();
	virtual void Interact() override;

public:
	UPROPERTY(Category = "Door", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Frame;

	UPROPERTY(Category = "Door", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool IsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool IsOpened;
};
