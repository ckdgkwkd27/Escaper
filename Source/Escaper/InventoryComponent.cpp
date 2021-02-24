 


#include "InventoryComponent.h"
#include "EscaperGameInstance.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{


}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& item : DefaultItems) {
		AddItem(item);
	}

	//game instance get
	UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TArray<UItemObject*> IniItems = gameInstance->GetAllInventoryItem();

	for (auto& item : IniItems) {
		if(!FindItem(item->ItemDisplayName))
			AddItem(item);
	}
	
}


bool UInventoryComponent::AddItem(UItemObject* item)
{
	if (!IsValid(item))
		return false;

	//item->InventoryComponent = this;
	item->AddToRoot();

	Items.Add(item);
	OnInventoryUpdated.Broadcast(); 

	//update to game instance
	UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->AddItem(item);

	return true;
}

bool UInventoryComponent::FindItem(FText name)
{
	if (Items.Num() == 0)
		return false;

	for (auto& item : Items) {
		if (item->ItemDisplayName.EqualTo(name))
			return true;
	}
	return false;
}

