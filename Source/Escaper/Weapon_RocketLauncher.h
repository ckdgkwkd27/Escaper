 

#pragma once

#include "GameInfo.h"
#include "Weapon.h"
#include "Weapon_RocketLauncher.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API AWeapon_RocketLauncher : public AWeapon
{
	GENERATED_BODY()
	
public:
	AWeapon_RocketLauncher();
	virtual void BeginPlay();
	virtual void LaunchBullet();
	virtual void SetBullet(int32 bulletCnt, int32 maxbulletCnt);
};
