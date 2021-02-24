 


#include "ZombieAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


AZombieAIController::AZombieAIController() {
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset(TEXT("BehaviorTree'/Game/Monster/BTZombie.BTZombie'"));
	if (BTAsset.Succeeded())
		m_BTAsset = BTAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAsset(TEXT("BlackboardData'/Game/Monster/BBZombie.BBZombie'"));
	if (BBAsset.Succeeded())
		m_BBAsset = BBAsset.Object;

	m_pTarget = nullptr;
}

void AZombieAIController::SetTarget(UObject* pTarget)
{
	Blackboard->SetValueAsObject(TEXT("Target"), pTarget);

	if (pTarget)
		m_pTarget = Cast<ACharacter>(pTarget);
	else
		m_pTarget = nullptr;
}

ACharacter* AZombieAIController::GetTarget() const
{
	return m_pTarget;
}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(m_BBAsset, Blackboard)) {
		if (!RunBehaviorTree(m_BTAsset)) {

		}
	}
}

void AZombieAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
