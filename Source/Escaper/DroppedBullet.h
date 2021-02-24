 

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "DroppedBullet.generated.h"

UCLASS()
class ESCAPER_API ADroppedBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADroppedBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapStart(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);


private:
	UPROPERTY(EditAnywhere, meta = (AllowPriavateAccess = "true"))
	USphereComponent* sph;

	UPROPERTY(EditAnywhere, meta = (AllowPriavateAccess = "true"))
	UStaticMeshComponent* Mesh1;

	UPROPERTY(EditAnywhere, meta = (AllowPriavateAccess = "true"))
	UStaticMeshComponent* Mesh2;
};
