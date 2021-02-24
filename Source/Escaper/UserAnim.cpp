 


#include "UserAnim.h"
#include "UserPlayer.h"

UUserAnim::UUserAnim() {
	BaseAnimType = &AnimType;
}

void UUserAnim::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
}

void UUserAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	AUserPlayer* pOwner = Cast<AUserPlayer>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		UCharacterMovementComponent* pMovement =
			pOwner->GetCharacterMovement();
		
		if (IsValid(pMovement))
		{
		}
	}
}
