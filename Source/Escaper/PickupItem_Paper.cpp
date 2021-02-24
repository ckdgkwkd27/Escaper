 


#include "PickupItem_Paper.h"

APickupItem_Paper::APickupItem_Paper() {
	Type = ItemType::ITEM;

	//interact clue¿Œ bp 
	static ConstructorHelpers::FClassFinder<AInteractClue> ClueAsset(TEXT("Blueprint'/Game/Interactable/Clue/BPPaper.BPPaper_C'"));

	if (ClueAsset.Succeeded())
		ClueClass = ClueAsset.Class;

	interactClue = ClueClass->GetDefaultObject<AInteractClue>();
	interactClue->SetDescription(FText::FromString("Its Written 1285.\nWhat does it mean?"));

	static ConstructorHelpers::FClassFinder<UItemObject> ItemAsset(TEXT("Blueprint'/Game/Interactable/Item/BPItem_Paper.BPItem_Paper_C'"));
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

void APickupItem_Paper::BeginPlay()
{
	Super::BeginPlay();
	inventory_item->AddToRoot();
}

void APickupItem_Paper::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
	inventory_item->RemoveFromRoot();
	inventory_item->ConditionalBeginDestroy();
}
