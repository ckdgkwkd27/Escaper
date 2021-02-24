 


#include "Weapon_SMG.h"
#include "EscaperGameInstance.h"

AWeapon_SMG::AWeapon_SMG() : AWeapon() {
	ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Weapons/Weapon/SK_SMG11_X.SK_SMG11_X'"));
	Title = FText::FromString("SMG");
	RarityAndCategory = FText::FromString("Uncommon | Weapon");
	Description = FText::FromString("Uncommon Submachine Gun");
	SetWeaponName(TEXT("SMG"));
	SetIconPath(TEXT("Texture2D'/Game/FlatWeaponIcons/Textures/Tex_L_FlatWeaponIcons_42.Tex_L_FlatWeaponIcons_42'"));
	SetRarityColor(FLinearColor::FLinearColor(0.f, 1.f, 0.f, 1.f));

	// fire bullet  관련 설정.
	static ConstructorHelpers::FClassFinder<ABullet> BulletAsset(TEXT("Blueprint'/Game/Weapons/Ammunition/BPBulletSMG.BPBulletSMG_C'"));

	if (BulletAsset.Succeeded())
		BulletClass = BulletAsset.Class;

	bullet_cnt = 50;
	Max_bullet_cnt = 250;
	SetBulletWhole(50, 250);
	RateOfFire = 600.f;
}

void AWeapon_SMG::BeginPlay() {
	Super::BeginPlay();

	//update from game instance
	int32 LoadedBullet = gameInstance->SMGBulletCnt;
	int32 FullBullet = gameInstance->SMGMaxBulletCnt;

	if ((LoadedBullet != -1) && (FullBullet != -1)) {
		SetBullet(LoadedBullet, FullBullet);
	}
}

void AWeapon_SMG::LaunchBullet() {
	Super::LaunchBullet();
	gameInstance->SMGBulletCnt = bullet_cnt;
	gameInstance->SMGMaxBulletCnt = Max_bullet_cnt;
}

void AWeapon_SMG::SetBullet(int32 bulletCnt, int32 maxbulletCnt)
{
	Super::SetBullet(bulletCnt, maxbulletCnt);
	gameInstance->SMGBulletCnt = bulletCnt;
	gameInstance->SMGMaxBulletCnt = maxbulletCnt;
}
