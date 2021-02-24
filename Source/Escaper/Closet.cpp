 


#include "Closet.h"
#include "InventoryComponent.h"

ACloset::ACloset() : AInteractable() {
	Closet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Closet"));
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));

	Closet->SetupAttachment(Box);
	LeftDoor->SetupAttachment(Box);
	RightDoor->SetupAttachment(Box);

	IsLocked = false;
	IsOpened = false;

	Closet->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftDoor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightDoor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACloset::BeginPlay()
{
	Super::BeginPlay();

}

void ACloset::Interact()
{
	Super::Interact();
	if (!IsValid(Inventory)) {
		return;
	}

	bool IsFound = Inventory->FindItem(FText::FromString("DoorKey"));
	if (IsLocked && !IsFound)
		return;

	//���� �ݸ����� �̻��ϴ� �����غ���.
	if (!IsOpened) {
		LeftDoor->SetRelativeRotation(FRotator(0.f, 120.f, 0.f).Quaternion());
		RightDoor->SetRelativeRotation(FRotator(0.f, -120.f, 0.f).Quaternion());
		Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
		IsOpened = true;
	}
	else {
		LeftDoor->SetRelativeRotation(FRotator(0.f, 0.f, 0.f).Quaternion());
		RightDoor->SetRelativeRotation(FRotator(0.f, 0.f, 0.f).Quaternion());
		Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
		IsOpened = false;
	}
}
