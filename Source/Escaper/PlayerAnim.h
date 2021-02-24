 

#pragma once

#include "GameInfo.h"
#include "PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */

UENUM(BlueprintType, Meta = (Bitflags))
enum class EPlayerAnim : uint8
{
	Idle,
	Run,
	Run_Stop,
	Attack,
	Jump,
	Reloading,
	Death,
	END
};

UCLASS()
class ESCAPER_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnim();

protected:
	uint8* BaseAnimType;

	UPROPERTY()
	APlayerController* playerController;

	UPROPERTY()
	APlayerCharacter* character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EDir"))
	uint8	Dir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	MoveStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	AttackEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	uint8	NextAttackIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	IsGround;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	IsEquipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool	IsPistol;

public:
	void SetMoveDir(EDir eDir)
	{
		Dir = (uint8)eDir;
	}

	void SetEquipped(bool stat) {
		IsEquipped = stat;
	}

	void SetIsPistol(bool stat) {
		IsPistol = stat;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_MoveStop();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_InIdle();

	UFUNCTION()
	void AnimNotify_ReturnIdle();

	UFUNCTION()
	void AnimNotify_PlayerStart();

	UFUNCTION()
	void AnimNotify_ReloadEnd();

	UFUNCTION()
	void AnimNotify_PlayerDied();

	UFUNCTION()
	void AnimNotify_IsStop();

public:
	void NormalAttack();
	void Jump();
	void Reload();
	void ChangeAnim(EPlayerAnim anim);
};
