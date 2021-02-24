 


#include "BTTask_TargetMove.h"
#include "Zombie.h"
#include "ZombieAIController.h"
#include "GameInfo.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_TargetMove::UBTTask_TargetMove() {
	NodeName = TEXT("TargetMove");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_TargetMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type	eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	AZombieAIController* pController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(pController))
		return EBTNodeResult::Failed;

	AZombie* pZombie = Cast<AZombie>(pController->GetPawn());
	if (!IsValid(pZombie)) 
		return EBTNodeResult::Failed;

	ACharacter* pTarget = pController->GetTarget();
	if (!IsValid(pTarget)) 
		return EBTNodeResult::Failed;


	return EBTNodeResult::InProgress;
}

void UBTTask_TargetMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AZombieAIController* pController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());

	AZombie* pZombie = Cast<AZombie>(pController->GetPawn());

	ACharacter* pTarget = pController->GetTarget();

	if (!pTarget)
	{
		pController->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 몬스터가 사망시 이동을 멈추도록 한다.

	// 몬스터가 살아있다면 이동을 시작한다.
	UAIBlueprintHelperLibrary::SimpleMoveToActor(pController, pTarget);

	FVector	vAILoc = pZombie->GetActorLocation();
	FVector	vTargetLoc = pTarget->GetActorLocation();

	vAILoc.Z = 0.f;
	vTargetLoc.Z = 0.f;

	// 거리를 구한다.
	float	fDist = FVector::Distance(vAILoc, vTargetLoc);

	//// 트레이스 거리 밖으로 나가면 스탑
	//if (fDist > pZombie->GetTraceRange())
	//{
	//	pController->StopMovement();
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	//	return;
	//}

	//공격거리 안에 들어오면 스톱
	if (fDist <= pZombie->GetAttackDistance())
	{
		pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}
