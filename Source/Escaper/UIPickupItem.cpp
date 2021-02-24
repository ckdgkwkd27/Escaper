 


#include "UIPickupItem.h"

void UUIPickupItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	Canvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Pickup")));
	Icon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	Title = Cast<UTextBlock>(GetWidgetFromName(TEXT("Title")));
	RarityAndCategory = Cast<UTextBlock>(GetWidgetFromName(TEXT("RarityAndCategory")));
	Description = Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")));
	Rarity = Cast<UImage>(GetWidgetFromName(TEXT("Rarity")));
}

void UUIPickupItem::NativeConstruct()
{
	Super::NativeConstruct();

	userController = Cast<AUserController>(GetWorld()->GetFirstPlayerController());

	Canvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Pickup")));
}

void UUIPickupItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUIPickupItem::SetTitle(FText title)
{
	Title->SetText(title);
}

void UUIPickupItem::SetIconImageFromPath(const FString& path)
{
	UTexture2D* IconTex = LoadObject<UTexture2D>(NULL, *path, NULL, LOAD_None, NULL);

	if (IconTex)
		Icon->SetBrushFromTexture(IconTex);
	else
		UE_LOG(LogTemp, Error, TEXT("Pickup: IconTex is NULL"));
}

void UUIPickupItem::SetRarityAndCategory(FText str)
{
	RarityAndCategory->SetText(str);
}

void UUIPickupItem::SetDescription(FText desc)
{
	Description->SetText(desc);
}

void UUIPickupItem::SetRarityColor(FLinearColor color)
{
	Rarity->SetColorAndOpacity(color);
}
