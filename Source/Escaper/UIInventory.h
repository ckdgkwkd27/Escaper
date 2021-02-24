 

#pragma once

#include "GameInfo.h"
#include "UserPlayer.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "UIInventory.generated.h"


UCLASS()
class ESCAPER_API UUIInventory : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWrapBox* UI_InventoryView;
	
	UPROPERTY()
	AUserPlayer* userPlayer;

	UPROPERTY()
	UInventoryComponent* inventory;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemUIClass;

	UPROPERTY()
	UUserWidget* UI_Item;

public:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void RefreshInventory();

	UFUNCTION()
	void InitializeInventory(UInventoryComponent* _inventory);
};
