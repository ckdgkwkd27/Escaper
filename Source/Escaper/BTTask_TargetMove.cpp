 


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

	// ���Ͱ� ����� �̵��� ���ߵ��� �Ѵ�.

	// ���Ͱ� ����ִٸ� �̵��� �����Ѵ�.
	UAIBlueprintHelperLibrary::SimpleMoveToActor(pController, pTarget);

	FVector	vAILoc = pZombie->GetActorLocation();
	FVector	vTargetLoc = pTarget->GetActorLocation();

	vAILoc.Z = 0.f;
	vTargetLoc.Z = 0.f;

	// �Ÿ��� ���Ѵ�.
	float	fDist = FVector::Distance(vAILoc, vTargetLoc);

	//// Ʈ���̽� �Ÿ� ������ ������ ��ž
	//if (fDist > pZombie->GetTraceRange())
	//{
	//	pController->StopMovement();
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	//	return;
	//}

	//���ݰŸ� �ȿ� ������ ����
	if (fDist <= pZombie->GetAttackDistance())
	{
		pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}
