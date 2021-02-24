 


#include "UIStartMenu.h"
#include "EscaperGameInstance.h"

void UUIStartMenu::NativePreConstruct() {
	Super::NativePreConstruct();

	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	CreditButton = Cast<UButton>(GetWidgetFromName(TEXT("CreditButton")));
	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));
	Background = Cast<UImage>(GetWidgetFromName(TEXT("MediaBG")));
	StartText = Cast<UTextBlock>(GetWidgetFromName(TEXT("StartText")));
	CreditText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CreditText")));
}

void UUIStartMenu::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UUIStartMenu::StartGame);
	CreditButton->OnClicked.AddDynamic(this, &UUIStartMenu::ShowCredit);
	ExitButton->OnClicked.AddDynamic(this, &UUIStartMenu::EndGame);

	StartButton->OnHovered.AddDynamic(this, &UUIStartMenu::PlayHoverSound);
	CreditButton->OnHovered.AddDynamic(this, &UUIStartMenu::PlayHoverSound);
	ExitButton->OnHovered.AddDynamic(this, &UUIStartMenu::PlayHoverSound);
}

void UUIStartMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UUIStartMenu::StartGame()
{
	StartText->SetText(FText::FromString("Normal"));
	CreditText->SetText(FText::FromString("Hard"));

	StartButton->OnClicked.RemoveDynamic(this, &UUIStartMenu::StartGame);
	CreditButton->OnClicked.RemoveDynamic(this, &UUIStartMenu::ShowCredit);

	StartButton->OnClicked.AddDynamic(this, &UUIStartMenu::SelectNormal);
	CreditButton->OnClicked.AddDynamic(this, &UUIStartMenu::SelectHard);
}

void UUIStartMenu::ShowCredit()
{
	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/AtmosphericMainMenu/Audio/S_Jump.S_Jump'"));
	UGameplayStatics::PlaySound2D(GetWorld(), SoundAsset);

	FPlatformProcess::LaunchURL(TEXT("https://github.com/lchbest10/Escaper"), NULL, NULL);
}

void UUIStartMenu::EndGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/AtmosphericMainMenu/Audio/S_Jump.S_Jump'"));
	UGameplayStatics::PlaySound2D(GetWorld(), SoundAsset);
}

void UUIStartMenu::PlayHoverSound()
{
	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/AtmosphericMainMenu/Audio/S_Option.S_Option'"));
	UGameplayStatics::PlaySound2D(GetWorld(), SoundAsset);
}

void UUIStartMenu::SelectNormal()
{
	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/AtmosphericMainMenu/Audio/S_Jump.S_Jump'"));
	UGameplayStatics::PlaySound2D(GetWorld(), SoundAsset);

	//GameInstance Difficulty 저장
	UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->diff = EDifficulty::Normal;
	gameInstance->SpawnRotation = FRotator(0, -90.f, 0);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("AptRuin"));
}

void UUIStartMenu::SelectHard()
{
	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/AtmosphericMainMenu/Audio/S_Jump.S_Jump'"));
	UGameplayStatics::PlaySound2D(GetWorld(), SoundAsset);

	//GameInstance Difficulty 저장
	UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->diff = EDifficulty::Hard;
	gameInstance->SpawnRotation = FRotator(0, -90.f, 0);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("AptRuin"));
}
