 

#pragma once

#include "GameInfo.h"
#include "Weapon.h"
#include "Engine/GameInstance.h"
#include "EscaperGameInstance.generated.h"


UENUM(BlueprintType, Meta = (Bitflags))
enum class EDifficulty : uint8
{
	Normal,
	Hard
};

USTRUCT(BlueprintType)
struct FZombieInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32	HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32	HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	AttackRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	TraceRange;

};

UCLASS()
class ESCAPER_API UEscaperGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	EDifficulty diff;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TMap<FString, bool> PickupSpawnMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool bFireAreaSolved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float PlayedTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString PrevLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString CurrLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FRotator SpawnRotation;

public:
	UEscaperGameInstance();
	TArray<UItemObject*> GetAllInventoryItem() const;
	void AddItem(UItemObject* obj);
	void SetWeapon(TSubclassOf<AWeapon> _Weapon);
	TSubclassOf<AWeapon> GetWeapon() const;
	void SetHP(int32 _hp);
	int32 GetHP() const;
	TArray<TSubclassOf<AWeapon>> GetWeaponClasses() const;
	void SetWeaponName(FString _name);
	FString GetWeaponName() const;
	const FZombieInfo* FindZombieInfo(const EDifficulty& dfct) const;

	UFUNCTION(BlueprintCallable)
	FVector GetProperLocation(FString from, FString to);

protected:
	UFUNCTION(BlueprintCallable)
	virtual void init();

private:
	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* inventory;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UItemObject*> Items;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> Weapon;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 hp;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AWeapon>> WeaponClasses;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString WeaponName;

	UPROPERTY(Category = ZombieInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* ZombieInfoTable;

public:
	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ARBulletCnt;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ARMaxBulletCnt;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 SMGBulletCnt;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 SMGMaxBulletCnt;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 PistolBulletCnt;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 PistolMaxBulletCnt;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 RocketBulletCnt;

	UPROPERTY(Category = PlayerInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 RocketMaxBulletCnt;

	UPROPERTY(Category = PortalInfo, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bPortalLocked;
};