 


#include "UIPassword.h"
#include "UserPlayer.h"
#include "MainGameModeBase.h"
#include "EscaperGameInstance.h"

void UUIPassword::NativePreConstruct() {
	Button0 = Cast<UButton>(GetWidgetFromName(TEXT("Button_0")));
	Button1 = Cast<UButton>(GetWidgetFromName(TEXT("Button_1")));
	Button2 = Cast<UButton>(GetWidgetFromName(TEXT("Button_2")));
	Button3 = Cast<UButton>(GetWidgetFromName(TEXT("Button_3")));
	Button4 = Cast<UButton>(GetWidgetFromName(TEXT("Button_4")));
	Button5 = Cast<UButton>(GetWidgetFromName(TEXT("Button_5")));
	Button6 = Cast<UButton>(GetWidgetFromName(TEXT("Button_6")));
	Button7 = Cast<UButton>(GetWidgetFromName(TEXT("Button_7")));
	Button8 = Cast<UButton>(GetWidgetFromName(TEXT("Button_8")));
	Button9 = Cast<UButton>(GetWidgetFromName(TEXT("Button_9")));
	ButtonEnter = Cast<UButton>(GetWidgetFromName(TEXT("Button_Enter")));
	ButtonClear = Cast<UButton>(GetWidgetFromName(TEXT("Button_Clear")));
	PwdText = Cast<UTextBlock>(GetWidgetFromName(TEXT("PasswdText")));

	password = FString("");
	bShowMessage = false;
	fShowMsgTime = 0.f;
	fShowMsgTimeMax = 2.f;
}

void UUIPassword::NativeConstruct()
{
	if(!IsValid(PwdText))
		UE_LOG(LogTemp, Warning, TEXT("Wrong Text"));

	Button0->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked0);
	Button1->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked1);
	Button2->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked2);
	Button3->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked3);
	Button4->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked4);
	Button5->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked5);
	Button6->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked6);
	Button7->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked7);
	Button8->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked8);
	Button9->OnClicked.AddDynamic(this, &UUIPassword::ButtonClicked9);
	ButtonClear->OnClicked.AddDynamic(this, &UUIPassword::ButtonClickedClear);
	ButtonEnter->OnClicked.AddDynamic(this, &UUIPassword::ButtonClickedEnter);
}

void UUIPassword::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{	

}

void UUIPassword::ButtonClicked0()
{
	if (password.Len() == 4)
		return;

	password.Append("0");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked1()
{
	if (password.Len() == 4)
		return;

	password.Append("1");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked2()
{
	if (password.Len() == 4)
		return;

	password.Append("2");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked3()
{
	if (password.Len() == 4)
		return;

	password.Append("3");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked4()
{
	if (password.Len() == 4)
		return;

	password.Append("4");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked5()
{
	if (password.Len() == 4)
		return;

	password.Append("5");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked6()
{
	if (password.Len() == 4)
		return;

	password.Append("6");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked7()
{
	if (password.Len() == 4)
		return;

	password.Append("7");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked8()
{
	if (password.Len() == 4)
		return;

	password.Append("8");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClicked9()
{
	if (password.Len() == 4)
		return;

	password.Append("9");
	PwdText->SetText(FText::FromString(password));
}

void UUIPassword::ButtonClickedEnter()
{
	
	if (password.Equals("1285")) {
		password = "CORRECT";
		PwdText->SetText(FText::FromString(password));

		Button0->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked0);
		Button1->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked1);
		Button2->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked2);
		Button3->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked3);
		Button4->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked4);
		Button5->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked5);
		Button6->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked6);
		Button7->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked7);
		Button8->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked8);
		Button9->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClicked9);
		ButtonClear->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClickedClear);
		ButtonEnter->OnClicked.RemoveDynamic(this, &UUIPassword::ButtonClickedEnter);

		//포탈 열기 설정 (gameInstance)
		gameInstance = Cast<UEscaperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		gameInstance->bPortalLocked = false;


		if (!gameInstance->bPortalLocked) {
			AMainGameModeBase* gameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
			UUIPlayerHUD* playerHUD = gameMode->GetPlayerHUD();

			playerHUD->SetNotiText(FText::FromString("PORTAL IN SOMEWHERE HAS OPENED!"));
		}
	}
	else {
		password.Empty();
		PwdText->SetText(FText::FromString(password));
	}
}

void UUIPassword::ButtonClickedClear()
{
	password.Empty();
	PwdText->SetText(FText::FromString(password));
}
