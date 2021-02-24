 

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "InteractClue.generated.h"

UCLASS()
class ESCAPER_API AInteractClue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractClue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString IconPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText RarityAndCategory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText Description;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void SetItemName(FString str) {
		ItemName = str;
	}

	virtual FString GetItemName() {
		return ItemName;
	}

	virtual void SetTitle(FText str) {
		Title = str;
	}

	virtual FText GetTitle() const {
		return Title;
	}

	virtual FText GetRarityAndCategory() const {
		return RarityAndCategory;
	}

	virtual FText GetDescription() const {
		return Description;
	}

	virtual void SetDescription(FText text) {
		Description = text;
	}

	virtual FString GetIconPath() const {
		return IconPath;
	}

	virtual void SetIconPath(const FString& path) {
		IconPath = path;
	}

	virtual UStaticMesh* GetItemMesh() const {
		return ItemMesh;
	}
};
