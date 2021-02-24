 

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UIEnding.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API UUIEnding : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* ui_Second;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* ui_MenuButton;

	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* ui_ExitButton;

public:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void SetSeconds(float sec);

	UFUNCTION()
	void MainMenu();

	UFUNCTION()
	void Exit();
};
