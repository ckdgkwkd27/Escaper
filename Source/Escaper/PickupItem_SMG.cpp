 


#include "PickupItem_SMG.h"

APickupItem_SMG::APickupItem_SMG() : APickupItem() {
	Type = ItemType::WEAPON;

	//Weapon TSubclassOf 정보 주입
	static ConstructorHelpers::FClassFinder<AWeapon> WeaponAsset(TEXT("Blueprint'/Game/Weapons/Weapon/BPWeaponSMG.BPWeaponSMG_C'"));

	if (WeaponAsset.Succeeded())
		WeaponClass = WeaponAsset.Class;

	weapon = WeaponClass->GetDefaultObject<AWeapon>();
}