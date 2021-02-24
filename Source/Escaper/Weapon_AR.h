 

#pragma once

#include "GameInfo.h"
#include "Bullet.h"
#include "Weapon.h"
#include "GameFramework/Actor.h"
#include "Weapon_AR.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPER_API AWeapon_AR : public AWeapon
{
	GENERATED_BODY()


public:
	AWeapon_AR();
	virtual void BeginPlay();
	virtual void LaunchBullet();
	virtual void SetBullet(int32 bulletCnt, int32 maxbulletCnt);
};
