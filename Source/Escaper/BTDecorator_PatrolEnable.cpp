 


#include "BTDecorator_PatrolEnable.h"
#include "Zombie.h"
#include "ZombieAIController.h"

UBTDecorator_PatrolEnable::UBTDecorator_PatrolEnable() {
	NodeName = TEXT("PatrolEnable");
}

bool UBTDecorator_PatrolEnable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp,
		NodeMemory);

	AZombieAIController* pController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return false;

	AZombie* pZombie = Cast<AZombie>(pController->GetPawn());

	if (!IsValid(pZombie))
		return false;

	if (pZombie->GetPatrolPointCount() < 2)
		return false;

	return true;
}
