 

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CinematicZone.generated.h"

UCLASS()
class ESCAPER_API ACinematicZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACinematicZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
		void StartEvent();

	UFUNCTION()
		void EndEvent();

	UFUNCTION()
		void CameraBlendEnd();

	UFUNCTION()
		void CameraChangeEnd(); 

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> CameraArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	AActor* MoveCamera;

	UPROPERTY()
	int32		PointIndex;

	UPROPERTY()
	FTimerHandle	BlendTimerHandle;

	UPROPERTY()
	FTimerHandle	ChangeTimerHandle;
};
