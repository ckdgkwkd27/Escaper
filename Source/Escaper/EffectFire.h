 

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "EffectFire.generated.h"

UCLASS()
class ESCAPER_API AEffectFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* Particle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetEffectPath(const FString& strPath, const FString& strSoundPath);
	void SetEffect(UParticleSystem* ParticleAsset, USoundBase* SoundAsset);

	UFUNCTION()
	void Finish(UParticleSystemComponent* Com);
};
