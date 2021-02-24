 


#include "Weapon_RocketLauncher.h"
#include "EscaperGameInstance.h"

AWeapon_RocketLauncher::AWeapon_RocketLauncher() : AWeapon() {
	ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Weapons/Weapon/New_RocketLauncher_SM_RocketLauncher.New_RocketLauncher_SM_RocketLauncher'"));
	Title = FText::FromString("Rocket Launcher");
	RarityAndCategory = FText::FromString("Unique | Weapon");
	Description = FText::FromString("You don't need to be afraid of\n Zombies anymore");
	SetWeaponName(TEXT("Rocket Launcher"));
	SetIconPath(TEXT("Texture2D'/Game/FlatWeaponIcons/Textures/Tex_FlatWeaponIcons_25.Tex_FlatWeaponIcons_25'"));
	SetRarityColor(FLinearColor::FLinearColor(1.f, 1.f, 0.f, 1.f));

	// fire bullet  관련 설정.
	static ConstructorHelpers::FClassFinder<ABullet> BulletAsset(TEXT("Blueprint'/Game/Weapons/Ammunition/BPBulletRocket.BPBulletRocket_C'"));

	if (BulletAsset.Succeeded())
		BulletClass = BulletAsset.Class;

	bullet_cnt = 3;
	Max_bullet_cnt = 0;
	SetBulletWhole(3, 0);
	RateOfFire = 45.f;
}

void AWeapon_RocketLauncher::BeginPlay() {
	Super::BeginPlay();

	int32 LoadedBullet = gameInstance->RocketBulletCnt;
	int32 FullBullet = gameInstance->RocketMaxBulletCnt;

	if ((LoadedBullet != -1) && (FullBullet != -1)) {
		SetBullet(LoadedBullet, FullBullet);
	}
}

void AWeapon_RocketLauncher::LaunchBullet() {
	Super::LaunchBullet();
	gameInstance->RocketBulletCnt = bullet_cnt;
	gameInstance->RocketMaxBulletCnt = Max_bullet_cnt;
}

void AWeapon_RocketLauncher::SetBullet(int32 bulletCnt, int32 maxbulletCnt)
{
	Super::SetBullet(bulletCnt, maxbulletCnt);
	gameInstance->RocketBulletCnt = bulletCnt;
	gameInstance->RocketMaxBulletCnt = maxbulletCnt;
}
