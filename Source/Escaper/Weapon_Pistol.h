 

#pragma once

#include "GameInfo.h"
#include "Weapon.h"
#include "Weapon_Pistol.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API AWeapon_Pistol : public AWeapon
{
	GENERATED_BODY()

public:
	AWeapon_Pistol();
	virtual void BeginPlay();
	virtual void LaunchBullet();
	virtual void SetBullet(int32 bulletCnt, int32 maxbulletCnt);
};
