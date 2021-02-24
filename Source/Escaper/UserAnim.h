 

#pragma once

#include "PlayerAnim.h"
#include "Weapon.h"
#include "Animation/AnimInstance.h"
#include "UserAnim.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EUserAnim : uint8 {
	Idle,
	Run,
	Attack,
	Hit,
	Jump,
	Death,
	WeaponChange,
	Reload
};

UCLASS()
class ESCAPER_API UUserAnim : public UPlayerAnim
{
	GENERATED_BODY()

public:
	UUserAnim();

	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EUserAnim"))
	uint8 AnimType;

private:
	UPROPERTY()
	AWeapon* Weapon;
};