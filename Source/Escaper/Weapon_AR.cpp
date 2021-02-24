 


#include "Weapon_AR.h"
#include "EscaperGameInstance.h"

AWeapon_AR::AWeapon_AR() : AWeapon() {
	ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Weapons/Weapon/SK_AR4.SK_AR4'"));
	Title = FText::FromString("Assault Rifle");
	RarityAndCategory = FText::FromString("Rare | Weapon");
	Description = FText::FromString("Very Rare Rifle");
	SetWeaponName(TEXT("Assault Rifle"));
	SetIconPath(TEXT("Texture2D'/Game/FlatWeaponIcons/Textures/Tex_FlatWeaponIcons_32.Tex_FlatWeaponIcons_32'"));
	SetRarityColor(FLinearColor::FLinearColor(0.5f, 0.f, 1.f, 1.f));

	// fire bullet  관련 설정.
	static ConstructorHelpers::FClassFinder<ABullet> BulletAsset(TEXT("Blueprint'/Game/Weapons/Ammunition/BPBulletAR.BPBulletAR_C'"));

	if (BulletAsset.Succeeded())
		BulletClass = BulletAsset.Class;

	bullet_cnt = 30;
	Max_bullet_cnt = 180;

	SetBulletWhole(30, 180);
	RateOfFire = 300.f;
}


void AWeapon_AR::BeginPlay() {
	Super::BeginPlay();

	int32 LoadedBullet = gameInstance->ARBulletCnt;
	int32 FullBullet = gameInstance->ARMaxBulletCnt;

	if ((LoadedBullet != -1) && (FullBullet != -1)) {
		SetBullet(LoadedBullet, FullBullet);
	}
}

void AWeapon_AR::LaunchBullet() {
	Super::LaunchBullet();
	gameInstance->ARBulletCnt = bullet_cnt;
	gameInstance->ARMaxBulletCnt = Max_bullet_cnt;
}

void AWeapon_AR::SetBullet(int32 bulletCnt, int32 maxbulletCnt)
{
	Super::SetBullet(bulletCnt, maxbulletCnt);
	gameInstance->ARBulletCnt = bulletCnt;
	gameInstance->ARMaxBulletCnt = maxbulletCnt;
}

