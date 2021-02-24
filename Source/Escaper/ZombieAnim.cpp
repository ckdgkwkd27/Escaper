 


#include "ZombieAnim.h"
#include "Zombie.h"
#include "ZombieAIController.h"

UZombieAnim::UZombieAnim() {
	MoveStop = true;
	AttackEnable = true;
	IsGround = true;
	IsDead = false;

	AnimType = (uint8)EZombieAnim::Idle;
}

void UZombieAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UZombieAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AZombie* pOwner = Cast<AZombie>(TryGetPawnOwner());

	if (!IsValid(pOwner))
		return;

	if (IsDead) {
		AnimType = (uint8)EZombieAnim::Death;
	}

	else
	{
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

					AnimType = (uint8)EZombieAnim::Run;

				}

				// 멈췄을때
				else
				{
					MoveStop = true;
				}
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("pMovement Not Valid"));
		}
	}
}

void UZombieAnim::AnimNotify_ChaseEnd()
{

}

void UZombieAnim::ChangeAnim(EZombieAnim eAnim) {
	AnimType = (uint8)eAnim;
	AZombie* pOwner = Cast<AZombie>(TryGetPawnOwner());

	if (AnimType == (uint8)EZombieAnim::Death) {
		IsDead = true;
	}
}

FString UZombieAnim::GetAnimString() {
	FString animstring = TEXT("");

	switch (AnimType) {
	case (uint8)EZombieAnim::Idle:
		animstring = TEXT("IDLE!");
		break;
	case (uint8)EZombieAnim::Run:
		animstring = TEXT("RUN!");
		break;
	case (uint8)EZombieAnim::Attack:
		animstring = TEXT("ATTACK!");
		break;
	case (uint8)EZombieAnim::Death:
		animstring = TEXT("DEATH!");
		break;
	}

	return animstring;
}

void UZombieAnim::AnimNotify_AttackEnd()
{
	AZombie* pOwner = Cast<AZombie>(TryGetPawnOwner());

	if (IsValid(pOwner))
		pOwner->AttackEnd();
}

void UZombieAnim::AnimNotify_DeathEnd()
{
	AZombie* pOwner = Cast<AZombie>(TryGetPawnOwner());

	if (IsValid(pOwner))
		pOwner->Death();
}

void UZombieAnim::AnimNotify_Damage()
{
	AZombie* pOwner = Cast<AZombie>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		AZombieAIController* AI = pOwner->GetController<AZombieAIController>();

		if (IsValid(AI))
		{
			ACharacter* Target = AI->GetTarget();

			FDamageEvent	DamageEvent;
			Target->TakeDamage(pOwner->GetAttackPoint(), DamageEvent,
				AI, pOwner);
		}
	}
}

void UZombieAnim::AnimNotify_IsDied() {

}