 

#pragma once

#include "GameInfo.h"
#include "Weapon.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"
#include "UIWeaponSlotbar.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API UUIWeaponSlotbar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* UI_Icon;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* Edge;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* MaxBulletCnt;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* Selection;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* Rarity;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UProgressBar* progressTimer;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AWeapon* Weapon;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(Category = SlotBar, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 key;

public:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void SetKey(int32 k) {
		key = k;
	}

	int32 GetKey() {
		return key;
	}

	void SetIconFromName(const FString& path) {
		UTexture2D* IconTex = LoadObject<UTexture2D>(NULL, *path, NULL, LOAD_None, NULL);
		if (!IsValid(IconTex)) {
			UE_LOG(LogTemp, Warning, TEXT("Wrong Icon"));
			return;
		}
		else
			UI_Icon->SetBrushFromTexture(IconTex);
	}

	void SetMaxBulletCnt(int32 bullet) {
		MaxBulletCnt->SetText(FText::FromString(FString::FromInt(bullet)));
	}

	void SetSelectionFromPath(const FString& path) {
		UTexture2D* SelectionTex = LoadObject<UTexture2D>(nullptr, *path);
		if(IsValid(SelectionTex))
			Selection->SetBrushFromTexture(SelectionTex);
	}

	void SetRarityFromPath(const FString& path) {
		UTexture2D* RarityTex = LoadObject<UTexture2D>(nullptr, *path);
		if(IsValid(RarityTex))
			Rarity->SetBrushFromTexture(RarityTex);
	}

	void SetEdgeFromPath(const FString& path) {
		UTexture2D* EdgeTex = LoadObject<UTexture2D>(nullptr, *path);
		if(IsValid(EdgeTex))
			Edge->SetBrushFromTexture(EdgeTex);
	}

	void SetWeaponInfo(AWeapon* weapon) {
		Weapon = weapon;
	}

	AWeapon* GetWeaponInfo() const {
		return Weapon;
	}

	void SetWeaponClassInfo(TSubclassOf<AWeapon> wc) {
		WeaponClass = wc;
	}

	TSubclassOf<AWeapon> GetWeaponClassInfo() const {
		return WeaponClass;
	}
};
