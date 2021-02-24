 


#include "BulletDecal.h"

// Sets default values
ABulletDecal::ABulletDecal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	
	SetRootComponent(Root);

	Decal->SetupAttachment(Root);
	Decal->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void ABulletDecal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

