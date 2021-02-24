 


#include "DigitalPassword.h"
#include "UserPlayer.h"
#include "UserController.h"
#include "MainGameModeBase.h"

ADigitalPassword::ADigitalPassword() : AInteractable() {
	static ConstructorHelpers::FClassFinder<UUIPassword> WidgetAsset(TEXT("WidgetBlueprint'/Game/UI/BPPassword.BPPassword_C'"));
	
	if (WidgetAsset.Succeeded())
		WidgetClass = WidgetAsset.Class;
}

void ADigitalPassword::BeginPlay() {
	Super::BeginPlay();

	userWidget = CreateWidget<UUIPassword>(GetWorld(), WidgetClass);
	if (IsValid(userWidget)) {
		userWidget->AddToViewport();
		userWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ADigitalPassword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector userloc = (Cast<AUserPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn()))->GetActorLocation();
	FVector myloc = GetActorLocation();
	playerHUD = userPlayer->GetPlayerHUD();

	if (userWidget->IsVisible() && FVector::Distance(myloc, userloc) > 300.f) {
		userWidget->SetVisibility(ESlateVisibility::Hidden);
		userController->bShowMouseCursor = false;
	}
}

void ADigitalPassword::Interact()
{
	if(IsValid(userWidget))
		userWidget->SetVisibility(ESlateVisibility::Visible);
	
	userController->bShowMouseCursor = true;
}


