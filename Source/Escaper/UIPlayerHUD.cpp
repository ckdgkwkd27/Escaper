 


#include "UIPlayerHUD.h"
#include "UserPlayer.h"
#include "Blueprint/WidgetTree.h"

void UUIPlayerHUD::NativePreConstruct() {
	Super::NativePreConstruct();
	
	SlotsBar = Cast<UVerticalBox>(GetWidgetFromName(TEXT("SlotBar")));
	Bullet_Cnt = Cast<UTextBlock>(GetWidgetFromName(TEXT("Bullet_Cnt")));
	Max_Bullet_Cnt = Cast<UTextBlock>(GetWidgetFromName(TEXT("Max_Bullet_Cnt")));
	Crosshairs = Cast<UImage>(GetWidgetFromName(TEXT("Crosshairs")));
	NotificationText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NotificationText")));
	HealthCircle = Cast<UImage>(GetWidgetFromName(TEXT("HealthCircle")));
	HealthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("HealthValue"))); 
	UIHorizontal = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("UIHorizontal")));

	//Slotbar Array

	if (!IsValid(SlotsBar)) {
		UE_LOG(LogTemp, Warning, TEXT("SlotBar Error"));
		return;
	}
	
	index = 0;
	bMsgShowed = false;
	fMsgTime = 0.f;
	fMsgTimeMax = 2.f;
}

void UUIPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

}

void UUIPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bMsgShowed) {
		if (fMsgTimeMax >= fMsgTime)
			SetNotiVisibility(ESlateVisibility::Visible);
		else {
			bMsgShowed = false;
			SetNotiVisibility(ESlateVisibility::Hidden);
			NotificationText->SetText(FText::FromString("Press F to interact"));
		}
		fMsgTime += InDeltaTime;
	}
}

void UUIPlayerHUD::SetBullet(int32 bulletCnt, int32 maxbulletCnt)
{
	Bullet_Cnt->SetText(FText::FromString(FString::FromInt(bulletCnt)));
	Max_Bullet_Cnt->SetText(FText::FromString(FString::FromInt(maxbulletCnt)));

}

void UUIPlayerHUD::SetHealth(int32 hp)
{
	AUserPlayer* userPlayer = Cast<AUserPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	int32 iMaxHP = userPlayer->GetMaxHelath();
	float HelathPercentage = (float)hp / (float)iMaxHP;

	HealthValue->SetText(FText::FromString(FString::FromInt(hp)));
	HealthCircle->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), HelathPercentage);
}

void UUIPlayerHUD::AddToSlot(AWeapon* weapon)
{
	UUIWeaponSlotbar* sb = tWeaponSlotArray[index];
	int32 size = tWeaponSlotArray.Num();
	if(IsValid(sb))
		sb->SetIconFromName(weapon->GetIconPath());
	sb->SetMaxBulletCnt(weapon->GetMaxBullet());
	sb->SetWeaponInfo(weapon);
	index++;

	UE_LOG(LogTemp, Warning, TEXT("TArray Size: %d"), *FString::FromInt(size));
}

AWeapon* UUIPlayerHUD::GetSlotInfo(int32 i) const {
	if (i > index) {
		UE_LOG(LogTemp, Warning, TEXT("i > index"));
		return nullptr;
	}
	UUIWeaponSlotbar* sb = tWeaponSlotArray[i];
	if (IsValid(sb)) {
		AWeapon* weapon = sb->GetWeaponInfo();
		return weapon;
	}
	UE_LOG(LogTemp, Warning, TEXT("NULL PASSED"));
	return nullptr;
}

TSubclassOf<AWeapon> UUIPlayerHUD::GetSlotClassInfo(int32 i) const
{

	return nullptr;
}

void UUIPlayerHUD::SetNotiText(FText text) {
	NotificationText->SetText(text);
	bMsgShowed = true;
}