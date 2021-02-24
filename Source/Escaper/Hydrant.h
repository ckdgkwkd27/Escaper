 

#pragma once

#include "GameInfo.h"
#include "Interactable.h"
#include "FireArea.h"
#include "EscaperGameInstance.h"
#include "Hydrant.generated.h"


UCLASS()
class ESCAPER_API AHydrant : public AInteractable
{
	GENERATED_BODY()
	
public:
	AHydrant();
	virtual void Interact();
	virtual void BeginPlay();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Fire", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFireArea> fireAreaClass;

	UPROPERTY(Category = "Fire", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AFireArea* fireArea;

	UPROPERTY(Category = "Fire", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<AFireArea*> fireAreas;

	UPROPERTY()
	UEscaperGameInstance* gameInstance;
};
