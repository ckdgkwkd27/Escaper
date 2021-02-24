 


#include "Weapon_Pistol.h"
#include "EscaperGameInstance.h"

AWeapon_Pistol::AWeapon_Pistol() : AWeapon() {
	ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Weapons/Weapon/GSA_pistolRigged.GSA_pistolRigged'"));
	Title = FText::FromString("Pistol");
	RarityAndCategory = FText::FromString("Normal | Weapon");
	Description = FText::FromString("Basic Pistol");
	SetWeaponName(TEXT("Pistol"));
	SetIconPath(TEXT("Texture2D'/Game/FlatWeaponIcons/Textures/Tex_FlatWeaponIcons_97.Tex_FlatWeaponIcons_97'"));
	SetRarityColor(FLinearColor::White);

	// fire bullet  관련 설정.
	static ConstructorHelpers::FClassFinder<ABullet> BulletAsset(TEXT("Blueprint'/Game/Weapons/Ammunition/BPBulletPistol.BPBulletPistol_C'"));

	if (BulletAsset.Succeeded())
		BulletClass = BulletAsset.Class;

	bullet_cnt = 10;
	Max_bullet_cnt = 70;
	SetBulletWhole(10, 70);
	RateOfFire = 60.f;
}

void AWeapon_Pistol::BeginPlay() {
	Super::BeginPlay();

	int32 LoadedBullet = gameInstance->PistolBulletCnt;
	int32 FullBullet = gameInstance->PistolMaxBulletCnt;

	if ((LoadedBullet != -1) && (FullBullet != -1)) {
		SetBullet(LoadedBullet, FullBullet);
	}
}

void AWeapon_Pistol::LaunchBullet() {
	Super::LaunchBullet();
	gameInstance->PistolBulletCnt = bullet_cnt;
	gameInstance->PistolMaxBulletCnt = Max_bullet_cnt;
}

void AWeapon_Pistol::SetBullet(int32 bulletCnt, int32 maxbulletCnt)
{
	Super::SetBullet(bulletCnt, maxbulletCnt);
	gameInstance->PistolBulletCnt = bulletCnt;
	gameInstance->PistolMaxBulletCnt = maxbulletCnt;
}
