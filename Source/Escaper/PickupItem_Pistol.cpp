 


#include "PickupItem_Pistol.h"

APickupItem_Pistol::APickupItem_Pistol() : APickupItem() {
	Type = ItemType::WEAPON;

	//Weapon TSubclassOf 정보 주입
	static ConstructorHelpers::FClassFinder<AWeapon> WeaponAsset(TEXT("Blueprint'/Game/Weapons/Weapon/BPWeaponPistol.BPWeaponPistol_C'"));

	if (WeaponAsset.Succeeded())
		WeaponClass = WeaponAsset.Class;

	weapon = WeaponClass->GetDefaultObject<AWeapon>();
}