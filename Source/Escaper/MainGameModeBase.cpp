 


#include "MainGameModeBase.h"
#include "UserPlayer.h"
#include "EscaperGameInstance.h"
#include "UserController.h"

AMainGameModeBase::AMainGameModeBase() {
	//HUD 
	static ConstructorHelpers::FClassFinder<UUIPlayerHUD> UIPlayerHUDAsset(TEXT("WidgetBlueprint'/Game/UI/BPPlayerInfoHUD.BPPlayerInfoHUD_C'"));

	if (UIPlayerHUDAsset.Succeeded())
		UIPlayerHUDClass = UIPlayerHUDAsset.Class;

	//Player
	static ConstructorHelpers::FClassFinder<AUserPlayer> PlayerClass(TEXT("Blueprint'/Game/Player/BPUserPlayer.BPUserPlayer_C'"));
	
	if (PlayerClass.Succeeded())
		DefaultPawnClass = PlayerClass.Class;

	//PlayerController
	static ConstructorHelpers::FClassFinder<AUserController> ControllerClass(TEXT("Blueprint'/Game/Player/BPUserController.BPUserController_C'"));

	if (ControllerClass.Succeeded())
		PlayerControllerClass = ControllerClass.Class;

	//Inventory
	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryAsset(TEXT("WidgetBlueprint'/Game/UI/BPInventory.BPInventory_C'"));

	if (InventoryAsset.Succeeded()) 
		InventoryClass = InventoryAsset.Class;

	//Death Menu
	static ConstructorHelpers::FClassFinder<UUserWidget> DeathMenuAsset(TEXT("WidgetBlueprint'/Game/UI/BPDeath.BPDeath_C'"));
	if (DeathMenuAsset.Succeeded())
		DeathMenuClass = DeathMenuAsset.Class;

	//Pause Menu
	static ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuAsset(TEXT("WidgetBlueprint'/Game/UI/BPPause.BPPause_C'"));
	if (PauseMenuAsset.Succeeded())
		PauseMenuClass = PauseMenuAsset.Class;

	//Ending Menu
	static ConstructorHelpers::FClassFinder<UUIEnding> EndingMenuAsset(TEXT("WidgetBlueprint'/Game/UI/BPEnding.BPEnding_C'"));
	if (EndingMenuAsset.Succeeded())
		EndingClass = EndingMenuAsset.Class;
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(UIPlayerHUDClass))
	{
		UIPlayerHUD = Cast<UUIPlayerHUD>(CreateWidget(GetWorld(), UIPlayerHUDClass));

		if (UIPlayerHUD)
		{
			UIPlayerHUD->AddToViewport();

			UEscaperGameInstance* GameInst = Cast<UEscaperGameInstance>(GetGameInstance());
		}
	}

	if (IsValid(InventoryClass)) {
		Inventory = Cast<UUserWidget>(CreateWidget(GetWorld(), InventoryClass));
		if (IsValid(Inventory))
			Inventory->AddToViewport();
	}

	if (IsValid(DeathMenuClass)) {
		DeathMenu = Cast<UUserWidget>(CreateWidget(GetWorld(), DeathMenuClass));
		if (IsValid(DeathMenu))
			DeathMenu->AddToViewport();
	}

	if (IsValid(PauseMenuClass)) {
		PauseMenu = Cast<UUserWidget>(CreateWidget(GetWorld(), PauseMenuClass));
		if (IsValid(PauseMenu))
			PauseMenu->AddToViewport();
	}

	if (IsValid(EndingClass)) {
		EndingMenu = Cast<UUIEnding>(CreateWidget(GetWorld(), EndingClass));
		if (IsValid(EndingMenu))
			EndingMenu->AddToViewport();
	}
}

UUIPlayerHUD* AMainGameModeBase::GetPlayerHUD() const {
	return UIPlayerHUD;
}

UUserWidget* AMainGameModeBase::GetInventory() const {
	if(IsValid(Inventory))
		return Inventory;
	return nullptr;
}

UUserWidget* AMainGameModeBase::GetDeathMenu() const {
	if (IsValid(DeathMenu))
		return DeathMenu;
	return nullptr;
}

UUserWidget* AMainGameModeBase::GetPauseMenu() const
{
	if (IsValid(PauseMenu))
		return PauseMenu;
	return nullptr;
}

UUIEnding* AMainGameModeBase::GetEndingMenu() const
{
	if (IsValid(EndingMenu))
		return EndingMenu;
	return nullptr;
}