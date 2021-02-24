#include "BTService_Detect.h"
#include "Zombie.h"
#include "ZombieAIController.h"
#include "DrawDebugHelpers.h"


UBTService_Detect::UBTService_Detect() {
	NodeName = TEXT("Detection");
	Interval = 0.5f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AZombieAIController* pController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(pController))
		return;

	AZombie* pZombie = Cast<AZombie>(pController->GetPawn());
	if (!IsValid(pZombie))
		return;

	FCollisionQueryParams params(NAME_None, false, pZombie);
	TArray<FOverlapResult> resultArray;

	float fTraceRange = pZombie->GetTraceRange();

	bool bOverlap = GetWorld()->OverlapMultiByChannel(resultArray,
		pZombie->GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(fTraceRange),
		params); 


	if (bOverlap)
	{
		pController->SetTarget(resultArray[0].GetActor());
	}

	else
	{
		pController->SetTarget(nullptr);
	}
}