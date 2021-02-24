 


#include "PickupItem_AR.h"

APickupItem_AR::APickupItem_AR() : APickupItem() {
	Type = ItemType::WEAPON;

	//Weapon TSubclassOf 정보 주입
	static ConstructorHelpers::FClassFinder<AWeapon> WeaponAsset(TEXT("Blueprint'/Game/Weapons/Weapon/BPWeaponAR.BPWeaponAR_C'"));

	if (WeaponAsset.Succeeded())
		WeaponClass = WeaponAsset.Class;

	weapon = WeaponClass->GetDefaultObject<AWeapon>();
}