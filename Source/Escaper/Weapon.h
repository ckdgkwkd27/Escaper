 

#pragma once

#include "GameInfo.h"
#include "Bullet.h"
#include "TimerManager.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class UEscaperGameInstance;

UCLASS()
class ESCAPER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	UPROPERTY(Category = Scene, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString WeaponName;

	UPROPERTY(Category = Scene, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Scene;

	UPROPERTY(Category=Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(Category = Bullet, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABullet> BulletClass;

	UPROPERTY(Category = Niagara, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* Effect;

	UPROPERTY(Category = Fire, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RateOfFire;

	UEscaperGameInstance* gameInstance;

	//RateOfFire¿¡¼­ À¯µµµÊ
	UPROPERTY()
	float TimeBetweenShots;

	UPROPERTY()
	float LastFireTime;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	class AMainGameModeBase* GameMode;

	UPROPERTY()
	class UUIPlayerHUD* playerHUD;

	UPROPERTY()
	class AUserPlayer* player;

	UPROPERTY()
	FText Title;

	UPROPERTY()
	FString IconPath;

	UPROPERTY()
	FText RarityAndCategory;

	UPROPERTY()
	FText Description;

	UPROPERTY()
	FLinearColor RarityColor;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPriavateAccess = "true"))
	int32 bullet_cnt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPriavateAccess = "true"))
	int32 Max_bullet_cnt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPriavateAccess = "true"))
	int32 bulletCntWhole;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPriavateAccess = "true"))
	int32 MaxbulletCntWhole;

public:	
	virtual void BeginPlay();
	virtual void LoadMesh(const FString& strPath);
	virtual void LaunchBullet();
	virtual void SetBullet(int32 bulletCnt, int32 maxbulletCnt);
	virtual int32 GetBullet();
	virtual void SetBulletWhole(int32 bullet, int32 maxbullet);
	virtual void SetMaxBulletWhole(int32 bullet);
	virtual int32 GetBulletWhole() const;
	virtual int32 GetMaxBulletWhole() const;
	virtual void StartFire(class AUserPlayer* userPlayer, FVector v, FRotator r);
	virtual void EndFire();

	UFUNCTION(BlueprintCallable)
	virtual int32 GetMaxBullet();

	virtual USkeletalMeshComponent* GetMesh() {
		return Mesh;
	}

	virtual void SetWeaponName(FString str) {
		WeaponName = str;
	}

	UFUNCTION(BlueprintCallable)
	virtual FString GetWeaponName() {
		return WeaponName;
	}

	virtual FText GetTitle() const {
		return Title;
	}

	virtual FText GetRarityAndCategory() const {
		return RarityAndCategory;
	}

	virtual FText GetDescription() const {
		return Description;
	}

	virtual FString GetIconPath() const {
		return IconPath;
	}

	virtual void SetIconPath(const FString& path) {
		IconPath = path;
	}

	virtual void SetRarityColor(FLinearColor color) {
		RarityColor = color;
	}

	virtual FLinearColor GetRarityColor() const {
		return RarityColor;
	}
};
