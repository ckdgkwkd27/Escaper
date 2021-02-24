 


#include "StartDoor.h"
#include "EscaperGameInstance.h"

AStartDoor::AStartDoor() : AInteractable() {

}

void AStartDoor::Interact() {
	Super::Interact();

	UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(GetGameInstance());
	gameInstance->SpawnRotation = FRotator(0, 0, 0);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Alley"));
}