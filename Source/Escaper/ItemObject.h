 

#pragma once

#include "GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

class UInventoryComponent;

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class ESCAPER_API UItemObject : public UObject
{
	GENERATED_BODY()
	
public:
	UItemObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText UseActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UStaticMesh* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemDescription;

	//UPROPERTY()
	//UInventoryComponent* InventoryComponent;

};
