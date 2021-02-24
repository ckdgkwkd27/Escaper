 


#include "Zombie.h"
#include "ZombieAnim.h"
#include "ZombieAIController.h"
#include "UserPlayer.h"
#include "UserController.h"
#include "EscaperGameInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = nullptr;
	bAttack = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Zombie"));
	GetMesh()->SetReceivesDecals(false);

	iMovePoint = 0;
	iMovePointDir = 1;

	static ConstructorHelpers::FClassFinder<UZombieAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BPZombieAnim.BPZombieAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<AActor> HealthItemAsset(TEXT("Blueprint'/Game/Monster/BPHealthItem.BPHealthItem_C'"));
	if(HealthItemAsset.Succeeded())
		HealthItemClass = HealthItemAsset.Class;

	static ConstructorHelpers::FClassFinder<ADroppedBullet> BulletItemAsset(TEXT("Blueprint'/Game/Weapons/Ammunition/DropItem/BPDroppedBullet.BPDroppedBullet_C'"));
	if (BulletItemAsset.Succeeded())
		BulletItemClass = BulletItemAsset.Class;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> PaperburnAsset(TEXT("MaterialInstanceConstant'/Game/Monster/MTPaperBurn_Inst.MTPaperBurn_Inst'"));
	if (PaperburnAsset.Succeeded())
		PaperburnMT = PaperburnAsset.Object;

	bIsDead = false;
	zombie_death_time = 0.f;
	zombie_death_time_max = 5.f;
	burnValue = 0.f;
	filterValue = 2.f;
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();

	//Get Data from Table
	UEscaperGameInstance* gameInstance = GetGameInstance<UEscaperGameInstance>();
	const FZombieInfo* pZombieInfo = gameInstance->FindZombieInfo(gameInstance->diff);

	if (pZombieInfo == nullptr) {
		return;
	}
	ZombieState.HPMax = pZombieInfo->HPMax;
	ZombieState.HP = pZombieInfo->HP;
	ZombieState.Speed = pZombieInfo->Speed;
	ZombieState.Attack = pZombieInfo->Attack;
	ZombieState.TraceRange = pZombieInfo->TraceRange;
	ZombieState.AttackRange = pZombieInfo->AttackRange;

	GetCharacterMovement()->MaxWalkSpeed = ZombieState.Speed;

	ZombieAnim = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead) {
		if (zombie_death_time >= zombie_death_time_max)
			Destroy();

		zombie_death_time += DeltaTime;
		burnValue += (DeltaTime / 8.f);
		filterValue -= (DeltaTime / 5.f);
		TArray<USceneComponent*> comps;
		GetMesh()->GetChildrenComponents(true, comps);

		for (auto x : comps) {
			USkeletalMeshComponent* skm = Cast<USkeletalMeshComponent>(x);
			UMaterialInstanceDynamic* dynamic_burn;

			if (IsValid(skm)) {
				dynamic_burn = skm->CreateDynamicMaterialInstance(0, PaperburnMT);
				dynamic_burn->SetScalarParameterValue(TEXT("Burn"), burnValue);
				dynamic_burn->SetScalarParameterValue(TEXT("Filter"), filterValue);

				GetMesh()->SetMaterial(0, dynamic_burn);
				GetMesh()->SetMaterial(1, dynamic_burn);
				skm->SetMaterial(0, dynamic_burn);
				skm->SetMaterial(1, dynamic_burn);
			}
		}
	}
}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZombie::ChangeAnim(EZombieAnim eAnim)
{
	ZombieAnim->ChangeAnim(eAnim);
}

float AZombie::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	ZombieState.HP -= (int32)fDamage;

	if (ZombieState.HP <= 0) {
		ZombieState.HP = 0;
		ChangeAnim(EZombieAnim::Death); 
		bIsDead = true;

		AZombieAIController* ZombieController = GetController<AZombieAIController>();
		if (IsValid(ZombieController)) {
			UBehaviorTreeComponent* BT = Cast<UBehaviorTreeComponent>(ZombieController->GetBrainComponent());
			if (IsValid(BT))
				BT->StopTree(EBTStopMode::Safe);
		}

		int iRand = FMath::RandRange(0.f, 100.f);

		FActorSpawnParameters	params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (0 <= iRand && iRand < 20) {
			HealthItem = GetWorld()->SpawnActor<AActor>(HealthItemClass, GetActorLocation(), GetActorRotation(), params);
		}
		else if (20 <= iRand && iRand < 40) {
			BulletItem = GetWorld()->SpawnActor<ADroppedBullet>(BulletItemClass, GetActorLocation(), GetActorRotation(), params);
		}			
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return fDamage;
}

void AZombie::AddPatrolPoint(APatrolPoint* point)
{
	PatrolPointArray.Add(point);
}

void AZombie::AttackEnd()
{
	bAttack = false;
	OnAttackEnd.Broadcast();

	for (FDelegateHandle& handle : AttackEndHandle)
	{
		OnAttackEnd.Remove(handle);
	}

	FDamageEvent DamageEvent;
	AUserPlayer* userPlayer = Cast<AUserPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	userPlayer->TakeDamage(10, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
	userPlayer->SetHealth(userPlayer->GetHealth());
}

void AZombie::Death()
{
	if (IsValid(SpawnPoint))
		SpawnPoint->Respawn();

	Destroy();
}