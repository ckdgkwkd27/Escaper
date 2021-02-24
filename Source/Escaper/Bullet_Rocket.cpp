 


#include "Bullet_Rocket.h"
#include "Zombie.h"
#include "NiagaraFunctionLibrary.h"
#include "DrawDebugHelpers.h"

ABullet_Rocket::ABullet_Rocket() : ABullet() {
	Damage = 150.f;

	Box->OnComponentBeginOverlap.RemoveDynamic(this, &ABullet::BulletBeginOverlap);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABullet_Rocket::BulletBeginOverlap);

	Movement->OnProjectileStop.RemoveDynamic(this, &ABullet::MovementStopped);
	Movement->OnProjectileStop.AddDynamic(this, &ABullet_Rocket::MovementStopped);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EffectAsset(TEXT("NiagaraSystem'/Game/sA_ParticleFx_01/Fx/NS_Explosion_4.NS_Explosion_4'"));
	if (EffectAsset.Succeeded())
		nExplode = EffectAsset.Object;
}


void ABullet_Rocket::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet_Rocket::BulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BulletBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	TArray<FHitResult> HitActors;

	FVector startTrace = GetActorLocation();
	FVector endTrace = startTrace;
	endTrace.Z -= 300.f;

	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Box;
	CollisionShape.SetBox(FVector(500.f));


	if (GetWorld()->SweepMultiByChannel(HitActors, startTrace, endTrace, FQuat::FQuat(), ECC_WorldStatic, CollisionShape)) {
		for (auto Actors = HitActors.CreateIterator(); Actors; Actors++) {
			AZombie* zombie = Cast<AZombie>((*Actors).GetActor());
			FDamageEvent DamageEvent;

			if (zombie) {
				zombie->TakeDamage(150.f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
			}
		}
	}

	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Weapons/Effect/rocket.rocket'"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAsset, GetActorLocation());

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), nExplode, GetActorLocation());
	
	Destroy();
}

void ABullet_Rocket::BulletEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<FHitResult> HitActors;

	FVector startTrace = GetActorLocation();
	FVector endTrace = startTrace;
	endTrace.Z += 300.f;

	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Box;
	CollisionShape.SetBox(FVector(300.f));


	if (GetWorld()->SweepMultiByChannel(HitActors, startTrace, endTrace, FQuat::FQuat(), ECC_WorldStatic, CollisionShape)) {
		for (auto Actors = HitActors.CreateIterator(); Actors; Actors++) {
			AZombie* zombie = Cast<AZombie>((*Actors).GetActor());
			FDamageEvent DamageEvent;

			if (zombie) {
				zombie->TakeDamage(150.f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
			}
		}
	}

	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Weapons/Effect/rocket.rocket'"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAsset, GetActorLocation());

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), nExplode, GetActorLocation());

	Destroy();
}



void ABullet_Rocket::MovementStopped(const FHitResult& ImpactResult)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	bulletDecal = GetWorld()->SpawnActor<ABulletDecal>(DecalClass, ImpactResult.ImpactPoint, GetActorRotation(), params);
	bulletDecal->SetActorScale3D(FVector(3.f));

	TArray<FHitResult> HitActors;

	FVector startTrace = GetActorLocation();
	FVector endTrace = startTrace;
	//endTrace.Z += 300.f;

	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Box;
	CollisionShape.SetBox(FVector(500.f));

	if (GetWorld()->SweepMultiByChannel(HitActors, startTrace, endTrace, FQuat::FQuat(), ECC_WorldStatic, CollisionShape)) {
		for (auto Actors = HitActors.CreateIterator(); Actors; Actors++) {
			AZombie* zombie = Cast<AZombie>((*Actors).GetActor());
			FDamageEvent DamageEvent;

			if (zombie) {
				zombie->TakeDamage(150.f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
			}
		}
	}
	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Weapons/Effect/rocket.rocket'"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAsset, GetActorLocation());

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), nExplode, GetActorLocation());

	Destroy();
}


