 


#include "UserController.h"
#include "UserPlayer.h"

AUserController::AUserController() {
	
}

void AUserController::BeginPlay() {
	Super::BeginPlay();

	AUserPlayer* userPlayer = Cast<AUserPlayer>(GetPawn());

	////GameInstance에서 정보update
	//UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(GetGameInstance());
	//if (IsValid(gameInstance->GetInventoryInfo())) {
	//	PrintViewport(30.f, FColor::Emerald, TEXT("Update Inventory Info"));
	//	userPlayer->SetInventoryComponent(gameInstance->GetInventoryInfo());
	//}
	//else
	//	PrintViewport(30.f, FColor::Red, TEXT("NOT CALLED"));
}