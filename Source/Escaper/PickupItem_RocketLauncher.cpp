 


#include "PickupItem_RocketLauncher.h"

APickupItem_RocketLauncher::APickupItem_RocketLauncher() : APickupItem() {
	Type = ItemType::WEAPON;

	//Weapon TSubclassOf 정보 주입
	static ConstructorHelpers::FClassFinder<AWeapon> WeaponAsset(TEXT("Blueprint'/Game/Weapons/Weapon/BPWeaponRocket.BPWeaponRocket_C'"));

	if (WeaponAsset.Succeeded())
		WeaponClass = WeaponAsset.Class;

	weapon = WeaponClass->GetDefaultObject<AWeapon>();
}