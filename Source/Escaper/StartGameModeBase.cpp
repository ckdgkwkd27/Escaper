 


#include "StartGameModeBase.h"
#include "StartController.h"

AStartGameModeBase::AStartGameModeBase() {
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AStartController::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> StartAsset(TEXT("WidgetBlueprint'/Game/UI/BPStartMenu.BPStartMenu_C'"));
	if (StartAsset.Succeeded())
		StartLevelWidgetClass = StartAsset.Class;
}

void AStartGameModeBase::BeginPlay() {
	StartLevelWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), StartLevelWidgetClass));

	if (IsValid(StartLevelWidget))
		StartLevelWidget->AddToViewport();
}