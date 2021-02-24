 

#pragma once

#include "GameInfo.h"
#include "EscaperGameInstance.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class ESCAPER_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapPortal(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* Effect;

	UPROPERTY(Category = "Level", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString LoadingLevel;

	UPROPERTY(Category = "Level", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bLocked;

	UPROPERTY(Category = "Level", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector SpawnLocation;

	UPROPERTY(Category = "Level", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator SpawnRoatation;

	UPROPERTY()
	UEscaperGameInstance* gameInstance;
};
