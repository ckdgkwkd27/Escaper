 


#include "Interactable.h"

// Sets default values
AInteractable::AInteractable()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetCollisionProfileName("Interactable");

	SetRootComponent(Box);

}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	userController = Cast<AUserController>(GetWorld()->GetFirstPlayerController());
	userPlayer = Cast<AUserPlayer>(userController->GetPawn());
	Inventory = userPlayer->GetInventory();
	playerHUD = userPlayer->GetPlayerHUD();
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractable::CallLog()
{
	
}

