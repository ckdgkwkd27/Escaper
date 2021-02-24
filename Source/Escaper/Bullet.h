 

#pragma once

#include "GameInfo.h"
#include "BulletDecal.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class ESCAPER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UFUNCTION(BlueprintCallable)
	void EndStart();
	
	UFUNCTION()
	virtual void BulletBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void MovementStopped(const FHitResult& ImpactResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(Category = Particle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* Particle;

	UPROPERTY(Category = ProjectTile, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* Movement;

	UPROPERTY(Category = Projectile, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bProjectTileEnd;

	UPROPERTY(Category = Box, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;
	
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Damage;

	UPROPERTY()
	TSubclassOf<ABulletDecal> DecalClass;

	UPROPERTY()
	ABulletDecal* bulletDecal;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDamage(float dmg) {
		Damage = dmg;
	}
};
