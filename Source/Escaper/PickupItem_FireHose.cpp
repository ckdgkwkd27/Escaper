 


#include "PickupItem_FireHose.h"
#include "InteractClue.h"

APickupItem_FireHose::APickupItem_FireHose() : APickupItem(){
	Type = ItemType::ITEM;

	static ConstructorHelpers::FClassFinder<AInteractClue> ClueAsset(TEXT("Blueprint'/Game/Interactable/Clue/BPFireHose.BPFireHose_C'"));
	if (ClueAsset.Succeeded())
		ClueClass = ClueAsset.Class;

	static ConstructorHelpers::FClassFinder<UItemObject> ItemAsset(TEXT("Blueprint'/Game/Interactable/Item/BPItem_FireHose.BPItem_FireHose_C'"));
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

void APickupItem_FireHose::BeginPlay()
{
	Super::BeginPlay();
	inventory_item->AddToRoot();
}

void APickupItem_FireHose::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
	inventory_item->RemoveFromRoot();
	inventory_item->ConditionalBeginDestroy();
}
