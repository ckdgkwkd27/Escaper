 


#include "BTTask_Attack.h"
#include "Zombie.h"
#include "ZombieAIController.h"

UBTTask_Attack::UBTTask_Attack() {
	NodeName = TEXT("Attack");
	bNotifyTick = true;
	bAttack = false;
}

void UBTTask_Attack::AttackEnd()
{
	bAttack = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type	eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	AZombieAIController* pController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return EBTNodeResult::Failed;

	AZombie* pZombie = Cast<AZombie>(pController->GetPawn());

	if (!IsValid(pZombie))
		return EBTNodeResult::Failed;

	pZombie->AddAttackEndDelegate<UBTTask_Attack>(this,
		&UBTTask_Attack::AttackEnd);

	// ���Ͱ� ����������� ������ �����Ѵ�.
	pZombie->ChangeAnim(EZombieAnim::Attack);

	bAttack = true;

	pZombie->Attack();

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	if (FVector::Distance(pTarget->GetActorLocation(), pZombie->GetActorLocation())
		> pZombie->GetTraceRange()) {
		pController->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	// Ÿ���� �ٶ󺸵��� ȸ����Ų��.
	FVector	vDir = pTarget->GetActorLocation() - pZombie->GetActorLocation();
	vDir.Normalize();

	pZombie->SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

	// ������ ������ ��� �����Ų��.
	if (!bAttack)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
