 


#include "EffectFire.h"

// Sets default values
AEffectFire::AEffectFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEffectFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	SetRootComponent(Particle);
}

void AEffectFire::SetEffectPath(const FString& strPath, const FString& strSoundPath)
{
	UParticleSystem* Asset = LoadObject<UParticleSystem>(nullptr, *strPath);

	if (IsValid(Asset))
		Particle->SetTemplate(Asset);

	Particle->OnSystemFinished.AddDynamic(this, &AEffectFire::Finish);

	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, *strSoundPath);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),
		SoundAsset, GetActorLocation());
}

void AEffectFire::SetEffect(UParticleSystem* ParticleAsset, USoundBase* SoundAsset)
{
	Particle->SetTemplate(ParticleAsset);
	Particle->OnSystemFinished.AddDynamic(this, &AEffectFire::Finish);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAsset, GetActorLocation());
}

void AEffectFire::Finish(UParticleSystemComponent* Com)
{
	Destroy();
}

