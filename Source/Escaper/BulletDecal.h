 

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "BulletDecal.generated.h"

UCLASS()
class ESCAPER_API ABulletDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletDecal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* Decal;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
