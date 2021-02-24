 

#pragma once

#include "GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Detect();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
