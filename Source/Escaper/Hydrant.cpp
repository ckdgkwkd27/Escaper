 


#include "Hydrant.h"

AHydrant::AHydrant() : AInteractable(){
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);

	ConstructorHelpers::FClassFinder<AFireArea> fireAreaAsset(TEXT("Blueprint'/Game/Interactable/BPFireArea.BPFireArea_C'"));
	if (fireAreaAsset.Succeeded())
		fireAreaClass = fireAreaAsset.Class;
}

void AHydrant::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UEscaperGameInstance>(GetGameInstance());

	userPlayer = Cast<AUserPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (IsValid(userPlayer))
		Inventory = userPlayer->GetInventory();

	if (!gameInstance->bFireAreaSolved) {
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		for (int32 i = 0; i < 5; i++) {
			fireArea = GetWorld()->SpawnActor<AFireArea>(fireAreaClass, FVector::ZeroVector,
				FRotator::ZeroRotator, params);
			fireAreas.Add(fireArea);
		}
		int32 i = 0;
		for (auto fa : fireAreas) {
			if (IsValid(fa)) {
				fa->SetActorLocation(FVector(GetActorLocation().X + 100.f * i,
					GetActorLocation().Y + 300.f, GetActorLocation().Z + 100.f));
				i++;
			}
		}
	}
}

void AHydrant::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("Interact with Hydrant"));

	if (IsValid(Inventory)) {
		if (Inventory->FindItem(FText::FromString("FireHose"))) {
			for (auto fa : fireAreas) {
				if (IsValid(fa)) {
					fa->Destroy();
					gameInstance->bFireAreaSolved = true;
				}
			}
		}
	}

}


