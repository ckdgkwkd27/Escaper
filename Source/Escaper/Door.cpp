 


#include "Door.h"
#include "UserPlayer.h"
#include "InventoryComponent.h"

ADoor::ADoor() : AInteractable() {
	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	Frame->SetupAttachment(Box);
	Door->SetupAttachment(Box);

	IsLocked = false;
	IsOpened = false;
}

void ADoor::BeginPlay() {
	Super::BeginPlay();
	//userPlayer = Cast<AUserPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//Inventory = userPlayer->GetInventory();
}

void ADoor::Interact()
{
	Super::Interact();

	bool IsFound = Inventory->FindItem(FText::FromString("DoorKey"));
	if (IsLocked && !IsFound)
		return;

	//여기 콜리젼이 이상하니 수정해볼것.
	if (!IsOpened) {
		Door->SetRelativeRotation(FRotator(0.f, -125.f, 0.f).Quaternion());
		Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
		IsOpened = true;
	}
	else {
		Door->SetRelativeRotation(FRotator(0.f, 90.f, 0.f).Quaternion());
		Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
		IsOpened = false;
	}
}
