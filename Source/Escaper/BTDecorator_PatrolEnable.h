 

#pragma once

#include "GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_PatrolEnable.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API UBTDecorator_PatrolEnable : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_PatrolEnable();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
