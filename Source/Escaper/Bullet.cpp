

#include "Bullet.h"
#include "Zombie.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	Mesh->SetWorldRotation(FRotator(0.f, -90.f, 0.f));

	Movement->InitialSpeed = 3000.f;
	Movement->MaxSpeed = 3000.f;
	Movement->ProjectileGravityScale = 0.f;
	
	SetRootComponent(Box);

	Mesh->SetupAttachment(Box);
	Particle->SetupAttachment(Mesh);

	Box->SetCollisionProfileName("Bullet");
	Box->SetGenerateOverlapEvents(true);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bProjectTileEnd = false;

	static ConstructorHelpers::FClassFinder<ABulletDecal> DecalAsset(TEXT("Blueprint'/Game/Weapons/Effect/BPBulletDecal.BPBulletDecal_C'"));
	if (DecalAsset.Succeeded())
		DecalClass = DecalAsset.Class;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Weapons/Effect/gunfire.gunfire'"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAsset, GetActorLocation());

	Movement->Velocity = GetActorForwardVector() * 3000.f;

	Box->OnComponentBeginOverlap.AddDynamic(this, &ABullet::BulletBeginOverlap);
	Movement->OnProjectileStop.AddDynamic(this, &ABullet::MovementStopped);
}

void ABullet::EndStart()
{
	bProjectTileEnd = true;
}

void ABullet::BulletBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult& SweepResult)
{	
	FDamageEvent DamageEvent;
	float fDamage = OtherActor->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
	
	FVector vStart = GetActorLocation();
	FVector vEnd = FVector(GetActorLocation().X + 10.f * GetActorScale().Size(), GetActorLocation().Y, GetActorLocation().Z);

	FVector vDir = vEnd - vStart;
	vDir.Normalize();

	FCollisionQueryParams  tColParams(NAME_None, false, this);
	FHitResult hitResult;

	bool bCollision = GetWorld()->SweepSingleByProfile(hitResult, vStart,
		vEnd, FQuat::Identity, TEXT("bullet"),
		FCollisionShape::MakeBox(FVector(32, 5.f, 5.f)),
		tColParams);

	FVector vImpactPoint = FVector::ZeroVector;
	FVector vImpactNormal = FVector::ZeroVector;

	if (hitResult.GetActor() == OtherActor)
	{
		vImpactPoint = hitResult.ImpactPoint;
		vImpactNormal = hitResult.ImpactNormal;
	}

	Destroy();
}

void ABullet::MovementStopped(const FHitResult& ImpactResult)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	bulletDecal = GetWorld()->SpawnActor<ABulletDecal>(DecalClass, ImpactResult.ImpactPoint, GetActorRotation(), params);
	Destroy(); 

}



// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



