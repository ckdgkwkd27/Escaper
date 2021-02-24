 

#pragma once

#include "GameInfo.h"
#include "Weapon.h"
#include "Weapon_SMG.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API AWeapon_SMG : public AWeapon
{
	GENERATED_BODY()


public:
	AWeapon_SMG();
	virtual void BeginPlay();
	virtual void LaunchBullet();
	virtual void SetBullet(int32 bulletCnt, int32 maxbulletCnt);
};
