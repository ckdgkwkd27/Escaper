 


#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bSpawnEnable = true;
	bInfinity = false;
	SpawnTime = 0.f; // max time
	SpawnDuration = 2.f; // current time
	SpawnZombie = nullptr;

	regenTime = 30.f;
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(SpawnType))
	{
		SpawnDuration += DeltaTime;

		if (SpawnDuration >= SpawnTime)
		{
			SpawnDuration = 0.f;
			SpawnTime = regenTime;

			if (!bInfinity)
			{
				if (bSpawnEnable)
				{
					bSpawnEnable = false;

					FActorSpawnParameters	params;
					params.SpawnCollisionHandlingOverride =
						ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
					SpawnZombie = GetWorld()->SpawnActor<AZombie>(SpawnType,
						GetActorLocation(), GetActorRotation(), params);

					SpawnZombie->SetSpawnPoint(this); 

					for (APatrolPoint* point : PatrolPointArray)
					{
						SpawnZombie->AddPatrolPoint(point);
					}
				}
				if(IsValid(SpawnZombie))
					if (SpawnZombie->GetZombieHP() == 0)
						Respawn();
			}

			else
			{
				FActorSpawnParameters	params;
				params.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				SpawnZombie = GetWorld()->SpawnActor<AZombie>(SpawnType,
					GetActorLocation(), GetActorRotation(), params);

				SpawnZombie->SetSpawnPoint(this);

				for (APatrolPoint* point : PatrolPointArray)
				{
					SpawnZombie->AddPatrolPoint(point);
				}
			}
		}

	}
}

void ASpawnPoint::Respawn()
{
	SpawnZombie = nullptr;
	if (bInfinity)
		return;
	bSpawnEnable = true;
}

