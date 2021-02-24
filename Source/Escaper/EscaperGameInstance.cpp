 


#include "EscaperGameInstance.h"
#include "ItemObject.h"
#include "InventoryComponent.h"

UEscaperGameInstance::UEscaperGameInstance() {
	hp = -1;

	ARBulletCnt = -1;
	ARMaxBulletCnt = -1;

	SMGBulletCnt = -1;
	SMGMaxBulletCnt = -1;

	PistolBulletCnt = -1;
	PistolMaxBulletCnt = -1;

	RocketBulletCnt = -1;
	RocketMaxBulletCnt = -1;

	bPortalLocked = true;

	PlayedTime = 0.f;

	PrevLevel = "";
	CurrLevel = "";

	bFireAreaSolved = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> ZombieInfoAsset(TEXT("DataTable'/Game/Monster/ZombieInfoDataTable.ZombieInfoDataTable'"));
	if (ZombieInfoAsset.Succeeded()) 
		ZombieInfoTable = ZombieInfoAsset.Object;
}

void UEscaperGameInstance::init()
{
	Super::Init();

	hp = -1;

	ARBulletCnt = -1;
	ARMaxBulletCnt = -1;

	SMGBulletCnt = -1;
	SMGMaxBulletCnt = -1;

	PistolBulletCnt = -1;
	PistolMaxBulletCnt = -1;

	RocketBulletCnt = -1;
	RocketMaxBulletCnt = -1;

	bPortalLocked = true;

	PlayedTime = 0.f;

	PrevLevel = "";
	CurrLevel = "";

	bFireAreaSolved = false;

	WeaponClasses.Empty();
	PickupSpawnMap.Empty();
}

TArray<UItemObject*> UEscaperGameInstance::GetAllInventoryItem() const
{
	return Items;
}

void UEscaperGameInstance::AddItem(UItemObject* obj) {
	Items.Add(obj);
}

void UEscaperGameInstance::SetWeapon(TSubclassOf<AWeapon> _Weapon)
{
	Weapon = _Weapon;

	WeaponClasses.Add(_Weapon);
}

TSubclassOf<AWeapon> UEscaperGameInstance::GetWeapon() const
{
	return Weapon;
}

void UEscaperGameInstance::SetHP(int32 _hp)
{
	hp = _hp;
}

int32 UEscaperGameInstance::GetHP() const
{
	return hp;
}

TArray<TSubclassOf<AWeapon>> UEscaperGameInstance::GetWeaponClasses() const
{
	return WeaponClasses;
}

void UEscaperGameInstance::SetWeaponName(FString _name)
{
	WeaponName = _name;
}

FString UEscaperGameInstance::GetWeaponName() const
{
	return WeaponName;
}

const FZombieInfo* UEscaperGameInstance::FindZombieInfo(const EDifficulty& dfct) const
{
	if (!IsValid(ZombieInfoTable))
		return nullptr;

	FName diffname = dfct == EDifficulty::Normal ? FName("Normal") : FName("Hard");
	return ZombieInfoTable->FindRow<FZombieInfo>(diffname, "");
}

FVector UEscaperGameInstance::GetProperLocation(FString from, FString to)
{
	FVector properLocation;
	if (from == "Main" && to == "Alley")
		properLocation = FVector(0.000244, -400.f, 240.f);

	return properLocation;
}