 

#include "Weapon.h"
#include "UserPlayer.h" 
#include "EscaperGameInstance.h"
#include "UIPlayerHUD.h"


AWeapon::AWeapon() {
	//PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Scene);
	Mesh->SetupAttachment(Scene);

	//SetBullet(30, 180);

	// Muzzle 관련 설정.
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EffectAsset(TEXT("NiagaraSystem'/Game/sA_ShootingVfxPack/FX/NiagaraSystems/NS_AR_Muzzleflash_1_ONCE.NS_AR_Muzzleflash_1_ONCE'"));

	if (EffectAsset.Succeeded())
		Effect = EffectAsset.Object;

	RateOfFire = 0.f;
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShots = 60 / RateOfFire;

	gameInstance = Cast<UEscaperGameInstance>(GetGameInstance());
}

void AWeapon::LoadMesh(const FString& strPath)
{
	USkeletalMesh* mesh = LoadObject<USkeletalMesh>(nullptr, *strPath);

	if (IsValid(mesh)) {
		Mesh->SetSkeletalMesh(mesh);
	}
}

void AWeapon::LaunchBullet()
{
	if (bullet_cnt <= 0)
		return;

	FActorSpawnParameters tParams;
	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector Loc;
	FRotator Rot;
	player->GetActorEyesViewPoint(Loc, Rot);

	Rot.Pitch -= 7.f;

	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, Loc, Rot, tParams);
	bullet_cnt--;

	GameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMode))
		playerHUD = GameMode->GetPlayerHUD();

	playerHUD->SetBullet(bullet_cnt, Max_bullet_cnt);
	Rot.Pitch += 7.f;

}

void AWeapon::SetBullet(int32 bulletCnt, int32 maxbulletCnt)
{
	bullet_cnt = bulletCnt;
	Max_bullet_cnt = maxbulletCnt;
}

int32 AWeapon::GetBullet()
{
	return bullet_cnt;
}

void AWeapon::SetBulletWhole(int32 bullet, int32 maxbullet)
{
	bulletCntWhole = bullet;
	MaxbulletCntWhole = maxbullet;
}

void AWeapon::SetMaxBulletWhole(int32 bullet)
{
	MaxbulletCntWhole = bullet;
}

int32 AWeapon::GetBulletWhole() const
{
	return bulletCntWhole;
}

int32 AWeapon::GetMaxBulletWhole() const
{
	return MaxbulletCntWhole;
}

int32 AWeapon::GetMaxBullet()
{
	return Max_bullet_cnt;
}

void AWeapon::StartFire(AUserPlayer* userPlayer, FVector v, FRotator r)
{
	player = userPlayer;

	float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.f);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWeapon::LaunchBullet, TimeBetweenShots, true, FirstDelay);
}

void AWeapon::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}
