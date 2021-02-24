 

#pragma once

#include "GameInfo.h"
#include "UIWeaponSlotbar.h"
#include "Weapon.h"
#include "UIPassword.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UIPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API UUIPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = WeaponSlot, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UUIWeaponSlotbar*> tWeaponSlotArray;

	UPROPERTY(Category = WeaponSlot, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int index;


protected:
	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UVerticalBox* SlotsBar;
	
	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* Bullet_Cnt;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* Max_Bullet_Cnt;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* Crosshairs;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* NotificationText;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* HealthCircle;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* HealthValue;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* UIHorizontal;

	UPROPERTY()
	bool bMsgShowed;;

	UPROPERTY()
	float fMsgTime;

	UPROPERTY()
	float fMsgTimeMax;

	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION(BlueprintCallable)
	void SetBullet(int32 bulletCnt, int32 maxbulletCnt);

	UFUNCTION(BlueprintCallable)
	void SetHealth(int32 hp);

	UFUNCTION(BlueprintCallable)
	void SetNotiText(FText text);

	UFUNCTION(BlueprintCallable)
	void SetNotiVisibility(ESlateVisibility state) {
		NotificationText->SetVisibility(state);
	}

	
public:
	UFUNCTION(BlueprintCallable, Category = "Equip")
	void AddToSlot(AWeapon* weapon);

	UFUNCTION(BlueprintCallable, Category = "Equip")
	AWeapon* GetSlotInfo(int32 i) const;

	UFUNCTION(BlueprintCallable, Category = "Equip")
	TSubclassOf<AWeapon> GetSlotClassInfo(int32 i) const;
};
