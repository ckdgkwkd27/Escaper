 

#pragma once

#include "GameInfo.h"
#include "Animation/AnimInstance.h"
#include "ZombieAnim.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EZombieAnim : uint8 {
	Idle,
	Run,
	Attack,
	Death
};

UCLASS()
class ESCAPER_API UZombieAnim : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EZombieAnim"))
	uint8	AnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	MoveStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	IsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	IsGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	AttackEnable;
	

public:
	UZombieAnim();
	void ChangeAnim(EZombieAnim eAnim);
	FString GetAnimString();
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	uint8 GetAnimType() const {
		return AnimType;
	}

	UFUNCTION()
	void AnimNotify_ChaseEnd();

	UFUNCTION()
	void  AnimNotify_AttackEnd();

	UFUNCTION()
	void  AnimNotify_DeathEnd();

	UFUNCTION()
	void  AnimNotify_Damage();

	UFUNCTION()
	void AnimNotify_IsDied();
};
