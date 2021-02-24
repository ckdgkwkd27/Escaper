 


#include "DroppedBullet.h"
#include "UserPlayer.h"
#include "Weapon_Pistol.h"
#include "Weapon_AR.h"
#include "Weapon_SMG.h"
#include "Weapon_RocketLauncher.h"

// Sets default values
ADroppedBullet::ADroppedBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sph = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));

	SetRootComponent(sph);
	Mesh1->SetupAttachment(sph);
	Mesh2->SetupAttachment(sph);

	Mesh1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADroppedBullet::BeginPlay()
{
	Super::BeginPlay();
	
	sph->OnComponentBeginOverlap.AddDynamic(this, &ADroppedBullet::OverlapStart);
}

// Called every frame
void ADroppedBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADroppedBullet::OverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
		return;

	AUserPlayer* userPlayer = Cast<AUserPlayer>(OtherActor);
	UUIPlayerHUD* playerHUD = userPlayer->GetPlayerHUD();

	if (!IsValid(playerHUD))
		return;

	for (int32 i = 0; i < 4; i++) {
		AWeapon* weapon = playerHUD->GetSlotInfo(i);

		if (IsValid(weapon)) {
			int32 bulletcnt = weapon->GetBullet();
			int32 maxbulletcnt = weapon->GetMaxBullet();

			//피스톨
			if(weapon->IsA<AWeapon_Pistol>())
				weapon->SetBullet(bulletcnt, maxbulletcnt + 20);
			//AR
			else if (weapon->IsA<AWeapon_AR>())
				weapon->SetBullet(bulletcnt, maxbulletcnt + 50);
			//SMG
			else if (weapon->IsA<AWeapon_SMG>())
				weapon->SetBullet(bulletcnt, maxbulletcnt + 100);
			//로켓런처
			else if (weapon->IsA<AWeapon_RocketLauncher>())
				weapon->SetBullet(bulletcnt, maxbulletcnt + 1);
		}
	}

	AWeapon* weapon = userPlayer->GetWeapon();
	if (IsValid(weapon)) {
		int32 bulletcnt = weapon->GetBullet();
		int32 maxbulletcnt = weapon->GetMaxBullet();
		playerHUD->SetBullet(bulletcnt, maxbulletcnt);
	}
	
	Destroy();
}

