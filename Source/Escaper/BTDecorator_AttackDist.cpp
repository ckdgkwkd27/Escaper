 


#include "BTDecorator_AttackDist.h"
#include "Zombie.h"
#include "ZombieAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationPath.h"

UBTDecorator_AttackDist::UBTDecorator_AttackDist() {
	NodeName = TEXT("AttackDistance");
}

bool UBTDecorator_AttackDist::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AZombieAIController* pController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(pController))
		return false;

	AZombie* pZombie = Cast<AZombie>(pController->GetPawn());
	if (!IsValid(pZombie))
		return false;

	if (pZombie->IsAttack()) {
		pController->StopMovement();
		return true;
	}

	ACharacter* pTarget = pController->GetTarget();
	if (!IsValid(pTarget))
		return false;

	FVector vAILoc = pZombie->GetActorLocation();
	FVector vTargetLoc = pTarget->GetActorLocation();

	vAILoc.Z = 0.f;
	vTargetLoc.Z = 0.f;

	//거리 계산
	float fDist = FVector::Distance(vAILoc, vTargetLoc);

	if (fDist <= pZombie->GetAttackDistance()) {
		pController->StopMovement();
		return true;
	}

	static bool bTest;
	if (!bTest) {
		bTest = true;
		UNavigationPath* pPath = UAIBlueprintHelperLibrary::GetCurrentPath(pController);

		if (IsValid(pPath)) {
			int32 iCount = pPath->PathPoints.Num();
			UE_LOG(LogTemp, Warning, TEXT("Path Count: %d"), iCount);
			for (int32 i = 0; i < iCount; i++) 
				UE_LOG(LogTemp, Warning, TEXT("Path Point: %s"), *pPath->PathPoints[i].ToString());
		}
	}
	return false;
}

