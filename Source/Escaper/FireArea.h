 

#pragma once

#include "GameInfo.h"
#include "UserPlayer.h"
#include "GameFramework/Actor.h"
#include "FireArea.generated.h"

UCLASS()
class ESCAPER_API AFireArea : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UBoxComponent * Box;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UParticleSystemComponent * Fire;

	UPROPERTY()
	float DamageTime = 0.f;

	UPROPERTY()
	float DamageTimeMax = 0.1f;

	UPROPERTY()
	AUserPlayer* userPlayer;

	UPROPERTY()
	bool bInside;

private:
	UFUNCTION()
	void StepOnFire(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OutOfFire(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Sets default values for this actor's properties
	AFireArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
