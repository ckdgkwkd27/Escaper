 

#pragma once

#include "GameInfo.h"
#include "EscaperGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UIPassword.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API UUIPassword : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void ButtonClicked0();

	UFUNCTION()
	void ButtonClicked1();

	UFUNCTION()
	void ButtonClicked2();

	UFUNCTION()
	void ButtonClicked3();

	UFUNCTION()
	void ButtonClicked4();

	UFUNCTION()
	void ButtonClicked5();

	UFUNCTION()
	void ButtonClicked6();

	UFUNCTION()
	void ButtonClicked7();

	UFUNCTION()
	void ButtonClicked8();

	UFUNCTION()
	void ButtonClicked9();

	UFUNCTION()
	void ButtonClickedClear();

	UFUNCTION()
	void ButtonClickedEnter();


private:
	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button0;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button1;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button2;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button3;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button4;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button5;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button6;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button7;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button8;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button9;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonEnter;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonClear;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* PwdText;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString password;

	UEscaperGameInstance* gameInstance;
	bool bShowMessage;
	float fShowMsgTime;
	float fShowMsgTimeMax;
};
