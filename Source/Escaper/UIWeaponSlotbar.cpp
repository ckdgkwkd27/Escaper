 


#include "UIWeaponSlotbar.h"

void UUIWeaponSlotbar::NativePreConstruct()
{
	Super::NativePreConstruct();

	UI_Icon = Cast<UImage>(GetWidgetFromName(TEXT("UI_Icon")));
	Edge = Cast<UImage>(GetWidgetFromName(TEXT("Edge")));
	MaxBulletCnt = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxBulletCnt")));
	Selection = Cast<UImage>(GetWidgetFromName(TEXT("Selection")));
	Rarity = Cast<UImage>(GetWidgetFromName(TEXT("Rarity")));
	progressTimer = Cast<UProgressBar>(GetWidgetFromName(TEXT("progressTimer")));
}

void UUIWeaponSlotbar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUIWeaponSlotbar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

