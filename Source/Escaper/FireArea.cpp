 


#include "FireArea.h"

// Sets default values
AFireArea::AFireArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bInside = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));

	SetRootComponent(Box);
	Fire->SetupAttachment(Box);

}

// Called when the game starts or when spawned
void AFireArea::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AFireArea::StepOnFire);
	Box->OnComponentEndOverlap.AddDynamic(this, &AFireArea::OutOfFire);
}

// Called every frame
void AFireArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInside) {
		if (DamageTime >= DamageTimeMax) {
			DamageTime = 0.f;

			FDamageEvent DamageEvent;
			userPlayer->TakeDamage(50.f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
			userPlayer->SetHealth(userPlayer->GetHealth());

			if (userPlayer->GetHealth() <= 0) 
				userPlayer->ChangeAnim(EPlayerAnim::Death); 
				
		}
		else
			DamageTime += DeltaTime;
	}
}

void AFireArea::StepOnFire(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) {
		UE_LOG(LogTemp, Warning, TEXT("OtherActor == NULL"));
		return;
	}

	userPlayer = Cast<AUserPlayer>(OtherActor);
	bInside = true;
}

void AFireArea::OutOfFire(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bInside = false;
}

