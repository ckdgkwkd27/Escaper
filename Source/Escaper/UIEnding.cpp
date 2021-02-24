 


#include "UIEnding.h"
#include "EscaperGameInstance.h"

void UUIEnding::NativePreConstruct()
{
	ui_Second = Cast<UTextBlock>(GetWidgetFromName(TEXT("Second")));
	ui_MenuButton = Cast<UButton>(GetWidgetFromName(TEXT("MenuButton")));
	ui_ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));
}

void UUIEnding::NativeConstruct()
{
	ui_MenuButton->OnClicked.AddDynamic(this, &UUIEnding::MainMenu);
	ui_ExitButton->OnClicked.AddDynamic(this, &UUIEnding::Exit);
}

void UUIEnding::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UUIEnding::SetSeconds(float sec)
{
	FString sec_str = FString::SanitizeFloat(sec) + FString(" seconds");
	FText sec_text = FText::FromString(sec_str);
	ui_Second->SetText(sec_text);
}

void UUIEnding::MainMenu()
{
	UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(GetGameInstance());
	gameInstance->Init();
	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartMenu"));
}

void UUIEnding::Exit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
