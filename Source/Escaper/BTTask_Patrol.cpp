 


#include "BTTask_Patrol.h"
#include "Zombie.h"
#include "ZombieAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_Patrol::UBTTask_Patrol() {
	NodeName = TEXT("Patrol");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp,NodeMemory);
	return EBTNodeResult::InProgress;
}

//TickTask�� ��ü
void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AZombieAIController* pController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());

	AZombie* pZombie = Cast<AZombie>(pController->GetPawn());

	// ���Ͱ� ����� �̵��� ���ߵ��� �Ѵ�.

	// ���Ͱ� ����ִٸ� �̵��� �����Ѵ�.
	FVector	vMonsterLoc = pZombie->GetActorLocation();
	FVector	vPatrolPointLoc = pZombie->GetPatrolPoint()->GetActorLocation();
	vPatrolPointLoc.Z = vMonsterLoc.Z;

	pController->MoveToActor(pZombie->GetPatrolPoint(), -1.f, false, true);

	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, vPatrolPointLoc); 

	vMonsterLoc.Z = 0.f;
	vPatrolPointLoc.Z = 0.f;

	float	fDist = FVector::Distance(vMonsterLoc, vPatrolPointLoc);

	if (fDist <= 5.f)
	{
		pZombie->ChangeAnim(EZombieAnim::Idle);
		pController->StopMovement();
		pZombie->NextPatrolPoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
