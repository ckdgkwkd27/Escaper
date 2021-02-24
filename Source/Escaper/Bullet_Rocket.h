 

#pragma once

#include "GameInfo.h"
#include "Bullet.h"
#include "Bullet_Rocket.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API ABullet_Rocket : public ABullet
{
	GENERATED_BODY()
	
public:
	ABullet_Rocket();
	virtual void BeginPlay();

	virtual void BulletBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	virtual void BulletEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	virtual void MovementStopped(const FHitResult& ImpactResult);

private:
	UNiagaraSystem* nExplode;
};
