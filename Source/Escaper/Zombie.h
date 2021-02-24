 

#pragma once

#include "GameInfo.h"
#include "ZombieAnim.h"
#include "SpawnPoint.h"
#include "PatrolPoint.h"
#include "DroppedBullet.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"


// 공격이 종료되었을때 호출될 함수를 등록할 델리게이트를 만들어준다.
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate)

USTRUCT(Atomic, BlueprintType)
struct FZombieState
{
	GENERATED_USTRUCT_BODY()

public:
	FZombieState()
	{

	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32	HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32	HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	TraceRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	AttackRange;
};


UCLASS()
class ESCAPER_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombie();
	void AttackEnd();
	void Death();

private:
	float zombie_death_time;
	float zombie_death_time_max;
	float burnValue;
	float filterValue;
	bool bIsDead;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	class ASpawnPoint* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<APatrolPoint*>	PatrolPointArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FZombieState	ZombieState;

	UPROPERTY()
	class UZombieAnim* ZombieAnim;

	bool bAttack;
	int32	iMovePoint;
	int32	iMovePointDir;

	FOnAttackEndDelegate	OnAttackEnd;

	TArray<FDelegateHandle>	AttackEndHandle;
	
	UPROPERTY()
	TSubclassOf<AActor> HealthItemClass;

	UPROPERTY()
	AActor* HealthItem;

	UPROPERTY()
	TSubclassOf<ADroppedBullet> BulletItemClass;

	UPROPERTY()
	ADroppedBullet* BulletItem;


	UPROPERTY()
	UMaterialInstance* PaperburnMT;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void ChangeAnim(EZombieAnim eAnim);

	template <typename T>
	void AddAttackEndDelegate(T* pObj, void(T::* pFunc)()) {
		FDelegateHandle handle = OnAttackEnd.AddUObject(pObj, pFunc);
		AttackEndHandle.Add(handle);
	}

	void AddPatrolPoint(APatrolPoint* point);
	int32 GetPatrolPointCount()	const
	{
		return PatrolPointArray.Num();
	}

	APatrolPoint* GetPatrolPoint()
	{
		return PatrolPointArray[iMovePoint];
	}

	void NextPatrolPoint()
	{
		iMovePoint += iMovePointDir;

		if (iMovePoint == PatrolPointArray.Num())
		{
			iMovePointDir = -1;
			iMovePoint = PatrolPointArray.Num() - 2;
		}

		else if (iMovePoint == -1)
		{
			iMovePointDir = 1;
			iMovePoint = 0;
		}
	}

	void SetSpawnPoint(ASpawnPoint* Point)
	{
		SpawnPoint = Point;
	}

	float GetTraceRange()	const
	{
		return ZombieState.TraceRange;
	}

	float GetAttackDistance()	const
	{
		return ZombieState.AttackRange;
	}

	float GetAttackPoint()	const
	{
		return ZombieState.Attack;
	}

	int32 GetZombieHP() const {
		return ZombieState.HP;
	}

	void Attack()
	{
		bAttack = true;
	}

	bool IsAttack()	const
	{
		return bAttack;
	}

};
