 

#pragma once

#include "GameInfo.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieAIController();
	void SetTarget(UObject* pTarget);
	ACharacter* GetTarget() const;

protected:
	UPROPERTY()
	UBehaviorTree*    m_BTAsset;

	UPROPERTY()
	UBlackboardData*  m_BBAsset;

	UPROPERTY()
	ACharacter* m_pTarget;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
};
