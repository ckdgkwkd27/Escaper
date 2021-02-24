 

#pragma once

#include "GameInfo.h"
#include "PatrolPoint.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class ESCAPER_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AZombie> SpawnType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float SpawnTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool bInfinity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<class APatrolPoint*> PatrolPointArray;

	UPROPERTY()
	float SpawnDuration;

	UPROPERTY()
	bool bSpawnEnable;

	UPROPERTY()
	class AZombie* SpawnZombie;

	float regenTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Respawn();
};
