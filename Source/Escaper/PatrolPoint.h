 

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "PatrolPoint.generated.h"

UCLASS()
class ESCAPER_API APatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
