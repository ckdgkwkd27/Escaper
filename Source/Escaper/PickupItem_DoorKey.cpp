 


#include "PickupItem_DoorKey.h"
#include "InteractClue.h"

APickupItem_DoorKey::APickupItem_DoorKey() : APickupItem() {
	Type = ItemType::ITEM;

	//interact clue¿Œ bp 
	static ConstructorHelpers::FClassFinder<AInteractClue> ClueAsset(TEXT("Blueprint'/Game/Interactable/Clue/BPDoorKey.BPDoorKey_C'"));
	if (ClueAsset.Succeeded())
		ClueClass = ClueAsset.Class;

	static ConstructorHelpers::FClassFinder<UItemObject> ItemAsset(TEXT("Blueprint'/Game/Interactable/Item/BPItem_DoorKey.BPItem_DoorKey_C'"));
	if (ItemAsset.Succeeded())
		ItemClass = ItemAsset.Class;

	interactClue = ClueClass->GetDefaultObject<AInteractClue>();
	inventory_item = ItemClass->GetDefaultObject<UItemObject>();

	inventory_item->PickupMesh = interactClue->GetItemMesh();
	UTexture2D* icon = LoadObject<UTexture2D>(nullptr, *(interactClue->GetIconPath()));
	inventory_item->Icon = icon;
	inventory_item->amount = 1;
	inventory_item->ItemDisplayName = interactClue->GetTitle();
	inventory_item->ItemDescription = interactClue->GetDescription();
}

void APickupItem_DoorKey::BeginPlay()
{
	Super::BeginPlay();
	inventory_item->AddToRoot();
}

void APickupItem_DoorKey::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
	inventory_item->RemoveFromRoot();
	inventory_item->ConditionalBeginDestroy();
}
