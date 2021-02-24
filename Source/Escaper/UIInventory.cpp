 


#include "UIInventory.h"
#include "ItemObject.h"

void UUIInventory::NativePreConstruct()
{
	UI_InventoryView = Cast<UWrapBox>(GetWidgetFromName(TEXT("UI_InventoryView")));

	//static ConstructorHelpers::FClassFinder<UUserWidget> widget_asset(TEXT("WidgetBlueprint'/Game/UI/BPInventoryItem.BPInventoryItem_C'"));
	//if (widget_asset.Succeeded())
	//	ItemUIClass = widget_asset.Class;
}

void UUIInventory::NativeConstruct()
{
	userPlayer = Cast<AUserPlayer>(GetOwningPlayer());
	inventory = userPlayer->GetInventory();
	inventory->OnInventoryUpdated.AddDynamic(this, &UUIInventory::RefreshInventory);
	InitializeInventory(inventory);
}

void UUIInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UUIInventory::RefreshInventory()
{
	InitializeInventory(inventory);
}

void UUIInventory::InitializeInventory(UInventoryComponent* _inventory)
{
	UI_InventoryView->ClearChildren();
	TArray<UItemObject*> itemArray = _inventory->Items;
	for (auto item : itemArray) {
		UI_Item = CreateWidget<UUserWidget>(this, ItemUIClass);
		UI_InventoryView->AddChildToWrapBox(UI_Item);
	}
}
