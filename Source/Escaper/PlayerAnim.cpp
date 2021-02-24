 


#include "PlayerAnim.h"
#include "UserPlayer.h"

UPlayerAnim::UPlayerAnim()
{
	Dir = (uint8)EDir::Front;

	MoveStop = true;
}

void UPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SetEquipped(false);
	*BaseAnimType = (uint8)EPlayerAnim::Idle;

	playerController = GetWorld()->GetFirstPlayerController();
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* pOwner = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		if (!pOwner->GetAnimationStatus())
			return;

		// Movement 얻어온다.
		UCharacterMovementComponent* pMovement =
			pOwner->GetCharacterMovement();

		if (IsValid(pMovement))
		{
			IsGround = pMovement->IsMovingOnGround(); 
			// 땅을 밟고 있는지 판단한다.
			if (IsGround)
			{
				// 움직이고 있을때
				if (pMovement->Velocity.Size() > 0.f)
				{
					MoveStop = false;
					*BaseAnimType = (uint8)EPlayerAnim::END;
					*BaseAnimType = (uint8)EPlayerAnim::Run; 
				}

				// 멈췄을때
				else
				{
					MoveStop = true;
					//*BaseAnimType = (uint8)EPlayerAnim::Idle;
				}
			}
		}
	}
}

void UPlayerAnim::AnimNotify_MoveStop()
{
	APlayerCharacter* pOwner = Cast<APlayerCharacter>(TryGetPawnOwner());
	if(pOwner->GetCharacterMovement()->Velocity.Size() == 0.f)
		*BaseAnimType = (uint8)EPlayerAnim::Idle;
}

void UPlayerAnim::AnimNotify_AttackEnd()
{
	AUserPlayer* pOwner = Cast<AUserPlayer>(TryGetPawnOwner());
	if (!IsValid(pOwner))
		return;
}

void UPlayerAnim::AnimNotify_InIdle()
{
	AttackEnable = true;
}


void UPlayerAnim::AnimNotify_ReturnIdle()
{
	*BaseAnimType = (uint8)EPlayerAnim::Idle;
}

void UPlayerAnim::AnimNotify_PlayerStart()
{
	APlayerCharacter* pOwner = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pOwner))
		pOwner->StartAnimation();
}

void UPlayerAnim::AnimNotify_ReloadEnd()
{
	AUserPlayer* userPlayer = Cast<AUserPlayer>(TryGetPawnOwner());
	userPlayer->ReloadBullet();

	*BaseAnimType = (uint8)EPlayerAnim::Idle;
}

void UPlayerAnim::AnimNotify_PlayerDied()
{
	if (IsValid(playerController))
		playerController = nullptr;
}

void UPlayerAnim::AnimNotify_IsStop()
{
	if (MoveStop) {
		*BaseAnimType = (uint8)EPlayerAnim::Run_Stop;
	}

}

void UPlayerAnim::NormalAttack()
{
	*BaseAnimType = (uint8)EPlayerAnim::Attack;

}

void UPlayerAnim::Jump()
{
	*BaseAnimType = (uint8)EPlayerAnim::Jump;

}

void UPlayerAnim::Reload()
{
	*BaseAnimType = (uint8)EPlayerAnim::Reloading;
}

void UPlayerAnim::ChangeAnim(EPlayerAnim anim)
{
	*BaseAnimType = (uint8)anim;

	if (anim == EPlayerAnim::Death) {
		AUserPlayer* userPlayer = Cast<AUserPlayer>(TryGetPawnOwner());
		USoundBase *SoundAsset = LoadObject<USoundBase>(nullptr, 
			TEXT("SoundWave'/Game/ParagonLtBelica/Audio/Wavs/LtBelica_Effort_Death_010.LtBelica_Effort_Death_010'"));
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAsset, userPlayer->GetActorLocation());
		
		userPlayer->EndAnimation();
	}
}
